// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Party/W_PartyPlayerInfo.h"
#include <Struct/Game/CharacterDatas.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Components/Image.h>

void UW_PartyPlayerInfo::NativeConstruct()
{
	Super::NativeConstruct();

	mLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("mLevel")));
	mName = Cast<UTextBlock>(GetWidgetFromName(TEXT("mName")));

	mClassImage = Cast<UImage>(GetWidgetFromName(TEXT("mClassImage")));
	mLeaderImage = Cast<UImage>(GetWidgetFromName(TEXT("mLeaderImage")));
}

void UW_PartyPlayerInfo::NativeDestruct()
{
}

void UW_PartyPlayerInfo::SetPlayerInfo(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsLeader)
{
	FString tempText;
	tempText.Append(FString::FromInt(inLevel));
	tempText.Append(TEXT("레벨"));
	FText netText = FText::FromString(tempText);

	mLevel->SetText(netText);
	mName->SetText(FText::FromString(inPlayerName));

	ECharacterClass characterClass = StaticCast<ECharacterClass>(inClass);
	switch (characterClass)
	{
	case ECharacterClass::None:
		break;
	case ECharacterClass::Warrior:
		mClassImage->SetBrushFromTexture(mWarriorClassTexture);
		break;
	case ECharacterClass::Wizard:
		mClassImage->SetBrushFromTexture(mWizardClassTexture);
		break;
	default:
		break;
	}

	if (inIsLeader)
	{
		mLeaderImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		mLeaderImage->SetVisibility(ESlateVisibility::Hidden);
	}

	mRemoteID = inRemoteID;
}

const int64& UW_PartyPlayerInfo::GetRemoteID()
{
	return mRemoteID;
}
