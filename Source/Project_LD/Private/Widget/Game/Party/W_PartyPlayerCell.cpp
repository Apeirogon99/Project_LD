// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Party/W_PartyPlayerCell.h"
#include <Struct/Game/CharacterDatas.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Components/Image.h>

void UW_PartyPlayerCell::NativeConstruct()
{
	Super::NativeConstruct();

	mPlayerInfo = Cast<UTextBlock>(GetWidgetFromName(TEXT("mPlayerInfo")));

	mActionButtonA	= Cast<UButton>(GetWidgetFromName(TEXT("mActionButtonA")));
	mActionButtonB	= Cast<UButton>(GetWidgetFromName(TEXT("mActionButtonB")));

	mClassImage		= Cast<UImage>(GetWidgetFromName(TEXT("mClassImage")));
	mActionImageA	= Cast<UImage>(GetWidgetFromName(TEXT("mActionImageA")));
	mActionImageB	= Cast<UImage>(GetWidgetFromName(TEXT("mActionImageB")));
	mLeaderImage	= Cast<UImage>(GetWidgetFromName(TEXT("mLeaderImage")));

	if (mActionButtonA != nullptr)
	{
		mActionButtonA->OnClicked.AddUniqueDynamic(this, &UW_PartyPlayerCell::Click_ActionButtonA);
	}

	if (mActionButtonB != nullptr)
	{
		mActionButtonB->OnClicked.AddUniqueDynamic(this, &UW_PartyPlayerCell::Click_ActionButtonB);
	}

	mRemoteID = 0;
}

void UW_PartyPlayerCell::Click_ActionButtonA()
{
	bool isBound = mActionButtonDelegateA.IsBound();
	if (true == isBound)
	{
		mActionButtonDelegateA.Execute();
	}
}

void UW_PartyPlayerCell::Click_ActionButtonB()
{
	bool isBound = mActionButtonDelegateB.IsBound();
	if (true == isBound)
	{
		mActionButtonDelegateB.Execute();
	}
}

void UW_PartyPlayerCell::SetPlayerInfo(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName)
{
	FString tempText;
	tempText.Append(FString::FromInt(inLevel));
	tempText.Append(TEXT("레벨 "));

	ECharacterClass characterClass = StaticCast<ECharacterClass>(inClass);
	switch (characterClass)
	{
	case ECharacterClass::None:
		tempText.Append(TEXT("미지정 "));
		//
		break;
	case ECharacterClass::Warrior:
		tempText.Append(TEXT("성기사 "));
		mClassImage->SetBrushFromTexture(mWarriorClassTexture);
		break;
	case ECharacterClass::Wizard:
		tempText.Append(TEXT("마법사 "));
		mClassImage->SetBrushFromTexture(mWizardClassTexture);
		break;
	default:
		break;
	}
	tempText.Append(inPlayerName);

	FText netText = FText::FromString(tempText);
	mPlayerInfo->SetText(netText);
	mRemoteID = inRemoteID;
}

void UW_PartyPlayerCell::SetListType(const EPartyListType& inPartyListType, const bool& inVisible)
{
	if (false == inVisible)
	{
		mActionImageA->SetVisibility(ESlateVisibility::Hidden);
		mActionImageB->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	else
	{
		mActionImageA->SetVisibility(ESlateVisibility::Visible);
		mActionImageB->SetVisibility(ESlateVisibility::Visible);
	}

	switch (inPartyListType)
	{
	case EPartyListType::None:
		break;
	case EPartyListType::PlayerList:
		mActionImageA->SetBrushFromTexture(mLeaderTexture);
		mActionImageB->SetBrushFromTexture(mKickOutTexture);
		break;
	case EPartyListType::RequestList:
		mActionImageA->SetBrushFromTexture(mAcceptTexture);
		mActionImageB->SetBrushFromTexture(mCancleTexture);
		break;
	default:
		break;
	}
}

void UW_PartyPlayerCell::SetLeader(const bool& inIsLeader)
{
	if (inIsLeader)
	{
		mLeaderImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		mLeaderImage->SetVisibility(ESlateVisibility::Hidden);
	}
}
