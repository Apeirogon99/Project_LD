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

void UW_PartyPlayerCell::SetListType(const bool& inIsSelf, const EPartyListType& inPartyListType, const bool& inIsLeader)
{

	if (EPartyListType::RequestList == inPartyListType)
	{
		mLeaderImage->SetVisibility(ESlateVisibility::Hidden);
		mActionImageA->SetBrushFromTexture(mAcceptTexture);
		mActionImageB->SetBrushFromTexture(mCancleTexture);
		return;
	}
	else if(EPartyListType::PlayerList == inPartyListType)
	{
		mActionImageA->SetBrushFromTexture(mLeaderTexture);
		mActionImageB->SetBrushFromTexture(mKickOutTexture);
	}
	else
	{
		return;
	}

	if (inIsLeader)
	{
		mLeaderImage->SetVisibility(ESlateVisibility::Visible);

		if (inIsSelf)
		{
			//리더이면서 본인이면 파티위임 불가능, 탈퇴 가능
			mActionButtonA->SetVisibility(ESlateVisibility::Hidden);
			mActionButtonB->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			//리더이면서 본인이 아니면 파티위임 가능, 탈퇴 가능
			mActionButtonA->SetVisibility(ESlateVisibility::Visible);
			mActionButtonB->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		mLeaderImage->SetVisibility(ESlateVisibility::Hidden);

		if (inIsSelf)
		{
			//리더가 아니고 본인이라면 파티위임 불가능, 탈퇴 가능
			mActionButtonA->SetVisibility(ESlateVisibility::Hidden);
			mActionButtonB->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			//리더가 아니고 본인이 아니면 파티위임 불가능, 탈퇴 불가능
			mActionButtonA->SetVisibility(ESlateVisibility::Hidden);
			mActionButtonB->SetVisibility(ESlateVisibility::Hidden);
		}
	}

}

const int64& UW_PartyPlayerCell::GetRemoteID()
{
	return mRemoteID;
}
