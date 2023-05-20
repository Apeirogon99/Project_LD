// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/Game/Inventory/StoreInven/UWGridInventory.h"
#include "Widget/Game/Inventory/UWItem.h"
#include "Components/CanvasPanelSlot.h"


void UUWGridInventory::NativeConstruct()
{
	Super::NativeConstruct();

	TSubclassOf<UUWItem> ImageWidgetAsset = StaticLoadClass(UUWItem::StaticClass(), NULL, TEXT("WidgetBlueprint'/Game/TestFolder/TestCharacter/widget/BW_Item.BW_Item_C'"));
	if (ImageWidgetAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("ImageWidget Succeeded"));
		ImageAsset = ImageWidgetAsset;
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

	ACInventory->OnInventoryChanged.Clear();
}

FReply UUWGridInventory::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);

	return FReply::Handled();
}

bool UUWGridInventory::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	FItemData Data = GetPayload(InOperation);
	if (IsRoomAvailableForPayload(Data))
	{
		Data = GetPayload(InOperation);
		ACInventory->AddItemAt(Data, ACInventory->TileToIndex(FTile(DraggedItemTopLeftTile.X, DraggedItemTopLeftTile.Y)));
	}
	else
	{
		Data = GetPayload(InOperation);
		if (!ACInventory->TryAddItem(Data))
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
	UItemDataObject* ItemData = Cast<UItemDataObject>(Operation->Payload);
	int32 RightSelect;
	int32 DownSelect;

	FIntPoint makeIntPoint;

	MousePositionbool.Right == true ? RightSelect = 1 : RightSelect = 0;
	float ClampValue_X = ItemData->GetSize().X - RightSelect;
	makeIntPoint.X = FMath::Clamp(ClampValue_X, 0.0f, ClampValue_X);

	MousePositionbool.Down == true ? DownSelect = 1 : DownSelect = 0;
	float ClampValue_Y = ItemData->GetSize().Y - DownSelect;
	makeIntPoint.Y = FMath::Clamp(ClampValue_Y, 0.0f, ClampValue_Y);

	DraggedItemTopLeftTile = FIntPoint(FMath::TruncToInt(MousePosition_Local.X / TileSize), FMath::TruncToInt(MousePosition_Local.Y / TileSize)) - (makeIntPoint / 2);

	return true;
}

void UUWGridInventory::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	DrawDropLocation = true;
}

void UUWGridInventory::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	DrawDropLocation = false;
}

void UUWGridInventory::Init(UACInventoryComponent* InventoryComponent, float Size)
{
	ACInventory = InventoryComponent;
	TileSize = Size;
	if (ACInventory != nullptr)
	{
		float SizeX = GetACInventory()->Colums * GetTileSize();
		float SizeY = GetACInventory()->Rows * GetTileSize();

		UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot);
		CanvasSlot->SetSize(FVector2D(SizeX, SizeY));

		CreateLineSegments();
		Refresh();
		ACInventory->OnInventoryChanged.AddUFunction(this, FName("Refresh"));
	}
}

void UUWGridInventory::CreateLineSegments()
{
	//Vertical
	for (int Index = 0; Index < GetACInventory()->Colums + 1; Index++)
	{
		float X_Local = Index * TileSize;
		FLine makeLine;
		makeLine.Start = FVector2D(X_Local, 0.0f);
		makeLine.End = FVector2D(X_Local, GetACInventory()->Rows * TileSize);
		
		LineArr.Add(makeLine);
	}
	//Horizantal
	for (int Index = 0; Index < GetACInventory()->Rows + 1; Index++)
	{
		float Y_Local = Index * TileSize;
		FLine makeLine;
		makeLine.Start = FVector2D(0.0f, Y_Local);
		makeLine.End = FVector2D(GetACInventory()->Colums * TileSize, Y_Local);

		LineArr.Add(makeLine);
	}	
}

void UUWGridInventory::CallRemoved_Single(FItemData& ItemData)
{
	UE_LOG(LogTemp, Warning, TEXT("CallRemoved_Single"));
	ACInventory->RemoveItem(ItemData);
}

void UUWGridInventory::Refresh()
{
	GridCanvas_Panel->ClearChildren();

	TArray<FItemData> AllItem = ACInventory->GetAllItems();
	for (FItemData Data : AllItem)
	{
		if (IsValid(ImageAsset))
		{
			UUWItem* ItemImageWidget = Cast<UUWItem>(CreateWidget(GetWorld(), ImageAsset));
			if (ItemImageWidget)
			{
				ItemImageWidget->TileSize = TileSize;
				ItemImageWidget->ItemData = Data;

				//Bind Remove
				ItemImageWidget->OnRemoved.AddUFunction(this, FName("CallRemoved_Single"));

				UCanvasPanelSlot* Local_Slot = Cast<UCanvasPanelSlot>(GridCanvas_Panel->AddChild(ItemImageWidget));
				Local_Slot->SetAutoSize(true);
				float X = Data.position_x * TileSize;
				float Y = Data.position_y * TileSize;
				Local_Slot->SetPosition(FVector2D(X, Y));
			}
		}
	}
}

FItemData UUWGridInventory::GetPayload(UDragDropOperation* Operator)
{
	if (IsValid(Operator))
	{
		return Cast<UItemDataObject>(Operator->Payload)->ItemData;
	}

	return FItemData();
}

UItemDataObject* UUWGridInventory::GetPayloadObject(UDragDropOperation* Operator) const
{
	UItemDataObject* Object = NewObject<UItemDataObject>();
	if (IsValid(Operator))
	{
		Object = Cast<UItemDataObject>(Operator->Payload);
	}
	return Object;
}

bool UUWGridInventory::IsRoomAvailableForPayload(FItemData Payload) const
{
	if (Payload.IsValid())
	{
		return ACInventory->IsRoomAvailable(Payload, ACInventory->TileToIndex(FTile(DraggedItemTopLeftTile.X, DraggedItemTopLeftTile.Y)));
	}

	return false;
}

FMousePositionReturn UUWGridInventory::MousePositionInTile(FVector2D MousePosition)
{
	FMousePositionReturn Return = FMousePositionReturn();
	Return.Right = FMath::Fmod(MousePosition.X, TileSize) > (TileSize / 2.0f);
	Return.Down = FMath::Fmod(MousePosition.Y, TileSize) > (TileSize / 2.0f);
	return Return;
}
