// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Network/NetworkController.h>
#include <Network/SendBuffer.h>
#include <Network/RecvBuffer.h>
#include <Network/NetworkController.h>

#include <IdentityPacket.pb.h>

class ANetworkController;

using SendBufferPtr = TSharedPtr<class FSendBuffer>;
using PacketFunc = TFunction<bool(ANetworkController*, BYTE*, int32)>;

bool Handle_INVALID(ANetworkController* controller, BYTE* buffer, int32 len);

class PROJECT_LD_API FClientPacketHandler
{
public:
	static void Init();

	static bool HandlePacket(ANetworkController* controller, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return PacketHandler[header->id](controller, buffer, len);
	}

private:
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, ANetworkController* controller, BYTE* buffer, int32 len)
	{
		PacketType pkt;
		if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
			return false;

		return func(controller, pkt);
	}

	template<typename T>
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, T& pkt, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferPtr SendBuffer = MakeShared<FSendBuffer>(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(SendBuffer->GetData());
		header->size = packetSize;
		header->id = pktId;
		pkt.SerializeToArray(&header[1], dataSize);
		return SendBuffer;
	}

private:
	friend class FIdentityPacketHandler;

public:
	static PacketFunc PacketHandler[UINT16_MAX];
};
