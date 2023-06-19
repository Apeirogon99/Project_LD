// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/Game/Inventory/StoreInven/UWGridInventory.h"
#include "Widget/Game/Inventory/UWItem.h"
#include "WIdget/Game/Inventory/UWInventory.h"
#include "Widget/Game/Item/W_ItemSpace.h"

#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include <Game/GM_Game.h>
#include <Game/PC_Game.h>
#include <Widget/Handler/ClientHUD.h>

#include <Component/ACEquipment.h>
#include <Component/ACInventoryComponent.h>
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Kismet/GameplayStatics.h"


void UUWGridInventory::NativeConstruct()
{
	Super::NativeConstruct();

	TSubclassOf<UUWItem> ImageWidgetAsset = StaticLoadClass(UUWItem::StaticClass(), NULL, TEXT("WidgetBlueprint'/Game/Blueprint/Widget/Game/Inventory/Item/BW_Item.BW_Item_C'"));
	if (ImageWidgetAsset)
	{
		mImageAsset = ImageWidgetAsset;
	}

	GridBorder = Cast<UBorder>(GetWidgetFromName(TEXT("GridBorder")));
	GridCanvas_Panel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("GridCanvas_Panel")));
}

void UUWGridInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUWGridInventory::NativeDestruct()
{
	Super::NativeDestruct();

	if (mInventoryComponent)
	{
		if (mInventoryComponent->OnInventoryChanged.IsBound())
		{
			mInventoryComponent->OnInventoryChanged.Unbind();
		}
	}
}

FReply UUWGridInventory::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);

	return FReply::Handled();
}

FReply UUWGridInventory::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);	

	if (InKeyEvent.GetKey() == EKeys::R)
	{
		UDragDropOperation* Operator = UWidgetBlueprintLibrary::GetDragDroppingContent();
		UItemObjectData* payload;
		GetPayload(Operator, payload);

		if (IsValid(payload))
		{
			if (Operator != nullptr)
			{
				UUWItem* ItemWidget = Cast<UUWItem>(Operator->DefaultDragVisual);
				if (ItemWidget)
				{
					payload->Rotate();
					ItemWidget->Refresh();
					return FReply::Handled();
				}
			}
		}
	}
	return FReply::Handled();
}

bool UUWGridInventory::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UItemObjectData* Data = Cast<UItemObjectData>(Cast<UDragDropOperation>(InOperation)->Payload);
	if (Data->Type == EItemObjectType::Inventory)
	{
		//공간이 있는지 파악
		if (IsRoomAvailableForPayload(Data))
		{
			GetPayload(InOperation, Data);
			if (Data->IsValid())
			{
				FTile tile;
				tile.X = mDraggedItemTopLeftTile.X;
				tile.Y = mDraggedItemTopLeftTile.Y;

				mInventoryComponent->AddItemAt(Data, mInventoryComponent->TileToIndex(tile));

				mInventoryComponent->SetInventoryPacket(Data, EInventoryType::Update);
			}
		}
		else
		{
			GetPayload(InOperation, Data);
			if (Data->IsValid())
			{
				if (!mInventoryComponent->TryAddItem(Data))
				{
					//Spawn Item
					mInventoryComponent->SetInventoryPacket(Data, EInventoryType::Remove);
				}
				else
				{
					mInventoryComponent->SetInventoryPacket(Data, EInventoryType::Update);
				}
			}
		}
	}
	if (Data->Type == EItemObjectType::Equipment)
	{
		if (IsRoomAvailableForPayload(Data))
		{
			GetPayload(InOperation, Data);
			if (Data->IsValid())
			{
				FTile tile;
				tile.X = mDraggedItemTopLeftTile.X;
				tile.Y = mDraggedItemTopLeftTile.Y;

				Data->Type = EItemObjectType::Inventory;
				mInventoryComponent->AddItemAt(Data, mInventoryComponent->TileToIndex(tile));
				mEquipmentComponent->mEquipmentData[Data->ItemData.category_id - 1]=NewObject<UItemObjectData>();

				mInventoryComponent->ReplacePacket(Data, NewObject<UItemObjectData>(),Data->ItemData.category_id);
			}
		}
		else
		{
			GetPayload(InOperation, Data);
			if (Data->IsValid())
			{
				Data->Type = EItemObjectType::Inventory;
				if (!mInventoryComponent->TryAddItem(Data))
				{
					Data->Type = EItemObjectType::Equipment;
					mEquipmentComponent->mEquipmentData[Data->ItemData.category_id - 1] = Data;
					mEquipmentComponent->mEquipmentWidget[Data->ItemData.category_id - 1]->ReMakeWidget(Data);
				}
				else
				{
					mEquipmentComponent->mEquipmentData[Data->ItemData.category_id - 1] = NewObject<UItemObjectData>();

					mInventoryComponent->ReplacePacket(Data, NewObject<UItemObjectData>(), Data->ItemData.category_id);
				}
			}
		}
	}
	mEquipmentComponent->DropItemWidget();
	
	return true;
}

