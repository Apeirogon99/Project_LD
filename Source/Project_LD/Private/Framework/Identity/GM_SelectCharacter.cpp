// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Identity/GM_SelectCharacter.h"

#include <Network/NetworkController.h>
#include <Framework/Identity/IdentityPlayerController.h>

#include <Widget/Handler/ClientHUD.h>
#include <Widget/Identity/W_SelectCharacter.h>
#include <Widget/Identity/W_SelectCharacterButton.h>

#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FIdentityPacketHandler.h>

AGM_SelectCharacter::AGM_SelectCharacter()
{
	this->PlayerControllerClass = AIdentityPlayerController::StaticClass();
}

AGM_SelectCharacter::~AGM_SelectCharacter()
{
}

void AGM_SelectCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AGM_SelectCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGM_SelectCharacter::InitNetwork()
{
	if (true == IsConnectedServer())
	{
		if (false == RequestKeepConnectServer(TEXT("116.41.116.247"), 9000))
		{
			NetworkGameModeLog(FString(TEXT("failed to requset keep connect server")));
		}
	}
	else
	{
		if (false == RequestConnectServer(TEXT("116.41.116.247"), 9000))
		{
			NetworkGameModeLog(FString(TEXT("failed to requset connect server")));
		}
	}
}

void AGM_SelectCharacter::BeginNetwork()
{
	Super::BeginNetwork();

	mClientHUD->ShowWidgetFromName("LoadingServer");

	ANetworkController* networkController = GetNetworkController();
	if (networkController)
	{
		Protocol::C2S_LoadCharacters loadCharactersPacket;
		loadCharactersPacket.set_server_id(1);
		SendBufferPtr pakcetBuffer = FIdentityPacketHandler::MakeSendBuffer(networkController, loadCharactersPacket);
		networkController->Send(pakcetBuffer);
	}
}
