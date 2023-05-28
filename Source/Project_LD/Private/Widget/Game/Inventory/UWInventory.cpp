// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/Inventory/UWInventory.h"
#include "Game/Inventory/StoreInven/UWGridInventory.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/DragDropOperation.h"

#include "Component/ACInventoryComponent.h"
#include "Components/Border.h"
#include "Components/BackgroundBlur.h"

#include "Kismet/GameplayStatics.h"

void UUWInventory::NativeConstruct()
{
	Super::NativeConstruct();

	BackgroundBorder = Cast<UBorder>(GetWidgetFromName(TEXT("BackgroundBorder")));
	BackgroundBlur = Cast<UBackgroundBlur>(GetWidgetFromName(TEXT("BackgroundBlur")));
}

void UUWInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUWInventory::NativeDestruct()
{
	Super::NativeDestruct();
}

FReply UUWInventory::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);

	return FReply::Handled();
}

bool UUWInventory::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragDropOperation* Operation = Cast<UDragDropOperation>(InOperation);
	UItemObjectData* ItemData = Cast<UItemObjectData>(Operation->Payload);

	AActor* Owner = mACInventory->GetOwner();
	//아이템 소환
	 
	return false;
}

void UUWInventory::InitInventory(UACInventoryComponent* InventoryComponent, float size)
{
	mACInventory = InventoryComponent;
	this->mTileSize = size;

	GridInventory = this->WidgetTree->FindWidget(FName(TEXT("BW_GridInventory")));
	if (GridInventory != nullptr)
	{
		if (IsValid(mACInventory))
		{
			UUWGridInventory* GridInven = Cast<UUWGridInventory>(GridInventory);
			GridInven->Init(mACInventory, size);
		}
	}
}
