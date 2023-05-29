// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/Game/Inventory/StoreInven/UWGridInventory.h"
#include "Widget/Game/Inventory/UWItem.h"

#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include <Game/PS_Game.h>
#include <Game/GM_Game.h>

#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>

#include "Kismet/GameplayStatics.h"


void UUWGridInventory::NativeConstruct()
{
	Super::NativeConstruct();

	TSubclassOf<UUWItem> ImageWidgetAsset = StaticLoadClass(UUWItem::StaticClass(), NULL, TEXT("WidgetBlueprint'/Game/Blueprint/Widget/Game/Inventory/BW_Item.BW_Item_C'"));
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

	if (mInventoryComponent->OnInventoryChanged.IsBound())
	{
		mInventoryComponent->OnInventoryChanged.Unbind();
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
	if (IsRoomAvailableForPayload(Data))
	{
		GetPayload(InOperation, Data);
		FTile tile;
		tile.X = mDraggedItemTopLeftTile.X;
		tile.Y = mDraggedItemTopLeftTile.Y;

		Update(Data->ObjectID, Data->mItemCode, tile.X, tile.Y, Data->rotation);

		mInventoryComponent->AddItemAt(Data, mInventoryComponent->TileToIndex(tile));
	}
	else
	{
		GetPayload(InOperation, Data);
		if (!mInventoryComponent->TryAddItem(Data))
		{
			//Spawn Item
		}
	}
	
	return true;
}

bool UUWGridInventory::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	FVector2D MousePosition_Local = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	FMousePositionReturn MousePositionbool = MousePositionInTile(MousePosition_Local);

	UDragDropOperation* Operation = Cast<UDragDropOperation>(InOperation);
	UItemObjectData* ItemData = Cast<UItemObjectData>(Operation->Payload);
	int32 RightSelect;
	int32 DownSelect;

	FIntPoint makeIntPoint;

	MousePositionbool.Right == true ? RightSelect = 1 : RightSelect = 0;
	float ClampValue_X = ItemData->GetSize().X - RightSelect;
	makeIntPoint.X = FMath::Clamp(ClampValue_X, 0.0f, ClampValue_X);

	MousePositionbool.Down == true ? DownSelect = 1 : DownSelect = 0;
	float ClampValue_Y = ItemData->GetSize().Y - DownSelect;
	makeIntPoint.Y = FMath::Clamp(ClampValue_Y, 0.0f, ClampValue_Y);

	mDraggedItemTopLeftTile = FIntPoint(FMath::TruncToInt(MousePosition_Local.X / mTileSize), FMath::TruncToInt(MousePosition_Local.Y / mTileSize)) - (makeIntPoint / 2);

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

void UUWGridInventory::Init(UACInventoryComponent* InvenComponent, float Size)
{
	mInventoryComponent = InvenComponent;
	mTileSize = Size;

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

				UCanvasPanelSlot* Local_Slot = Cast<UCanvasPanelSlot>(GridCanvas_Panel->AddChild(ItemImageWidget));
				Local_Slot->SetAutoSize(true);
				float X = Data->position_x * mTileSize;
				float Y = Data->position_y * mTileSize;
				Local_Slot->SetPosition(FVector2D(X, Y));
			}
		}
	}
}

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

void UUWGridInventory::Update(const int64 inObjectID, const int32 inItemID, const int32 inPositionX, const int32 inPositionY, const int32 inRotation)
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
	if (nullptr == gameMode)
	{
		return;
	}

	ANetworkController* controller = gameMode->GetNetworkController();
	if (nullptr == controller)
	{
		return;
	}

	Protocol::C2S_UpdateInventory updateInventoryPacket;
	updateInventoryPacket.set_timestamp(controller->GetServerTimeStamp());
	Protocol::SItem* item = updateInventoryPacket.mutable_item();
	item->set_object_id(inObjectID);
	item->set_item_code(inItemID);

	Protocol::SVector2D* invenPositon = item->mutable_inven_position();
	invenPositon->set_x(inPositionX);
	invenPositon->set_y(inPositionY);
	item->set_rotation(inRotation);

	SendBufferPtr sendBuffer = FGamePacketHandler::MakeSendBuffer(controller, updateInventoryPacket);
	controller->Send(sendBuffer);

}
