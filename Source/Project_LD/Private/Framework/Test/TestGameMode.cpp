// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Test/TestGameMode.h"
#include <Network/NetworkController.h>
#include <Framework/Identity/IdentityPlayerController.h>
#include <Widget/Handler/ClientHUD.h>

#include <Protobuf/Handler/FIdentityPacketHandler.h>

ATestGameMode::ATestGameMode()
{
	this->PlayerControllerClass = AIdentityPlayerController::StaticClass();
}

ATestGameMode::~ATestGameMode()
{
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (false == IsConnectedServer())
	{
		if (false == RequestConnectServer(TEXT("116.41.116.247"), 9000))
		{

		}
	}
}

void ATestGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ATestGameMode::BeginNetwork()
{
	Super::BeginNetwork();

	if (false == mClientHUD)
	{
		return;
	}

	ANetworkController* controller = GetNetworkController();
	Protocol::C2S_EnterIdentityServer packet;
	packet.set_error(0);
	controller->Send(FIdentityPacketHandler::MakeSendBuffer(controller, packet));

	mClientHUD->ShowWidgetFromName(TEXT("Test"));
}
