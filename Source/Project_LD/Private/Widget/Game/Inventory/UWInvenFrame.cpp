// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Inventory/UWInvenFrame.h"
#include "Blueprint/DragDropOperation.h"

#include <Component/ACInventoryComponent.h>

void UUWInvenFrame::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UUWInvenFrame::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);

	return FReply::Handled();
}

bool UUWInvenFrame::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragDropOperation* Operation = Cast<UDragDropOperation>(InOperation);
	UItemObjectData* ItemData = Cast<UItemObjectData>(Operation->Payload);

	//인벤토리로 돌아감
	if (ItemData->IsValid())
	{
		if (ItemData->Type == EItemObjectType::Inventory)
		{
			FTile tile;
			tile.X = ItemData->position_x;
			tile.Y = ItemData->position_y;

			mInvenComponent->AddItemAt(ItemData, mInvenComponent->TileToIndex(tile));

			mInvenComponent->SetInventoryPacket(ItemData, EInventoryType::Update);
		}
		if(ItemData->Type==EItemObjectType::Equipment)
		{

		}
	}
	return false;
}

void UUWInvenFrame::Init(UACInventoryComponent* InvenComponent)
{
	mInvenComponent = InvenComponent;
}
