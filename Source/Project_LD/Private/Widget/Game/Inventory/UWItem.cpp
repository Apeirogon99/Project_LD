// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Inventory/UWItem.h"

#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"

#include "TimerManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Kismet/GameplayStatics.h"

void UUWItem::NativeConstruct()
{
	Super::NativeConstruct();

	BackgroundSizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("BackgroundSizeBox")));
	BackgroundBorder = Cast<UBorder>(GetWidgetFromName(TEXT("BackgroundBorder")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));

	bIsFocusable = true;

	mIsEnter = false;

	ItemImage->SetBrushFromTexture(mItemObjectData->ItemData.icon);
}

void UUWItem::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	mItemObjectData = NewObject<UItemObjectData>();

	FTimerHandle InitTimer;
	GetWorld()->GetTimerManager().SetTimer(InitTimer, this, &UUWItem::Refresh, 0.001f, false);
}

void UUWItem::NativeDestruct()
{
	Super::NativeDestruct();

	if (OnRemoved.IsBound())
	{
		OnRemoved.Clear();
	}
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

	DragDropOperation->Payload = mItemObjectData;
	DragDropOperation->DefaultDragVisual = this;
	DragDropOperation->Pivot = EDragPivot::CenterCenter;

	if (OnRemoved.IsBound() == true)
	{
		OnRemoved.Broadcast(mItemObjectData);
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
	mIsEnter = true;
	return Reply.NativeReply;
}

FReply UUWItem::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	mIsEnter = false;
	return FReply::Handled();
}

void UUWItem::Refresh()
{
	if (mItemObjectData->rotation)
	{
		ItemImage->SetRenderTransformAngle(90.0f);
	}
	else
	{
		ItemImage->SetRenderTransformAngle(0.0f);
	}

	mSize.X = mItemObjectData->GetSize().X * mTileSize;
	mSize.Y = mItemObjectData->GetSize().Y * mTileSize;

	BackgroundSizeBox->SetWidthOverride(mSize.X);
	BackgroundSizeBox->SetHeightOverride(mSize.Y);

	UCanvasPanelSlot* ImageCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ItemImage);
	if (ImageCanvasSlot)
	{
		ImageCanvasSlot->SetSize(mSize*0.7f);
	}
}

void UUWItem::Rotate()
{
	mItemObjectData->Rotate();
}
