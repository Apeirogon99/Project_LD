// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/Inventory/UWInventory.h"
#include "Game/Inventory/StoreInven/UWGridInventory.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/DragDropOperation.h"

#include <Game/PS_Game.h>
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

	//아이템 소환
	 
	return false;
}

void UUWInventory::InitInventory(APS_Game* PlayerState, float TileSize)
{
	mTileSize = TileSize;
	mPlayerState = PlayerState;

	GridInventory = this->WidgetTree->FindWidget(FName(TEXT("BW_GridInventory")));
	if (GridInventory != nullptr)
	{
		if (IsValid(mPlayerState))
		{
			UUWGridInventory* GridInven = Cast<UUWGridInventory>(GridInventory);
			GridInven->Init(mPlayerState, mTileSize);
		}
	}
}
