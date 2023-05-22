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
}

void AGM_LoginScreen::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGM_LoginScreen::InitNetwork()
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

void AGM_LoginScreen::BeginNetwork()
{
	Super::BeginNetwork();

	ANetworkController* controller = GetNetworkController();

	if (controller)
	{
		Protocol::C2S_EnterIdentityServer packet;
		controller->Send(FIdentityPacketHandler::MakeSendBuffer(controller, packet));
	}
}
