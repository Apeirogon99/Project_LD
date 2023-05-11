// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/Game/Inventory/UWInventory.h"

void UUWInventory::NativeConstruct()
{
	Super::NativeConstruct();

	GridInventory = this->WidgetTree->FindWidget(FName(TEXT("BW_GridInventory")));
	if (GridInventory != nullptr)
	{
		UUWGridInventory* GridInven = Cast<UUWGridInventory>(GridInventory);
		GridInven->Init(ACInventory,TileSize);
	}
}

void UUWInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUWInventory::NativeDestruct()
{
	Super::NativeDestruct();
}