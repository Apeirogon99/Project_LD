// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkController.h"
#include <Network/NetworkSession.h>
#include <Network/RecvBuffer.h>
#include <Network/SendBuffer.h>
#include <Network/SendBufferQueue.h>
#include <Network/NetworkUtils.h>
#include <Network/NetworkTimeStamp.h>
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
	const bool isValid = mNetworkSession.IsValid();
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

UNetworkTimeStamp* ANetworkController::GetTimeStamp()
{
	if (mNetworkSession)
	{
		return mNetworkSession->GetTimeStamp();
	}

	return nullptr;
}

const int64 ANetworkController::GetServerTimeStamp()
{
	if (mNetworkSession)
	{
		return mNetworkSession->GetTimeStamp()->GetServerTimeStamp();
	}

	return int64();
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
	uint32 processLen = 0;
	while (true)
	{
		int32 dataSize = len - processLen;
		mTempPacketBuffer.Empty();

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

		mTempPacketBuffer.Init(0, packetSize);
		buffer->Dequeue(&mTempPacketBuffer[0], packetSize);

		bool packetResult = OnRecvPacket(&mTempPacketBuffer[0], packetSize);
		if (false == packetResult)
		{
			return false;
		}

		processLen += packetSize;
	}

	return true;
}

void ANetworkController::ExecutePossessCallBack(const bool inResult)
{
	if (mPossessCallBack.IsBound())
	{
		mPossessCallBack.Execute(inResult);
	}
}

void ANetworkController::ExecuteUnPossessCallBack(const bool inResult)
{
	if (mUnPossessCallBack.IsBound())
	{
		mUnPossessCallBack.Execute(inResult);
	}
}
