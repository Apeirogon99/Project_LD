// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Main/W_MainGame.h"
#include <Game/GM_Game.h>
#include <Game/PC_Game.h>
#include <Widget/Handler/ClientHUD.h>

#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>

void UW_MainGame::NativeConstruct()
{
	Super::NativeConstruct();

	misInventoryOpen = true;
}

void UW_MainGame::InventoryOpenRequest()
{
	AGM_Game* gamemode = Cast<AGM_Game>(GetWorld()->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}

	APC_Game* playerController = Cast<APC_Game>(gamemode->GetNetworkController());
	if(GetOwningPlayer()!=playerController)
	{
		return;
	}
	
	AClientHUD* clientHUD = Cast<AClientHUD>(gamemode->GetClientHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	if (misInventoryOpen)
	{
		misInventoryOpen = !misInventoryOpen;
		clientHUD->CleanWidgetFromName(FString(TEXT("Inventory")));
		playerController->SwitchMovementMode();
	}
	else
	{
		Protocol::C2S_LoadInventory loadInventoryPacket;
		const int64 serverTimeStamp = playerController->GetServerTimeStamp();
		loadInventoryPacket.set_timestamp(serverTimeStamp);
		playerController->Send(FGamePacketHandler::MakeSendBuffer(playerController, loadInventoryPacket));
	}
}

void UW_MainGame::InventoryOpenResponse()
{
	AGM_Game* gamemode = Cast<AGM_Game>(GetWorld()->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}

	APC_Game* playerController = Cast<APC_Game>(gamemode->GetNetworkController());
	if (GetOwningPlayer() != playerController)
	{
		return;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(gamemode->GetClientHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	misInventoryOpen = !misInventoryOpen;
	if (misInventoryOpen)
	{
		clientHUD->ShowWidgetFromName(FString(TEXT("Inventory")));
		playerController->SwitchUIMode();
	}
}
