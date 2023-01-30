// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_EditBox.h"
#include <Components/EditableTextBox.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>

void UW_EditBox::NativeConstruct()
{
	Super::NativeConstruct();

	mTitleText			= Cast<UTextBlock>(GetWidgetFromName(TEXT("mTitleText")));
	mConfirmButtonText	= Cast<UTextBlock>(GetWidgetFromName(TEXT("mConfirmButtonText")));
	mEditbox			= Cast<UEditableTextBox>(GetWidgetFromName(TEXT("mEditbox")));
	mConfirmButton		= Cast<UButton>(GetWidgetFromName(TEXT("mConfirmButton")));

	if (mEditbox != nullptr)
	{
		mEditbox->OnTextChanged.AddUniqueDynamic(this, &UW_EditBox::Committed_Editbox);
	}

	if (mConfirmButton != nullptr)
	{
		mConfirmButton->OnClicked.AddUniqueDynamic(this, &UW_EditBox::Click_Confirm);
		EnableButton();
	}
}

void UW_EditBox::NativeDestruct()
{
	bool isBound = mConfirmDelegate.IsBound();
	if (false == isBound)
	{
		return;
	}
}

void UW_EditBox::Committed_Editbox(const FText& inEditValue)
{
	mEditValue = inEditValue.ToString();
	EnableButton();
}

void UW_EditBox::SetEditHint(const FText& inHint)
{
	if (mEditbox != nullptr)
	{
		mEditbox->SetHintText(inHint);
	}
}

void UW_EditBox::SetEditTitleText(const FText& inTitle)
{
	if (mTitleText != nullptr)
	{
		mTitleText->SetText(inTitle);
	}
}

void UW_EditBox::SetConfrimButtonText(const FText& inButtonText)
{
	if (mConfirmButtonText != nullptr)
	{
		mConfirmButtonText->SetText(inButtonText);
	}
}

void UW_EditBox::Click_Confirm()
{
	bool isBound = mConfirmDelegate.IsBound();
	if (false == isBound)
	{
		return;
	}

	bool isEmpty = mEditValue.IsEmpty();
	if (true == isEmpty)
	{
		return;
	}

	mConfirmDelegate.Execute(mEditValue);

}

void UW_EditBox::EnableButton()
{
	if (false == mEditValue.IsEmpty())
	{
		mConfirmButton->SetBackgroundColor(mButtonActiveColor);
		mConfirmButton->SetIsEnabled(true);
	}
	else
	{
		mConfirmButton->SetBackgroundColor(mButtonDeactivationColor);
		mConfirmButton->SetIsEnabled(false);
	}
}
