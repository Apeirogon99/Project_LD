// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/Game/Main/W_MainPlayerInfo.h"
#include <Widget/Game/Main/W_ExpBar.h>
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"

#include <Framework/Game/GM_Game.h>
#include <Framework/Game/PC_Game.h>
#include <Framework/Game/PS_Game.h>

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include <Struct/Game/CharacterDatas.h>
#include <LDGameInstance.h>

void UW_MainPlayerInfo::NativeConstruct()
{

	Super::NativeConstruct();

	mExpBar = this->WidgetTree->FindWidget(FName(TEXT("BW_ExpBar")));
	if (mExpBar == nullptr)
	{
		return;
	}

	TB_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Name")));
	if (TB_Name == nullptr)
	{
		return;
	}
}

void UW_MainPlayerInfo::Init()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}

	APC_Game* controller = Cast<APC_Game>(gamemode->GetNetworkController());
	if (nullptr == controller)
	{
		return;
	}

	APS_Game* playerstate = controller->GetPlayerState<APS_Game>();
	if (playerstate == nullptr)
	{
		return;
	}
	
	playerstate->OnCharacterExpChanged.AddUFunction(this, FName(TEXT("UpdateExpBar")));
	
	TB_Name->SetText(FText::FromString(playerstate->GetCharacterData().GetName()));

	UpdateExpBar();
}

void UW_MainPlayerInfo::UpdateExpBar()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}

	APC_Game* controller = Cast<APC_Game>(gamemode->GetNetworkController());
	if (nullptr == controller)
	{
		return;
	}

	APS_Game* playerstate = controller->GetPlayerState<APS_Game>();
	if (playerstate == nullptr)
	{
		return;
	}

	UW_ExpBar* expBar = Cast<UW_ExpBar>(mExpBar);
	if (expBar == nullptr)
	{
		return;
	}

	ULDGameInstance* Instance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	int32 CurrentLevel = playerstate->GetCharacterData().GetLevel();
	FLevelDataTable* leveldata = Instance->GetLevelDataTable(CurrentLevel + 1);
	float nextlevelExp = leveldata->next_experience;
	float ExpBarPercent = playerstate->GetCharacterData().GetExp() / nextlevelExp;

	expBar->ExpBar->SetPercent(ExpBarPercent);
}