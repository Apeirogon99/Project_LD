// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/Game/Equipment/UWEquipItem.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/SizeBox.h"
#include <Blueprint/WidgetBlueprintLibrary.h>

void UUWEquipItem::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UUWEquipItem::NativeDestruct()
{
	Super::NativeDestruct();

	if (OnEquipItemRemoved.IsBound() == true)
	{
		OnEquipItemRemoved.Unbind();
	}
}

void UUWEquipItem::NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseEnter(MyGeometry, MouseEvent);

	if (BackgroundBorder)
	{
		BackgroundBorder->SetBrushColor(FLinearColor(0.5f, 0.5f, 0.5f, 0.2f));
	}
}

void UUWEquipItem::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseLeave(MouseEvent);

	if (BackgroundBorder)
	{
		BackgroundBorder->SetBrushColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.5f));
	}
}

void UUWEquipItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragDropOperation* DragDropOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	this->SetVisibility(ESlateVisibility::HitTestInvisible);

	DragDropOperation->Payload = mItemObjectData;
	DragDropOperation->DefaultDragVisual = this;
	DragDropOperation->Pivot = EDragPivot::CenterCenter;

	if (mItemObjectData == nullptr)
	{
		return;
	}

	if (OnEquipItemRemoved.IsBound() == true)
	{
		OnEquipItemRemoved.ExecuteIfBound();
	}
	RemoveFromParent();

	OutOperation = DragDropOperation;
}

FReply UUWEquipItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FEventReply Reply;
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	}
	mIsEnter = true;

	return Reply.NativeReply;
}

FReply UUWEquipItem::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	mIsEnter = false;

	return FReply::Handled();
}

void UUWEquipItem::SetImage()
{
	if (IsValid(mItemObjectData))
	{
		if (mItemObjectData->IsValid())
		{
			if (ItemBackgroundImage)
			{
				ItemBackgroundImage->SetBrushFromTexture(mFrameTextureArr[mItemObjectData->ItemData.tier_id - 1]);
			}
			if (ItemImage)
			{
				ItemImage->SetBrushFromTexture(mItemObjectData->ItemData.icon);
			}
		}
	}
}
void UUWEquipItem::SetFrameSize(float X, float Y)
{
	BackgroundSizeBox->SetWidthOverride(X);
	BackgroundSizeBox->SetHeightOverride(Y);
}

void UUWEquipItem::Init()
{
	if (bIsFirst)
	{
		bIsFirst = false;
		BackgroundBorder = Cast<UBorder>(GetWidgetFromName(TEXT("BackgroundBorder")));
		BackgroundSizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("BackgroundSizeBox")));
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

		mIsEnter = false;
	}
}
