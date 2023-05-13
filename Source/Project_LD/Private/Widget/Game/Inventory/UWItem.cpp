// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Inventory/UWItem.h"
#include "Components/CanvasPanelSlot.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

void UUWItem::NativeConstruct()
{
	Super::NativeConstruct();

	BackgroundSizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("BackgroundSizeBox")));
	BackgroundBorder = Cast<UBorder>(GetWidgetFromName(TEXT("BackgroundBorder")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));
}

void UUWItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FTimerHandle InitTimer;
	GetWorld()->GetTimerManager().SetTimer(InitTimer, this, &UUWItem::Refresh, 0.001f, false);
}

void UUWItem::NativeDestruct()
{
	Super::NativeDestruct();

	OnRemoved.Clear();
}

void UUWItem::Refresh()
{
	Size.X = ItemData.size_x * TileSize;
	Size.Y = ItemData.size_y * TileSize;

	BackgroundSizeBox->SetWidthOverride(Size.X);
	BackgroundSizeBox->SetHeightOverride(Size.Y);

	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(ItemImage->Slot);
	CanvasSlot->SetSize(Size);
}
