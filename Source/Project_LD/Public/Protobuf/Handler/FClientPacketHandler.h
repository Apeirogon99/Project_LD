// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Network/NetworkController.h>
#include <Network/SendBuffer.h>
#include <Network/RecvBuffer.h>
#include <Network/NetworkController.h>
#include <PacketUtils.h>

#include <IdentityPacket.pb.h>
#include <CommonPacket.pb.h>

class ANetworkController;

using SendBufferPtr = TSharedPtr<class FSendBuffer>;
using PacketFunc = TFunction<bool(ANetworkController*, BYTE*, int32)>;

enum class EPakcetID : uint16
{
	C2S_EnterIdentityServer = 1000,
	S2C_EnterIdentityServer = 1001,
	C2S_LeaveIdentityServer = 1002,
	S2C_LeaveIdentityServer = 1003,
	C2S_Singin = 1004,
	S2C_Singin = 1005,
	C2S_Singup = 1006,
	S2C_Singup = 1007,
	C2S_EmailVerified = 1008,
	S2C_EmailVerified = 1009,
	S2C_LoadServer = 1010,
	C2S_LoadCharacters = 1011,
	S2C_LoadCharacters = 1012,
	C2S_CreateCharacter = 1013,
	S2C_CreateCharacter = 1014,
	C2S_UpdateAppearance = 1015,
	S2C_UpdateAppearance = 1016,
	C2S_DeleteCharacter = 1017,
	S2C_DeleteCharacter = 1018,
	C2S_UpdateNickName = 1019,
	S2C_UpdateNickName = 1020,
	C2S_TravelLevel = 1021,
	S2C_TravelLevel = 1022,
	C2S_TravelServer = 1023,
	S2C_TravelServer = 1024,
	C2S_Test = 1025,
	S2C_Test = 1026,

	C2S_EnterGameServer = 2000,
	S2C_EnterGameServer = 2001,
	C2S_LeaveGameServer = 2002,
	S2C_LeaveGameServer = 2003,
	C2S_MovementCharacter = 2004,
	S2C_MovementCharacter = 2005,

	S2C_ReplicatedServerTimeStamp = 9000,
};

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
	static SendBufferPtr MakeSendBuffer(const ANetworkController* controller, const T& pkt, const uint16 pktId)
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
	friend class FCommonPacketHandler;

public:
	static PacketFunc PacketHandler[UINT16_MAX];
};
