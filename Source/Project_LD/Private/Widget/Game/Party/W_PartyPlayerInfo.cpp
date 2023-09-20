// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Party/W_PartyPlayerInfo.h"
#include <Struct/Game/CharacterDatas.h>
#include <Components/TextBlock.h>
#include <Components/Button.h>
#include <Components/Image.h>
#include <Components/ProgressBar.h>
#include <Components/ScrollBox.h>
#include <GS_Game.h>
#include <PC_Game.h>
#include <GM_Game.h>
#include <Widget/Game/Party/W_PlayerBuffInfo.h>
#include <LDGameInstance.h>


void UW_PartyPlayerInfo::NativeConstruct()
{
	Super::NativeConstruct();

	mLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("mLevel")));
	mName = Cast<UTextBlock>(GetWidgetFromName(TEXT("mName")));

	mClassImage = Cast<UImage>(GetWidgetFromName(TEXT("mClassImage")));
	mLeaderImage = Cast<UImage>(GetWidgetFromName(TEXT("mLeaderImage")));

	mHP = Cast<UProgressBar>(GetWidgetFromName(TEXT("mHP")));
	mMP = Cast<UProgressBar>(GetWidgetFromName(TEXT("mMP")));

	BuffList = Cast<UScrollBox>(GetWidgetFromName(TEXT("BuffList")));
}

void UW_PartyPlayerInfo::NativeDestruct()
{
}

void UW_PartyPlayerInfo::SetPlayerInfo(const int64& inRemoteID, const int64& inLeaderRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsSelf)
{
	AGS_Game* gameState = GetWorld()->GetGameState<AGS_Game>();
	if (nullptr == gameState)
	{
		return;
	}
	AController* controller = gameState->FindPlayerController(inRemoteID);
	if (nullptr == controller)
	{
		return;
	}
	
	ANPS_Game* playerState = controller->GetPlayerState<ANPS_Game>();
	if (nullptr == playerState)
	{
		return;
	}

	mRemoteID = inRemoteID;

	for (int i = 0; i < 3; i++)
	{
		buffArr[i] = 0;
	}

	playerState->OnCharacterHealthChanged.AddUFunction(this, FName(TEXT("UpdateHealthBar")));
	playerState->OnCharacterManaChanged.AddUFunction(this, FName(TEXT("UpdateManaBar")));
	playerState->OnApplyBuffOrDeBuff.AddUFunction(this, FName(TEXT("UpdateBuffInfo")));

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

	if (inRemoteID == inLeaderRemoteID)
	{
		mLeaderImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		mLeaderImage->SetVisibility(ESlateVisibility::Hidden);
	}

	UpdateHealthBar();
	UpdateManaBar();
	UpdateBuffInfo();
}

void UW_PartyPlayerInfo::UpdateHealthBar()
{
	AGS_Game* gameState = GetWorld()->GetGameState<AGS_Game>();
	if (nullptr == gameState)
	{
		return;
	}
	AController* controller = gameState->FindPlayerController(mRemoteID);
	if (nullptr == controller)
	{
		return;
	}

	ANPS_Game* playerState = controller->GetPlayerState<ANPS_Game>();
	if (nullptr == playerState)
	{
		return;
	}

	float CurrentHealthPercent = playerState->GetCharacterStats().GetCurrentStats().GetHealth();
	float MaxHealthPercent = playerState->GetCharacterStats().GetMaxStats().GetHealth();
	if (MaxHealthPercent == 0)
	{
		return;
	}
	float HealthPercent = CurrentHealthPercent / MaxHealthPercent;

	/*
	UE_LOG(LogTemp, Warning, TEXT("Update Character HP ID : %d M HP %f C HP %f Percent %f"),
		mRemoteID, MaxHealthPercent, CurrentHealthPercent, HealthPercent);
		*/
	mHP->SetPercent(HealthPercent);
}

void UW_PartyPlayerInfo::UpdateManaBar()
{
	AGS_Game* gameState = GetWorld()->GetGameState<AGS_Game>();
	if (nullptr == gameState)
	{
		return;
	}
	AController* controller = gameState->FindPlayerController(mRemoteID);
	if (nullptr == controller)
	{
		return;
	}

	ANPS_Game* playerState = controller->GetPlayerState<ANPS_Game>();
	if (nullptr == playerState)
	{
		return;
	}

	float CurrentManaPercent = playerState->GetCharacterStats().GetCurrentStats().GetMana();
	float MaxManaPercent = playerState->GetCharacterStats().GetMaxStats().GetMana();
	if (MaxManaPercent == 0)
	{
		return;
	}
	float ManaPercent = CurrentManaPercent / MaxManaPercent;

	mMP->SetPercent(ManaPercent);
}

