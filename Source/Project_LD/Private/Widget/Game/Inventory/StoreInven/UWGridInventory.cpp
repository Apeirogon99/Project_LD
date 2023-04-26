// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Inventory/StoreInven/UWGridInventory.h"

void UUWGridInventory::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUWGridInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUWGridInventory::Init(UACInventoryComponent* InventoryComponent, float Size)
{
	ACInventory = InventoryComponent;
	SetTileSize(Size);

	Setting();
}
