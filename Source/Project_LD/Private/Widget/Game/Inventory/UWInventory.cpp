// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Inventory/UWInventory.h"

void UUWInventory::NativeConstruct()
{
	Super::NativeConstruct();

	InventoryStore = Cast<UUWGridInventory>(GetWidgetFromName(TEXT("InventoryStore")));
}

void UUWInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UUWInventory::DelayInit, 0.01f, false);
}

void UUWInventory::DelayInit()
{
	//InventoryStore->Init(ACInventory, TileSize);
	if (ACInventory != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWInven ACInventory exist"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UWInven ACInventory dosen't exist"));
	}
}
