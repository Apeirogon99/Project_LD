// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PC_Game.h"
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Network/NetworkUtils.h>

APC_Game::APC_Game()
{
	SwitchMovementMode();
}

APC_Game::~APC_Game()
{
}

void APC_Game::BeginPlay()
{
	Super::BeginPlay();
}

bool APC_Game::OnRecvPacket(BYTE* buffer, const uint32 len)
{
	ANetworkController* controller = Cast<ANetworkController>(this);
	bool result = false;
	result = FClientPacketHandler::HandlePacket(controller, buffer, len);
	if (false == result)
	{
		UNetworkUtils::NetworkConsoleLog("Failed to handle packet", ELogLevel::Error);
		return false;
	}

	return true;
}

bool APC_Game::OnSend(int32 len)
{
	return true;
}

bool APC_Game::OnConnect()
{
	return true;
}

bool APC_Game::OnDisconnect()
{
	return true;
}
