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
	ItemBackgroundImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemBackgroundImage")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemImage")));

	UTexture2D* Texture2DNormal = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/Common/Tier/T_Normal_Frame.T_Normal_Frame'"));
	UTexture2D* Texture2DRare = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/Common/Tier/T_Rare_Frame.T_Rare_Frame'"));
	UTexture2D* Texture2DEpic = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/Common/Tier/T_Epic_Frame.T_Epic_Frame'"));
	UTexture2D* Texture2DMythic = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/Common/Tier/T_Mythic_Frame.T_Mythic_Frame'"));
	UTexture2D* Texture2DLegendary = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/GameContent/GUI/Common/Tier/T_Legendary_Frame.T_Legendary_Frame'"));

	if (Texture2DNormal)
	{
		mFrameTextureArr.Add(Texture2DNormal);
	}
	if (Texture2DRare)
	{
		mFrameTextureArr.Add(Texture2DRare);
	}
	if (Texture2DEpic)
	{
		mFrameTextureArr.Add(Texture2DEpic);
	}
	if (Texture2DMythic)
	{
		mFrameTextureArr.Add(Texture2DMythic);
	}
	if (Texture2DLegendary)
	{
		mFrameTextureArr.Add(Texture2DLegendary);
	}

	bIsFocusable = true;

	mIsEnter = false;

	ItemBackgroundImage->SetBrushFromTexture(mFrameTextureArr[mItemObjectData->ItemData.tier_id - 1]);
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
