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

	bIsFocusable = true;
}

void UUWItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ItemData = NewObject<UItemObjectData>();

	FTimerHandle InitTimer;
	GetWorld()->GetTimerManager().SetTimer(InitTimer, this, &UUWItem::Refresh, 0.001f, false);
}

void UUWItem::NativeDestruct()
{
	Super::NativeDestruct();

	OnRemoved.Clear();
}

void UUWItem::NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseEnter(MyGeometry, MouseEvent);

	BackgroundBorder->SetBrushColor(FLinearColor(0.5f, 0.5f, 0.5f, 0.2f));
}

void UUWItem::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseLeave(MouseEvent);

	BackgroundBorder->SetBrushColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.5f));
}

void UUWItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragDropOperation* DragDropOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	this->SetVisibility(ESlateVisibility::HitTestInvisible);

	DragDropOperation->Payload = ItemData;
	DragDropOperation->DefaultDragVisual = this;
	DragDropOperation->Pivot = EDragPivot::CenterCenter;
	
	if (OnRemoved.IsBound() == true)
	{

		OnRemoved.Broadcast(ItemData);
	}
	RemoveFromParent();
	
	OutOperation = DragDropOperation;
}

FReply UUWItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	FEventReply Reply;
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent,this,EKeys::LeftMouseButton);
	}
	return Reply.NativeReply;
}

void UUWItem::Refresh()
{
	Size.X = ItemData->GetSize().X * TileSize;
	Size.Y = ItemData->GetSize().Y * TileSize;
	
	BackgroundSizeBox->SetWidthOverride(Size.X);
	BackgroundSizeBox->SetHeightOverride(Size.Y);

	UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(ItemImage->Slot);
	CanvasSlot->SetSize(Size);
}

void UUWItem::Rotate()
{
	ItemData->Rotate();
}
