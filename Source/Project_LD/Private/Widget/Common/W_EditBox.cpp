// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_EditBox.h"
#include <Components/EditableTextBox.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Widget/Handler/ClientHUD.h>

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

	mConfirmDelegate.Unbind();
}

void UW_EditBox::Committed_Editbox(const FText& inEditValue)
{
	mEditValue = inEditValue.ToString();
	EnableButton();
}

void UW_EditBox::SetEditHint(const FString& inHint)
{
	if (mEditbox != nullptr)
	{
		FText editHint = FText::FromString(inHint);
		mEditbox->SetHintText(editHint);
	}
}

void UW_EditBox::SetEditTitleText(const FString& inTitle)
{
	if (mTitleText != nullptr)
	{
		FText editTitle = FText::FromString(inTitle);
		mTitleText->SetText(editTitle);
	}
}

void UW_EditBox::SetConfrimButtonText(const FString& inButtonText)
{
	if (mConfirmButtonText != nullptr)
	{
		FText buttonText = FText::FromString(inButtonText);
		mConfirmButtonText->SetText(buttonText);
	}
}

void UW_EditBox::Click_Confirm()
{

	bool isEmpty = mEditValue.IsEmpty();
	if (true == isEmpty)
	{
		return;
	}

	bool isBound = mConfirmDelegate.IsBound();
	if (true == isBound)
	{
		mConfirmDelegate.Execute(mEditValue);
	}

	//AClientHUD* clientHUD = Cast<AClientHUD>(GetOwningPlayer()->GetHUD());
	//clientHUD->CleanWidgetFromName("EditBox");

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
