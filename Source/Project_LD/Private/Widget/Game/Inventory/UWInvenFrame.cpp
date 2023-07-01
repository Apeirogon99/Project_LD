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
	UItemObjectData* ItemObjectData = Cast<UItemObjectData>(Operation->Payload);

	//인벤토리로 돌아감
	if (IsValid(ItemObjectData))
	{
		if (ItemObjectData->IsValid())
		{
			if (ItemObjectData->GetType() == EItemObjectType::Inventory)
			{
				//인벤토리에서 온 경우 인벤토리로 재 전송
				FTile tile;
				tile.X = ItemObjectData->GetPositionX();
				tile.Y = ItemObjectData->GetPositionY();

				mInvenComponent->AddItemAt(ItemObjectData, mInvenComponent->TileToIndex(tile));

				mInvenComponent->SetInventoryPacket(ItemObjectData, EInventoryType::Update);
			}
			else if (ItemObjectData->GetType() == EItemObjectType::Equipment)
			{
				//장비창에서 왔다면 해당 장비창으로 재 전송
				int Index = ItemObjectData->GetItemData().GetCategoryID() - 1;

				mEquipmentComponent->GetEquipmentObjectData()[Index] = ItemObjectData;
				mEquipmentComponent->GetEquipmentWidget()[Index]->ReMakeWidget(ItemObjectData);
			}
		}
	}
	mEquipmentComponent->DropItemWidget();

	return true;
}

bool UUWInvenFrame::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	UDragDropOperation* Operation = Cast<UDragDropOperation>(InOperation);
	UItemObjectData* ItemObjectData = Cast<UItemObjectData>(Operation->Payload);
	
	if (IsValid(ItemObjectData))
	{
		if (ItemObjectData->IsValid())
		{
			mEquipmentComponent->CanItemDropWidgetCheck(ItemObjectData);
		}
	}

	return true;
}

void UUWInvenFrame::Init(UACInventoryComponent* InvenComponent, UACEquipment* EquipmentComponent)
{
	mInvenComponent = InvenComponent;
	mEquipmentComponent = EquipmentComponent;

	if (mInvenComponent == nullptr)
	{
		return;
	}
	if (mEquipmentComponent == nullptr)
	{
		return;
	}
}
