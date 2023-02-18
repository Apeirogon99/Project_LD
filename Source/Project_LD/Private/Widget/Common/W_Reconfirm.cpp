// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_Reconfirm.h"
#include <Components/EditableTextBox.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>

void UW_Reconfirm::NativeConstruct()
{
	Super::NativeConstruct();

	mTitleText				= Cast<UTextBlock>(GetWidgetFromName(TEXT("mTitleText")));
	mReconfirmText			= Cast<UTextBlock>(GetWidgetFromName(TEXT("mReconfirmText")));
	mConfirmButtonText = Cast<UTextBlock>(GetWidgetFromName(TEXT("mConfirmButtonText")));
	mCancleButtonText		= Cast<UTextBlock>(GetWidgetFromName(TEXT("mCancleButtonText")));
	mConfirmButton			= Cast<UButton>(GetWidgetFromName(TEXT("mConfirmButton")));
	mCancleButton			= Cast<UButton>(GetWidgetFromName(TEXT("mCancleButton")));

	if (mConfirmButton != nullptr)
	{
		mConfirmButton->OnClicked.AddUniqueDynamic(this, &UW_Reconfirm::Click_Confirm);
	}

	if (mCancleButton != nullptr)
	{
		mCancleButton->OnClicked.AddUniqueDynamic(this, &UW_Reconfirm::Click_Cancle);
	}

}

void UW_Reconfirm::NativeDestruct()
{
	bool isCancleBound = mCancleDelegate.IsBound();
	if (isCancleBound)
	{
		mCancleDelegate.Unbind();
	}

	bool isConfirmBound = mReConfirmDelegate.IsBound();
	if (isConfirmBound)
	{
		mReConfirmDelegate.Unbind();
	}
}

void UW_Reconfirm::SetTitleText(const FString& inTitle)
{
	FText title = FText::FromString(inTitle);
	if (nullptr != mTitleText)
	{
		mTitleText->SetText(title);
	}
}

void UW_Reconfirm::SetReconfirmText(const FString& inReconfirm)
{
	FText reconfirm = FText::FromString(inReconfirm);
	if (nullptr != mReconfirmText)
	{
		mReconfirmText->SetText(reconfirm);
	}
}

void UW_Reconfirm::SetConfirmButtonText(const FString& inButtonText)
{
	FText buttonText = FText::FromString(inButtonText);
	if (nullptr != mConfirmButtonText)
	{
		mConfirmButtonText->SetText(buttonText);
	}
}

void UW_Reconfirm::SetCancleButtonText(const FString& inButtonText)
{
	FText buttonText = FText::FromString(inButtonText);
	if (nullptr != mCancleButtonText)
	{
		mCancleButtonText->SetText(buttonText);
	}
}

void UW_Reconfirm::Click_Confirm()
{
	bool isBound = mReConfirmDelegate.IsBound();
	if (false == isBound)
	{
		return;
	}

	mReConfirmDelegate.Execute();
}

void UW_Reconfirm::Click_Cancle()
{
	bool isBound = mCancleDelegate.IsBound();
	if (false == isBound)
	{
		return;
	}

	mCancleDelegate.Execute();
}
