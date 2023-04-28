// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Identity/GM_LoginScreen.h"
#include <Network/NetworkController.h>
#include <Framework/Identity/IdentityPlayerController.h>
#include <Widget/Handler/ClientHUD.h>

#include <Protobuf/Handler/FIdentityPacketHandler.h>

AGM_LoginScreen::AGM_LoginScreen()
{
	this->PlayerControllerClass = AIdentityPlayerController::StaticClass();
}

AGM_LoginScreen::~AGM_LoginScreen()
{
}

void AGM_LoginScreen::BeginPlay()
{
	Super::BeginPlay();

	if (true == IsConnectedServer())
	{
		if (false == RequestKeepConnectServer(TEXT("127.0.0.1"), 9000))
		{

		}
	}
	else
	{
		if (false == RequestConnectServer(TEXT("127.0.0.1"), 9000))
		{

		}
	}
}

void AGM_LoginScreen::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGM_LoginScreen::BeginNetwork()
{
	Super::BeginNetwork();

	ANetworkController* controller = GetNetworkController();

	Protocol::C2S_EnterIdentityServer packet;
	packet.set_error(0);

	controller->Send(FIdentityPacketHandler::MakeSendBuffer(controller, packet));
}
