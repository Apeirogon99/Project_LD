// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Friend/W_FriendCell.h"
#include <Struct/Game/CharacterDatas.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Components/Image.h>

void UW_FriendCell::NativeConstruct()
{
	Super::NativeConstruct();

	mPlayerName			= Cast<UTextBlock>(GetWidgetFromName(TEXT("mPlayerName")));
	mPlayerInfo			= Cast<UTextBlock>(GetWidgetFromName(TEXT("mPlayerInfo")));

	mActionButton		= Cast<UButton>(GetWidgetFromName(TEXT("mActionButton")));

	mConnectStateImage	= Cast<UImage>(GetWidgetFromName(TEXT("mConnectStateImage")));
	mActionImage		= Cast<UImage>(GetWidgetFromName(TEXT("mActionImage")));

	if (mActionButton != nullptr)
	{
		mActionButton->OnClicked.AddUniqueDynamic(this, &UW_FriendCell::Click_ActionButton);
	}
}

void UW_FriendCell::Click_ActionButton()
{
	bool isBound = mActionButtonDelegate.IsBound();
	if (true == isBound)
	{
		mActionButtonDelegate.Execute();
	}
}

void UW_FriendCell::SetPlayerName(const FString& inPlayerName)
{
	FText netText = FText::FromString(inPlayerName);
	mPlayerName->SetText(netText);
	mName = inPlayerName;
}

void UW_FriendCell::SetPlayerInfo(const int32& inLevel, const int32& inClass, const int32& inLocale, const bool& inVisuble)
{
	FString tempText;
	tempText.Append(FString::FromInt(inLevel));
	tempText.Append(TEXT("레벨 "));

	ECharacterClass characterClass = StaticCast<ECharacterClass>(inClass);
	switch (characterClass)
	{
	case ECharacterClass::None:
		tempText.Append(TEXT("미지정"));
		break;
	case ECharacterClass::Warrior:
		tempText.Append(TEXT("전사"));
		break;
	case ECharacterClass::Wizard:
		tempText.Append(TEXT("마법사"));
		break;
	default:
		break;
	}

	tempText.Append(TEXT(" - "));

	//TODO: 데이터 집어 넣어야함
	tempText.Append(TEXT("모험가의 마을"));

	FText netText = FText::FromString(tempText);
	mPlayerInfo->SetText(netText);
}

void UW_FriendCell::SetConnectStateImage(const EConnectState& inConnectState, const bool& inVisuble)
{
	switch (inConnectState)
	{
	case EConnectState::None:
		break;
	case EConnectState::Connect:
		mConnectStateImage->SetBrushFromTexture(mConnectState);
		break;
	case EConnectState::Away:
		mConnectStateImage->SetBrushFromTexture(mAwayState);
		break;
	case EConnectState::DisConnect:
		mConnectStateImage->SetBrushFromTexture(mDisConnectState);
		break;
	default:
		break;
	}

	if (inVisuble)
	{
		mConnectStateImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		mConnectStateImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UW_FriendCell::SetActionImage(const EActionState& inActionState)
{
	switch (inActionState)
	{
	case EActionState::None:
		break;
	case EActionState::Invite:
		mActionImage->SetBrushFromTexture(mInvite);
		break;
	case EActionState::Request:
		mActionImage->SetBrushFromTexture(mRequest);
		break;
	case EActionState::Block:
		mActionImage->SetBrushFromTexture(mBlock);
		break;
	default:
		break;
	}
}

const FString& UW_FriendCell::GetPlayerName()
{
	return mName;
}
