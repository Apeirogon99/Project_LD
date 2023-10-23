// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PS_Game.h"
#include <Handler/ClientHUD.h>
#include <Widget/Game/Inventory/UWInventory.h>
#include <Widget/Game/Item/W_ItemSpace.h>
#include <Widget/Game/Main/W_MainGame.h>

#include <GM_Game.h>
#include <PC_Game.h>
#include <C_Game.h>

APS_Game::APS_Game()
{
	mRemoteID = 0;
}

APS_Game::~APS_Game()
{
}

void APS_Game::BeginPlay()
{
	Super::BeginPlay();
}

void APS_Game::UpdateExpValue(int InExp)
{
	mCharacterData.SetExp(InExp);
	UpdateExpBar();
}

void APS_Game::InitializeLocalPlayerState()
{
	ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
	if (nullptr == gameMode)
	{
		return;
	}
	
	if (gameMode->GetNetworkController() == GetPawn()->GetController())
	{
		mInventoryComponent = NewObject<UACInventoryComponent>(this,TEXT("Inventory"));
		if (mInventoryComponent == nullptr)
		{
			return;
		}
		this->AddOwnedComponent(mInventoryComponent);
		mInventoryComponent->RegisterComponent();

		mEquipmentComponent = NewObject<UACEquipment>(this, TEXT("Equipment"));
		if (mEquipmentComponent == nullptr)
		{
			return;
		}
		this->AddOwnedComponent(mEquipmentComponent);
		mEquipmentComponent->RegisterComponent();

		mPartyComponent = NewObject<UACPartyComponent>(this, TEXT("Party"));
		if (mPartyComponent == nullptr)
		{
			return;
		}
		this->AddOwnedComponent(mPartyComponent);
		mPartyComponent->RegisterComponent();

	}
	APC_Game* playercontroller = Cast<APC_Game>(gameMode->GetNetworkController());
	if (nullptr == playercontroller)
	{
		return;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(playercontroller->GetHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("Inventory")));
	if (nullptr == widget)
	{
		return;
	}

	UUWInventory* inventory = Cast<UUWInventory>(widget);

	inventory->InitInventory(mInventoryComponent, 50.0f, mEquipmentComponent);

	mEquipmentComponent->Init(inventory);
}

void APS_Game::InitializeLocalPlayerData()
{
	ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
	if (nullptr == gameMode)
	{
		return;
	}

	APC_Game* playercontroller = Cast<APC_Game>(gameMode->GetNetworkController());
	if (nullptr == playercontroller)
	{
		return;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(playercontroller->GetHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	auto maingame = clientHUD->GetWidgetFromName(TEXT("MainGame"));
	Cast<UW_MainGame>(maingame)->Init();

	calculationStats();

	mCharacterStats.SetCurrentStats(mCharacterStats.GetMaxStats());

	UpdateCurrentStatsBar();
}

void APS_Game::UpdateExpBar()
{
	if (OnCharacterExpChanged.IsBound())
	{
		OnCharacterExpChanged.Broadcast();
	}
}