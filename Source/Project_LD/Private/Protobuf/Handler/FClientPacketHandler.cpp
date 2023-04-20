// Fill out your copyright notice in the Description page of Project Settings.


#include "Protobuf/Handler/FClientPacketHandler.h"
#include <Network/NetworkUtils.h>
#include <PacketUtils.h>
#include <Protobuf/Handler/FIdentityPacketHandler.h>

PacketFunc FClientPacketHandler::PacketHandler[UINT16_MAX];

bool Handle_INVALID(ANetworkController* controller, BYTE* buffer, int32 len)
{
	UNetworkUtils::NetworkConsoleLog("PacketHandle : Handle_INVALID", ELogLevel::Error);
	return true;
}

void FClientPacketHandler::Init()
{
	for (int i = 0; i < UINT16_MAX; ++i)
	{
		PacketHandler[i] = Handle_INVALID;
	}

	FIdentityPacketHandler::Init(PacketHandler);

	UNetworkUtils::NetworkConsoleLog("PacketHandle success Init", ELogLevel::Warning);
}
