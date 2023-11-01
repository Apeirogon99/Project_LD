// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_Notification.h"
#include <Widget/Handler/ClientHUD.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>


void UW_Notification::NativeConstruct()
{
	Super::NativeConstruct();

	mTitleText			= Cast<UTextBlock>(GetWidgetFromName(TEXT("mTitleText")));
	mNotificationText	= Cast<UTextBlock>(GetWidgetFromName(TEXT("mNotificationText")));
	mConfirmButtonText	= Cast<UTextBlock>(GetWidgetFromName(TEXT("mConfirmButtonText")));
	mConfirmButton		= Cast<UButton>(GetWidgetFromName(TEXT("mConfirmButton")));

	if (mConfirmButton != nullptr)
	{
		mConfirmButton->SetBackgroundColor(mButtonActiveColor);
		mConfirmButton->SetIsEnabled(true);
		mConfirmButton->OnClicked.AddUniqueDynamic(this, &UW_Notification::Click_Confirm);
	}
}

void UW_Notification::NativeDestruct()
{
	Super::NativeDestruct();

	bool isBound = mNotificationDelegate.IsBound();
	if (false == isBound)
	{
		return;
	}

	mNotificationDelegate.Unbind();

	if (mConfirmButton->OnClicked.IsBound())
	{
		mConfirmButton->OnClicked.Clear();
	}
}

void UW_Notification::SetNotification(const FString& inNotification)
{
	if (mNotificationText != nullptr)
	{
		FText notification = FText::FromString(inNotification);
		mNotificationText->SetText(notification);
	}

}

void UW_Notification::SetTitle(const FString& inTitle)
{
	if (mTitleText != nullptr)
	{
		FText title = FText::FromString(inTitle);
		mTitleText->SetText(title);
	}
}

void UW_Notification::SetButtonText(const FString& inButtonText)
{
	if (mConfirmButtonText != nullptr)
	{
		FText buttonText = FText::FromString(inButtonText);
		mConfirmButtonText->SetText(buttonText);
	}
}

void UW_Notification::Click_Confirm()
{
	bool isBound = mNotificationDelegate.IsBound();
	if (true == isBound)
	{
		mNotificationDelegate.Execute();
	}

	//AClientHUD* clientHUD = Cast<AClientHUD>(GetOwningPlayer()->GetHUD());
	//clientHUD->CleanWidgetFromName("Notification");
}
