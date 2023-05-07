// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/Game/Inventory/UWInventory.h"

void UUWInventory::NativePreConstruct()
{
	Super::NativePreConstruct();

	Grid_Inventory = Cast<UUWGridInventory>(GetWidgetFromName(TEXT("BP_UWInventoryStore")));
	if (Grid_Inventory == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("111111111111 Fail"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("22222222222 Success"));
	}
}

void UUWInventory::NativeConstruct()
{
	Super::NativeConstruct();



	
}

void UUWInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UE_LOG(LogTemp, Warning, TEXT("Call UWInven NativeOnInitialized"));

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UUWInventory::DelayInit, 0.01f, false);
}

void UUWInventory::DelayInit()
{
	UE_LOG(LogTemp, Warning, TEXT("Call UWInven DelayInit"));
	/*
	UWidget* InvenWidget = GetWidgetFromName(TEXT("BP_UWInventoryStore"));
	if (InvenWidget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("DelayInit UWidget GetWidgetFromName Fail"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DelayInit UWidget GetWidgetFromName Success"));
	}

	GridInventory = Cast<UUWGridInventory>(InvenWidget);
	*/

	/*
	if (ACInventory != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWInven ACInventory exist"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UWInven ACInventory dosen't exist"));
	}
	*/
	/*
	if (GridInventory != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWInven GridInven exist"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UWInven GridInven dosen't exist"));
	}
	
	if (GridBorder != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWInven GridBorder exist"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UWInven GridBorder dosen't exist"));
	}*/
	
	//GridInventory->ACInventory = ACInventory;
	//GridInventory->TileSize = TileSize;
	//GridInventory->testInit();
}