void UW_PartyPlayerInfo::UpdateBuffInfo()
{
	ULDGameInstance* Instance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	if (nullptr == Instance)
	{
		return;
	}

	AGS_Game* gameState = GetWorld()->GetGameState<AGS_Game>();
	if (nullptr == gameState)
	{
		return;
	}
	AController* controller = gameState->FindPlayerController(mRemoteID);
	if (nullptr == controller)
	{
		return;
	}

	ANPS_Game* playerState = controller->GetPlayerState<ANPS_Game>();
	if (nullptr == playerState)
	{
		return;
	}

	float C_AttackDamage = playerState->GetCharacterStats().GetCurrentStats().GetAttackDamage();
	float C_Armor = playerState->GetCharacterStats().GetCurrentStats().GetArmor();
	float C_MovementSPeed = playerState->GetCharacterStats().GetCurrentStats().GetMovementSpeed();

	float M_AttackDamage = playerState->GetCharacterStats().GetMaxStats().GetAttackDamage();
	float M_Armor = playerState->GetCharacterStats().GetMaxStats().GetArmor();
	float M_MovementSPeed = playerState->GetCharacterStats().GetMaxStats().GetMovementSpeed();

	UE_LOG(LogTemp, Warning, TEXT("C_Attack %f M_Attack %f"), C_AttackDamage, M_AttackDamage);
	if (C_AttackDamage > M_AttackDamage && buffArr[0] == 0)
	{
		buffArr[0] = 1;
		FBuffData buffdata = *Instance->GetBuffData(0);
		UW_PlayerBuffInfo* childWidget = CreateWidget<UW_PlayerBuffInfo>(this, UW_PlayerBuffInfo::StaticClass());
		if (childWidget)
		{
			UTexture2D* texture = buffdata.GetImage();
			childWidget->mBuffImage->SetBrushFromTexture(texture);

			BuffList->AddChild(childWidget);
		}
	}
	else if (C_AttackDamage < M_AttackDamage)
	{
		buffArr[0] = -1;
		FBuffData buffdata = *Instance->GetBuffData(1);
		UW_PlayerBuffInfo* childWidget = NewObject<UW_PlayerBuffInfo>();
		if (childWidget->mBuffImage)
		{
			
		}
		//->SetBrushFromTexture(buffdata.GetImage());

		BuffList->AddChild(childWidget);
	}
	else
	{
		buffArr[0] = 0;
	}
	/*
	if (C_Armor > M_Armor && buffArr[1] == 0)
	{
		buffArr[1] = 1;
		FBuffData buffdata = *Instance->GetBuffData(2);
		//UW_PlayerBuffInfo* childWidget = NewObject<UW_PlayerBuffInfo>();
		//childWidget->mBuffImage->SetBrushFromTexture(buffdata.GetImage());

		//BuffList->AddChild(childWidget);
	}
	else if (C_Armor < M_Armor)
	{
		buffArr[1] = -1;
		FBuffData buffdata = *Instance->GetBuffData(3);
		UW_PlayerBuffInfo* childWidget = NewObject<UW_PlayerBuffInfo>();
		childWidget->mBuffImage->SetBrushFromTexture(buffdata.GetImage());

		BuffList->AddChild(childWidget);
	}
	else
	{
		buffArr[1] = 0;
	}

	if (C_MovementSPeed > M_MovementSPeed && buffArr[2] == 0)
	{
		buffArr[2] = 1;
		FBuffData buffdata = *Instance->GetBuffData(4);
		UW_PlayerBuffInfo* childWidget = NewObject<UW_PlayerBuffInfo>();
		childWidget->mBuffImage->SetBrushFromTexture(buffdata.GetImage());

		BuffList->AddChild(childWidget);
	}
	else if (C_MovementSPeed < M_MovementSPeed)
	{
		buffArr[2] = -1;
		FBuffData buffdata = *Instance->GetBuffData(5);
		UW_PlayerBuffInfo* childWidget = NewObject<UW_PlayerBuffInfo>();
		childWidget->mBuffImage->SetBrushFromTexture(buffdata.GetImage());

		BuffList->AddChild(childWidget);
	}
	else
	{
		buffArr[2] = 0;
	}*/
}

const int64& UW_PartyPlayerInfo::GetRemoteID()
{
	return mRemoteID;
}
