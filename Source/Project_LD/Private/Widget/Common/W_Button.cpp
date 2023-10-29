// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_Button.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

void UW_Button::NativeConstruct()
{
	Super::NativeConstruct();

	mButton = Cast<UButton>(GetWidgetFromName(TEXT("mButton")));

	mButtonText = Cast<UTextBlock>(GetWidgetFromName(TEXT("mButtonText")));

	if (mButton != nullptr)
	{
		mButton->OnClicked.AddDynamic(this, &UW_Button::Click_Button);
	}
}

void UW_Button::NativeDestruct()
{
	Super::NativeDestruct();

	bool isBound = mButtonDelegate.IsBound();
	if (false == isBound)
	{
		return;
	}

	mButtonDelegate.Unbind();
}

void UW_Button::SetText(const FString& inText)
{
	if (mButtonText != nullptr)
	{
		FText text = FText::FromString(inText);
		mButtonText->SetText(text);
	}
}

void UW_Button::Click_Button()
{
	bool isBound = mButtonDelegate.IsBound();
	if (true == isBound)
	{
		mButtonDelegate.Execute();
	}
}
