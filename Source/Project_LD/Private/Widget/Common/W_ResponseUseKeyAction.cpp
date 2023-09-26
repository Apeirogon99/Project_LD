// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_ResponseUseKeyAction.h"
#include <Components/TextBlock.h>

void UW_ResponseUseKeyAction::NativeConstruct()
{
	Super::NativeConstruct();

	mMessage = Cast<UTextBlock>(GetWidgetFromName(TEXT("mMessage")));
}

void UW_ResponseUseKeyAction::NativeDestruct()
{
	Super::NativeDestruct();
}

void UW_ResponseUseKeyAction::SetResponseUseKeyAction(const int32& inKey, const FString& inMessage)
{
	if (mMessage != nullptr)
	{
		FText notification = FText::FromString(inMessage);
		mMessage->SetText(notification);
	}
}

void UW_ResponseUseKeyAction::OnActiveAnimation_Implementation()
{
}
