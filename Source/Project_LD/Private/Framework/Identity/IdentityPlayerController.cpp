// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Identity/IdentityPlayerController.h"

#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FCommonPacketHandler.h>
#include <Network/NetworkUtils.h>
#include <Widget/Handler/ClientHUD.h>
#include <Network/NetworkTimeStamp.h>
#include <Widget/Game/Main/W_MainGame.h>
#include <Widget/WidgetUtils.h>

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
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("Failed to handle packet [%d]"), header->id), ELogLevel::Error);

		AClientHUD* clientHUD = Cast<AClientHUD>(controller->GetHUD());
		if (nullptr == clientHUD)
		{
			UNetworkUtils::NetworkConsoleLog("Invalid client hud", ELogLevel::Error);
			return false;
		}

		FNotificationDelegate notificationDelegate;
		notificationDelegate.BindLambda([=]()
			{
				clientHUD->CleanWidgetFromName(TEXT("Notification"));
				FGenericPlatformMisc::RequestExit(false);
			});

		bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("Error"), FString::Printf(TEXT("Failed to handle packet [%d]"), header->id), TEXT("Confirm"), notificationDelegate);
		if (ret == false)
		{
			return false;
		}

		return false;
	}

	return true;
}

bool AIdentityPlayerController::OnSend(int32 len)
{
	UNetworkUtils::NetworkConsoleLog("OnSend", ELogLevel::Error);
	return true;
}

bool AIdentityPlayerController::OnConnect()
{
	UNetworkUtils::NetworkConsoleLog("OnConnect", ELogLevel::Error);
	return true;
}

bool AIdentityPlayerController::OnDisconnect()
{
	UNetworkUtils::NetworkConsoleLog("OnDisconnect", ELogLevel::Error);
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
