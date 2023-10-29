// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_ColorPicker.h"

#include <Blueprint/WidgetLayoutLibrary.h>

#include <Components/EditableTextBox.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Components/Image.h>

#include <Widget/Handler/ClientHUD.h>
#include <Network/NetworkUtils.h>

void UW_ColorPicker::NativeConstruct()
{
	Super::NativeConstruct();

	mDragButton		= Cast<UButton>(GetWidgetFromName(TEXT("mDragButton")));
	mRefreshButton	= Cast<UButton>(GetWidgetFromName(TEXT("mRefreshButton")));
	mRandomButton	= Cast<UButton>(GetWidgetFromName(TEXT("mRandomButton")));
	mPickerButton	= Cast<UButton>(GetWidgetFromName(TEXT("mPickerButton")));


	mPickerTarget	= Cast<UTextBlock>(GetWidgetFromName(TEXT("mPickerTarget")));

	mColorEdit		= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("mColorEdit")));

	mPickerPreviewImage = Cast<UImage>(GetWidgetFromName(TEXT("mPickerPreviewImage")));

	if (mDragButton != nullptr)
	{
		mDragButton->OnPressed.AddUniqueDynamic(this, &UW_ColorPicker::Pressed_Drag);
		mDragButton->OnReleased.AddUniqueDynamic(this, &UW_ColorPicker::Released_Drag);
	}

	if (mRefreshButton != nullptr)
	{
		mRefreshButton->OnClicked.AddUniqueDynamic(this, &UW_ColorPicker::Click_Refresh);
	}

	if (mRandomButton != nullptr)
	{
		mRandomButton->OnClicked.AddUniqueDynamic(this, &UW_ColorPicker::Click_Random);
	}

	if (mPickerButton != nullptr)
	{
		mPickerButton->OnClicked.AddUniqueDynamic(this, &UW_ColorPicker::Click_Picker);
	}

	if (mColorEdit != nullptr)
	{
		mColorEdit->OnTextChanged.AddUniqueDynamic(this, &UW_ColorPicker::Committed_Color);
	}

}

void UW_ColorPicker::NativeDestruct()
{
	Super::NativeDestruct();
}

void UW_ColorPicker::Pressed_Drag()
{
	FVector2D currentMousePoint		= UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2D currentViewportPoint	= RenderTransform.Translation;
	mPressedMousePoint = currentMousePoint - currentViewportPoint;
	UpdateLocation();
}

void UW_ColorPicker::Released_Drag()
{
	if(true == GetWorld()->GetTimerManager().IsTimerActive(mUpdateLocationTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(mUpdateLocationTimerHandle);
	}
}

void UW_ColorPicker::Click_Refresh()
{
	
}

void UW_ColorPicker::Click_Random()
{

}

void UW_ColorPicker::Click_Picker()
{

}

void UW_ColorPicker::Committed_Color(const FText& inEditValue)
{
	
}

void UW_ColorPicker::UpdateLocation()
{
	float WaitTime = 0.01f;
	GetWorld()->GetTimerManager().SetTimer(mUpdateLocationTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			FVector2D currentMousePoint = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

			FWidgetTransform widgetTransform;
			widgetTransform.Translation = currentMousePoint - mPressedMousePoint;
			widgetTransform.Scale		= FVector2D(1, 1);
			widgetTransform.Shear		= FVector2D(0, 0);
			widgetTransform.Angle		= 0.0f;
			SetRenderTransform(widgetTransform);

		}), WaitTime, true);
}

void UW_ColorPicker::SetPickerTarget(const FString& inTarget)
{
	if (mPickerTarget != nullptr)
	{
		FText target = FText::FromString(inTarget);
		mPickerTarget->SetText(target);
	}
}

void UW_ColorPicker::SetPickerPreviewColor(const FLinearColor& inColor)
{
	if (mPickerPreviewImage != nullptr)
	{
		mPickerPreviewImage->SetColorAndOpacity(inColor);
		mLinearColor = inColor;
	}
}

void UW_ColorPicker::SetPickerColor(const FString& inColor)
{
	if (mColorEdit != nullptr)
	{
		FText color = FText::FromString(inColor);
		mColorEdit->SetText(color);
	}
}

const FString& UW_ColorPicker::GetColorString()
{
	return mColorStr;
}

FLinearColor UW_ColorPicker::GetLinearColor()
{
	return mLinearColor;
}

FLinearColor UW_ColorPicker::OnUsed_Implementation(FLinearColor inColor)
{
	return inColor;
}
