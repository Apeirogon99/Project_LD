// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Item/W_ItemSpace.h"
#include "Widget/Game/Inventory/UWItem.h"

#include "Blueprint/DragDropOperation.h"

#include "Components/CanvasPanel.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"

#include <GameDatas.h>

void UW_ItemSpace::NativePreConstruct()
{
	Super::NativePreConstruct();

	TSubclassOf<UUWItem> ImageWidgetAsset = StaticLoadClass(UUWItem::StaticClass(), NULL, TEXT("WidgetBlueprint'/Game/Blueprint/Widget/Game/Inventory/BW_Item.BW_Item_C'"));
	if (ImageWidgetAsset)
	{
		mImageAsset = ImageWidgetAsset;
	}

	ImgSlotFrame = Cast<UImage>(GetWidgetFromName(TEXT("ImgSlotFrame")));
	ImgSlot = Cast<UImage>(GetWidgetFromName(TEXT("ImgSlot")));

	SlotSizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("SlotSizeBox")));
	if (SlotSizeBox)
	{
		SlotSizeBox->SetWidthOverride(mSizeX);
		SlotSizeBox->SetHeightOverride(mSizeY);
	}
}

bool UW_ItemSpace::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	/*
	UDragDropOperation* Operation = Cast<UDragDropOperation>(InOperation);
	if (Operation)
	{
		UItemObjectData* ItemData = Cast<UItemObjectData>(Operation->Payload);
		if (ItemData)
		{
			if (ItemData->IsValid())
			{
				UUWItem* ItemImageWidget = Cast<UUWItem>(CreateWidget(GetWorld(), mImageAsset));
				if (ItemImageWidget)
				{
					//ItemImageWidget->
				}
			}
		}
	}*/
	return false;
}
