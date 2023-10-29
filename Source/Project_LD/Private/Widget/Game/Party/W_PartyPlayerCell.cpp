// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Party/W_PartyPlayerCell.h"
#include <Struct/Game/CharacterDatas.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Components/Image.h>

#include <Framework/Game/PS_Game.h>
#include <NetworkController.h>
#include <NetworkGameMode.h>

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

void UW_PartyPlayerCell::NativeDestruct()
{
	Super::NativeDestruct();

	if (mActionButtonDelegateA.IsBound())
	{
		mActionButtonDelegateA.Unbind();
	}
	if (mActionButtonDelegateB.IsBound())
	{
		mActionButtonDelegateB.Unbind();
	}
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

	this->mRemoteID = inRemoteID;
}

void UW_PartyPlayerCell::SetListType(const bool& inIsSelf,  const int64& inLeaderRemoteID, const EPartyListType& inPartyListType)
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

	APlayerController* owningController = GetOwningPlayer();
	if (nullptr == owningController)
	{
		return;

	}

	APS_Game* playerState = owningController->GetPlayerState<APS_Game>();
	if (nullptr == playerState)
	{
		return;

	}

	bool isLeader	= inLeaderRemoteID == this->mRemoteID;
	bool ownerLeader = inLeaderRemoteID == playerState->GetRemoteID();

	if (ownerLeader)
	{
		if (inIsSelf)
		{
			//자신 리더O 리더O 본인O	리더 문장O, 팀장 위임X, 파티 퇴장O
			mLeaderImage->SetVisibility(ESlateVisibility::Visible);
			mActionButtonA->SetVisibility(ESlateVisibility::Hidden);
			mActionButtonB->SetVisibility(ESlateVisibility::Visible);
		}
		else if (!inIsSelf)
		{
			//자신 리더O 리더O 본인X	리더 문장X, 팀장 위임O, 파티 퇴장O
			mLeaderImage->SetVisibility(ESlateVisibility::Hidden);
			mActionButtonA->SetVisibility(ESlateVisibility::Visible);
			mActionButtonB->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		if (!isLeader && inIsSelf)
		{
			//자신 리더X 리더X 본인O	리더 문장X, 팀장 위임X, 파티 퇴장O
			mLeaderImage->SetVisibility(ESlateVisibility::Hidden);
			mActionButtonA->SetVisibility(ESlateVisibility::Hidden);
			mActionButtonB->SetVisibility(ESlateVisibility::Visible);
		}
		else if (isLeader && !inIsSelf)
		{
			//자신 리더X 리더O 본인X 리더 문장O, 팀장 위임X, 파티 퇴장X
			mLeaderImage->SetVisibility(ESlateVisibility::Visible);
			mActionButtonA->SetVisibility(ESlateVisibility::Hidden);
			mActionButtonB->SetVisibility(ESlateVisibility::Hidden);
		}
		else if (!isLeader && !inIsSelf)
		{
			//자신 리더X 리더X 본인X	리더 문장X, 팀장 위임X, 파티 퇴장X
			mLeaderImage->SetVisibility(ESlateVisibility::Hidden);
			mActionButtonA->SetVisibility(ESlateVisibility::Hidden);
			mActionButtonB->SetVisibility(ESlateVisibility::Hidden);
		}
	}

}

const int64& UW_PartyPlayerCell::GetRemoteID()
{
	return mRemoteID;
}
