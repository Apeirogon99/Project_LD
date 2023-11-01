// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Chat/W_ChatBox.h"
#include <Components/TextBlock.h>

void UW_ChatBox::NativeConstruct()
{
	Super::NativeConstruct();

	mChatLog		= Cast<UTextBlock>(GetWidgetFromName(TEXT("mChatLog")));

	mChatType		= EChat::Chat_Unspecified;
}

void UW_ChatBox::NativeDestruct()
{
	Super::NativeDestruct();
}

void UW_ChatBox::SetChatBox(const FString& inPlayerName, const FString& inMessage, const EChat& inChatType)
{

	switch (inChatType)
	{
	case EChat::Chat_World:
		mChatLog->SetColorAndOpacity(FSlateColor(FLinearColor::Gray));
		break;
	case EChat::Chat_Party:
		mChatLog->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
		break;
	case EChat::Chat_Friend:
		mChatLog->SetColorAndOpacity(FSlateColor(FLinearColor(0.8f, 0.2f, 1.0f)));
		break;
	default:
		return;
		break;
	}

	FString tempChatLog;
	tempChatLog.Append(inPlayerName);
	tempChatLog.Append(TEXT(" : "));
	tempChatLog.Append(inMessage);

	FText newChatLog = FText::FromString(tempChatLog);
	mChatLog->SetText(newChatLog);
	mChatType = inChatType;
}

const EChat& UW_ChatBox::GetChatType() const
{
	return mChatType;
}
