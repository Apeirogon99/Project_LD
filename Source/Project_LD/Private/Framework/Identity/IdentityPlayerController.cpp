// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Identity/IdentityPlayerController.h"

#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FCommonPacketHandler.h>
#include <Network/NetworkUtils.h>

#include <Network/NetworkTimeStamp.h>

#include <Network/RecvBuffer.h>
#include <Network/NetworkUtils.h>

AIdentityPlayerController::AIdentityPlayerController()
{

}

AIdentityPlayerController::~AIdentityPlayerController()
{

}

void AIdentityPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}

bool AIdentityPlayerController::OnRecvPacket(BYTE* buffer, const uint32 len)
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

bool AIdentityPlayerController::OnSend(int32 len)
{
	return true;
}

bool AIdentityPlayerController::OnConnect()
{
	return true;
}

bool AIdentityPlayerController::OnDisconnect()
{
	return true;
}

bool AIdentityPlayerController::OnTick()
{
	UNetworkTimeStamp* networkTimeStmap = this->GetTimeStamp();
	if (nullptr == networkTimeStmap)
	{
		return false;
	}

	const int64 nowUtcTimeStamp = networkTimeStmap->GetUtcTimeStmap();
	const int64 nowRTT = networkTimeStmap->GetRTT();

	Protocol::C2S_ReplicatedServerTimeStamp timeStampPacket;
	timeStampPacket.set_utc_time(nowUtcTimeStamp);
	timeStampPacket.set_rtt(nowRTT);
	SendBufferPtr pakcetBuffer = FCommonPacketHandler::MakeSendBuffer(this, timeStampPacket);
	this->Send(pakcetBuffer);
	return true;
}
