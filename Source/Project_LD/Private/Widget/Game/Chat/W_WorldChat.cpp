// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Chat/W_WorldChat.h"
#include <Components/TextBlock.h>

void UW_WorldChat::NativeConstruct()
{
	Super::NativeConstruct();

	mChatLog = Cast<UTextBlock>(GetWidgetFromName(TEXT("mChatLog")));

	mChatTime = 0.0f;
	mIsMessage = false;
}

void UW_WorldChat::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (nullptr == this->GetOwningPlayer())
	{
		return;
	}

	if (true == mIsMessage)
	{
		mChatTime -= InDeltaTime;
		if (mChatTime <= 0.0f)
		{
			mIsMessage = false;

			this->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UW_WorldChat::SetWorldChat(const FString& inPlayerName, const FString& inMessage, const float& inDuration)
{
	FString tempChatLog;
	tempChatLog.Append(inPlayerName);
	tempChatLog.Append(TEXT(" : "));
	tempChatLog.Append(inMessage);

	FText newChatLog = FText::FromString(tempChatLog);
	mChatLog->SetText(newChatLog);

	mChatTime = 3.0f;
	mIsMessage = true;

	this->SetVisibility(ESlateVisibility::Visible);
}