bool UUWGridInventory::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	FVector2D MousePosition_Local = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	FMousePositionReturn MousePositionbool = MousePositionInTile(MousePosition_Local);

	UDragDropOperation* Operation = Cast<UDragDropOperation>(InOperation);
	UItemObjectData* ItemObjectData = Cast<UItemObjectData>(Operation->Payload);
	int32 RightSelect;
	int32 DownSelect;

	FIntPoint makeIntPoint;

	MousePositionbool.Right == true ? RightSelect = 1 : RightSelect = 0;
	float ClampValue_X = ItemObjectData->GetSize().X - RightSelect;
	makeIntPoint.X = FMath::Clamp(ClampValue_X, 0.0f, ClampValue_X);

	MousePositionbool.Down == true ? DownSelect = 1 : DownSelect = 0;
	float ClampValue_Y = ItemObjectData->GetSize().Y - DownSelect;
	makeIntPoint.Y = FMath::Clamp(ClampValue_Y, 0.0f, ClampValue_Y);

	mDraggedItemTopLeftTile = FIntPoint(FMath::TruncToInt(MousePosition_Local.X / mTileSize), FMath::TruncToInt(MousePosition_Local.Y / mTileSize)) - (makeIntPoint / 2);

	mEquipmentComponent->CanItemDropWidgetCheck(ItemObjectData);

	return true;
}

void UUWGridInventory::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	mDrawDropLocation = true;
}

void UUWGridInventory::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	mDrawDropLocation = false;
}

//초기화
void UUWGridInventory::Init(UACInventoryComponent* InvenComponent, float Size, UACEquipment* EquipmentComponent)
{
	mInventoryComponent = InvenComponent;
	mTileSize = Size;
	mEquipmentComponent = EquipmentComponent;

	if (mInventoryComponent != nullptr)
	{
		float SizeX = mInventoryComponent->mColums * GetTileSize();
		float SizeY = mInventoryComponent->mRows * GetTileSize();

		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot);
		CanvasSlot->SetSize(FVector2D(SizeX, SizeY));

		CreateLineSegments();
		Refresh();
		mInventoryComponent->OnInventoryChanged.BindUFunction(this, FName("Refresh"));
	}
}

//라인그리기
void UUWGridInventory::CreateLineSegments()
{
	//Vertical
	for (int Index = 0; Index < mInventoryComponent->mColums + 1; Index++)
	{
		float X_Local = Index * mTileSize;
		FLine makeLine;
		makeLine.Start = FVector2D(X_Local, 0.0f);
		makeLine.End = FVector2D(X_Local, mInventoryComponent->mRows * mTileSize);
		
		LineArr.Add(makeLine);
	}
	//Horizantal
	for (int Index = 0; Index < mInventoryComponent->mRows + 1; Index++)
	{
		float Y_Local = Index * mTileSize;
		FLine makeLine;
		makeLine.Start = FVector2D(0.0f, Y_Local);
		makeLine.End = FVector2D(mInventoryComponent->mColums * mTileSize, Y_Local);

		LineArr.Add(makeLine);
	}	
}

void UUWGridInventory::CallRemoved_Single(UItemObjectData*& ItemData)
{
	mInventoryComponent->RemoveItem(ItemData);
}

//캔버스 초기화 후 Item 받아와서 이미지 생성
void UUWGridInventory::Refresh()
{
	GridCanvas_Panel->ClearChildren();

	TArray<UItemObjectData*> AllItem = mInventoryComponent->GetAllItems();
	for (UItemObjectData*& Data : AllItem)
	{
		if (IsValid(mImageAsset))
		{
			UUWItem* ItemImageWidget = Cast<UUWItem>(CreateWidget(GetWorld(), mImageAsset));
			if (ItemImageWidget)
			{
				ItemImageWidget->mTileSize = mTileSize;
				ItemImageWidget->mItemObjectData = Data;
	
				//Bind Remove
				ItemImageWidget->OnRemoved.AddUFunction(this, FName("CallRemoved_Single"));

				UPanelSlot* LocalPanelSlot = GridCanvas_Panel->AddChild(ItemImageWidget);
				UCanvasPanelSlot* Local_Slot = Cast<UCanvasPanelSlot>(LocalPanelSlot);
				
				float sizeX = Data->GetSize().X * mTileSize;
				float sizeY = Data->GetSize().Y * mTileSize;

				Local_Slot->SetSize(FVector2D(sizeX, sizeY));

				float posX = Data->position_x * mTileSize;
				float posY = Data->position_y * mTileSize;
				Local_Slot->SetPosition(FVector2D(posX, posY));
			}
		}
	}
}

//아이템 데이터 받아오기
void UUWGridInventory::GetPayload(UDragDropOperation* Operator,UItemObjectData*& Payload) const
{
	if (IsValid(Operator))
	{
		Payload = Cast<UItemObjectData>(Operator->Payload);
	}
	else
	{
		Payload = NewObject<UItemObjectData>();
	}
}

bool UUWGridInventory::IsRoomAvailableForPayload(UItemObjectData* Payload) const
{
	if (Payload->IsValid())
	{
		FTile tile;
		tile.X = mDraggedItemTopLeftTile.X;
		tile.Y = mDraggedItemTopLeftTile.Y;
		return mInventoryComponent->IsRoomAvailable(Payload, mInventoryComponent->TileToIndex(tile));
	}

	return false;
}

FMousePositionReturn UUWGridInventory::MousePositionInTile(FVector2D MousePosition)
{
	FMousePositionReturn Return = FMousePositionReturn();
	Return.Right = FMath::Fmod(MousePosition.X, mTileSize) > (mTileSize / 2.0f);
	Return.Down = FMath::Fmod(MousePosition.Y, mTileSize) > (mTileSize / 2.0f);
	return Return;
}