// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Inventory/UWInvenFrame.h"
#include "Widget/Game/Item/W_ItemSpace.h"
#include "Blueprint/DragDropOperation.h"

#include <Component/ACEquipment.h>
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
	UItemObjectData* ItemObejctData = Cast<UItemObjectData>(Operation->Payload);

	//인벤토리로 돌아감
	if (ItemObejctData->IsValid())
	{
		if (ItemObejctData->Type == EItemObjectType::Inventory)
		{
			FTile tile;
			tile.X = ItemObejctData->position_x;
			tile.Y = ItemObejctData->position_y;

			mInvenComponent->AddItemAt(ItemObejctData, mInvenComponent->TileToIndex(tile));

			mInvenComponent->SetInventoryPacket(ItemObejctData, EInventoryType::Update);
		}
		else if(ItemObejctData->Type==EItemObjectType::Equipment)
		{
			mEquipmentComponent->mEquipmentData[ItemObejctData->ItemData.category_id - 1] = ItemObejctData;
			mEquipmentComponent->mEquipmentWidget[ItemObejctData->ItemData.category_id - 1]->ReMakeWidget(ItemObejctData);
		}
	}

	return true;
}

void UUWInvenFrame::Init(UACInventoryComponent* InvenComponent, UACEquipment* EquipmentComponent)
{
	mInvenComponent = InvenComponent;
	mEquipmentComponent = EquipmentComponent;
}
