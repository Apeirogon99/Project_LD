// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PS_Game.h"
#include <Handler/ClientHUD.h>
#include <Widget/Game/Inventory/UWInventory.h>
#include <Widget/Game/Item/W_ItemSpace.h>

#include <GM_Game.h>
#include <PC_Game.h>
#include <C_Game.h>

APS_Game::APS_Game()
{
	mInventoryComponent = CreateDefaultSubobject<UACInventoryComponent>(TEXT("Inventory"));
	if (mInventoryComponent == nullptr)
	{
		return;
	}

	mEquipmentComponent = CreateDefaultSubobject<UACEquipment>(TEXT("Equipment"));
	if (mEquipmentComponent == nullptr)
	{
		return;
	}

	mRemoteID = 0;
}

APS_Game::~APS_Game()
{
}

void APS_Game::InitializeLocalPlayerState()
{

	AGM_Game* gameMode = Cast<AGM_Game>(GetWorld()->GetAuthGameMode());
	if (nullptr == gameMode)
	{
		return;
	}
	
	if (gameMode->GetNetworkController() != GetPawn()->GetController())
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

	UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("Inventory")));
	if (nullptr == widget)
	{
		return;
	}

	UUWInventory* inventory = Cast<UUWInventory>(widget);

	inventory->InitInventory(mInventoryComponent, 50.0f, mEquipmentComponent);

	mEquipmentComponent->Init(inventory);
}

void APS_Game::SetRemotePlayerID(const int64 inRemoteID)
{
	mRemoteID = inRemoteID;
}

void APS_Game::SetCharacterData(const FCharacterData& InCharacterDatas)
{
	mCharacterData = InCharacterDatas;
}

void APS_Game::SetCharacterEqipment(const FCharacterEquipment& inCharacterEquipment)
{
	mCharacterData.mEquipment = inCharacterEquipment;
}