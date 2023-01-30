// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkController.h"
#include <Network/NetworkSession.h>
#include <Network/RecvBuffer.h>
#include <Network/SendBuffer.h>
#include <Network/SendBufferQueue.h>
#include <Network/NetworkUtils.h>

ANetworkController::ANetworkController()
{
}

ANetworkController::~ANetworkController()
{
}

bool ANetworkController::IsConnectedToSession()
{
	return mNetworkSession != nullptr ? true : false;
}

void ANetworkController::ConnectToSession(FNetworkSession* session)
{
	mNetworkSession = session;
}

void ANetworkController::DisconnectToSession()
{
}

void ANetworkController::Send(SendBufferPtr FSendBuffer)
{
	if (mNetworkSession)
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

		//buffer->MoveFront(packetSize);

		processLen += packetSize;
	}

	return true;
}