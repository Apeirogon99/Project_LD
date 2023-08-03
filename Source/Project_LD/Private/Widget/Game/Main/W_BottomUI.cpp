// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Main/W_BottomUI.h"
#include <Widget/Game/Main/W_PlayerBar.h>
#include "Blueprint/WidgetTree.h"

#include <Framework/Game/GM_Game.h>
#include <Framework/Game/PC_Game.h>
#include <Framework/Game/PS_Game.h>

#include "Components/ProgressBar.h"

void UW_BottomUI::Init()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	AGM_Game* gamemode = Cast<AGM_Game>(world->GetAuthGameMode());
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

	playerstate->OnCharacterHealthChanged.AddUFunction(this, FName(TEXT("UpdateHealthBar")));
	playerstate->OnCharacterManaChanged.AddUFunction(this, FName(TEXT("UpdateManaBar")));

	UpdateHealthBar();
	UpdateManaBar();
}

void UW_BottomUI::UpdateHealthBar()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	AGM_Game* gamemode = Cast<AGM_Game>(world->GetAuthGameMode());
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

	UW_PlayerBar* playerBar = Cast<UW_PlayerBar>(mPlayerBar);
	if (playerBar == nullptr)
	{
		return;
	}

	playerBar->HealthBar->SetPercent(playerstate->GetHealthBarPercent());
}

void UW_BottomUI::UpdateManaBar()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	AGM_Game* gamemode = Cast<AGM_Game>(world->GetAuthGameMode());
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

	UW_PlayerBar* playerBar = Cast<UW_PlayerBar>(mPlayerBar);
	if (playerBar == nullptr)
	{
		return;
	}

	playerBar->ManaBar->SetPercent(playerstate->GetManaBarPercent());
}

void UW_BottomUI::NativeConstruct()
{
	mPlayerBar = this->WidgetTree->FindWidget(FName(TEXT("BW_PlayerBar")));
	if (mPlayerBar == nullptr)
	{
		return;
	}
}