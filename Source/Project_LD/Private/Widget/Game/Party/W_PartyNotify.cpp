// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Party/W_PartyNotify.h"
#include <Components/TextBlock.h>

void UW_PartyNotify::NativeConstruct()
{
	Super::NativeConstruct();

	mNotifyParty = Cast<UTextBlock>(GetWidgetFromName(TEXT("mNotifyParty")));
}

void UW_PartyNotify::SetNotifyParty(const FString& inPlayerName, const int32& inAction)
{
	FString tempText;
	tempText.Append(inPlayerName);
	if (inAction == 1)
	{
		mNotifyParty->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
		tempText.Append(TEXT("님이 파티를 요청 하였습니다"));
	}
	else if (inAction == 2)
	{
		mNotifyParty->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
		tempText.Append(TEXT("님이 파티를 응답을 수락 하였습니다"));
	}
	else if (inAction == 3)
	{
		mNotifyParty->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
		tempText.Append(TEXT("님이 파티를 응답을 거절 하였습니다"));
	}
	else if (inAction == 4)
	{
		mNotifyParty->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
		tempText.Append(TEXT("님이 파티를 참가 하였습니다"));
	}
	else if (inAction == 5)
	{
		mNotifyParty->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
		tempText.Append(TEXT("님이 파티를 탈퇴 하였습니다"));
	}
	else
	{
		return;
	}

	FText newNotiyFriend = FText::FromString(tempText);
	mNotifyParty->SetText(newNotiyFriend);

	OnNotifyParty(inAction);
}

int32 UW_PartyNotify::OnNotifyParty_Implementation(int32 inAction)
{
	return inAction;
}
