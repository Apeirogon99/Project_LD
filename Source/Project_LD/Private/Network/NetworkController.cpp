// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkController.h"
#include <Network/NetworkSession.h>
#include <Network/RecvBuffer.h>
#include <Network/SendBuffer.h>
#include <Network/SendBufferQueue.h>
#include <Network/NetworkUtils.h>
#include <Framework/Gameinstance/LDGameInstance.h>

ANetworkController::ANetworkController()
{
}

ANetworkController::~ANetworkController()
{
}

void ANetworkController::BeginPlay()
{
	
}

void ANetworkController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

bool ANetworkController::IsConnectedToSession()
{
	bool isValid = mNetworkSession.IsValid();
	return isValid == true ? true : false;
}

bool ANetworkController::ConnectToSession(FNetworkSessionPtr session, FPossessCallBack inPossessCallBack)
{
	if (nullptr == session)
	{
		UNetworkUtils::NetworkConsoleLog("[ANetworkController::ConnectToSession] : Invalid session", ELogLevel::Error);
		return false;
	}

	mNetworkSession = session;

	if (false == inPossessCallBack.IsBound())
	{
		UNetworkUtils::NetworkConsoleLog("[ANetworkController::ConnectToSession] : Invalid possess call back", ELogLevel::Error);
		return false;
	}

	mPossessCallBack = inPossessCallBack;
	mPossessCallBack.Execute(true);

	return true;
}

bool ANetworkController::DisconnectToSession(FUnPossessCallBack inUnPossessCallback)
{
	if (false == mNetworkSession.IsValid())
	{
		UNetworkUtils::NetworkConsoleLog("[ANetworkController::DisconnectToSession] : Invalid session", ELogLevel::Error);
		return false;
	}

	mNetworkSession.Reset();

	if (false == inUnPossessCallback.IsBound())
	{
		UNetworkUtils::NetworkConsoleLog("[ANetworkController::DisconnectToSession] : Invalid unpossess call back", ELogLevel::Error);
		return false;
	}

	mUnPossessCallBack = inUnPossessCallback;
	mUnPossessCallBack.Execute(true);

	return true;
}

bool ANetworkController::IsClientController()
{
	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(GetGameInstance());
	if (!gameInstance)
	{
		return false;
	}



	return true;
}

int64 ANetworkController::GetNetworkTimeStamp()
{
	if (mNetworkSession)
	{
		return mNetworkSession->GetServerTimeStamp();
	}

	return -1;
}

void ANetworkController::SetNetworkTimeStamp(const int64 inTimeStamp)
{
	mNetworkSession->SetTimeStamp(inTimeStamp);
}

void ANetworkController::Send(SendBufferPtr FSendBuffer)
{
	if (mNetworkSession.IsValid())
	{
		mNetworkSession->Send(FSendBuffer);
	}
}

bool ANetworkController::OnRecv(FRecvBuffer* buffer, int32 len)
{
	BYTE packetBuffer[1024];
	uint32 processLen = 0;

	while (true)
	{
		int32 dataSize = len - processLen;

		if (dataSize < sizeof(PacketHeader))
		{
			break;
		}

		PacketHeader header;
		buffer->Peek(reinterpret_cast<BYTE*>(&header), sizeof(PacketHeader));
		const uint16 packetSize = header.size;
		if (dataSize < packetSize)
		{
			break;
		}

		memset(packetBuffer, NULL, 1024);
		buffer->Dequeue(packetBuffer, packetSize);

		bool packetResult = OnRecvPacket(packetBuffer, packetSize);
		if (false == packetResult)
		{
			return false;
		}

		processLen += packetSize;
	}

	return true;
}