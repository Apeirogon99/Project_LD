// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Friend/W_NotifyFriend.h"
#include <Components/TextBlock.h>

void UW_NotifyFriend::NativeConstruct()
{
	Super::NativeConstruct();

	mNotifyFriend = Cast<UTextBlock>(GetWidgetFromName(TEXT("mNotifyFriend")));
}

void UW_NotifyFriend::NativeDestruct()
{
	Super::NativeDestruct();
}

void UW_NotifyFriend::SetNotifyFriend(const FString& inPlayerName, const bool& inConnect)
{
	FString tempText;
	tempText.Append(inPlayerName);
	if (inConnect)
	{
		mNotifyFriend->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
		tempText.Append(TEXT("님이 접속을 하였습니다"));
	}
	else
	{
		mNotifyFriend->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
		tempText.Append(TEXT("님이 접속을 종료하였습니다"));
	}

	FText newNotiyFriend = FText::FromString(tempText);
	mNotifyFriend->SetText(newNotiyFriend);

	OnNotifyFriend();
}

void UW_NotifyFriend::OnNotifyFriend_Implementation()
{
}
