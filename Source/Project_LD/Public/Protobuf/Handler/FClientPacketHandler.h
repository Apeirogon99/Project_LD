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
#include <GamePacket.pb.h>

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
	C2S_LoadServer = 1010,
	S2C_LoadServer = 1011,
	C2S_SelectServer = 1012,
	S2C_SelectServer = 1013,
	C2S_StartGame = 1014,
	S2C_StartGame = 1015,
	C2S_LoadCharacters = 1016,
	S2C_LoadCharacters = 1017,
	C2S_CreateCharacter = 1018,
	S2C_CreateCharacter = 1019,
	C2S_DeleteCharacter = 1020,
	S2C_DeleteCharacter = 1021,

	C2S_EnterGameServer = 2000,
	S2C_EnterGameServer = 2001,
	C2S_LeaveGameServer = 2002,
	S2C_LeaveGameServer = 2003,
	C2S_Tick = 2004,
	S2C_Tick = 2005,
	S2C_AppearCharacter = 2006,
	S2C_DisAppearCharacter = 2007,
	C2S_MovementCharacter = 2008,
	S2C_MovementCharacter = 2009,
	C2S_PlayAnimation = 2010,
	S2C_PlayAnimation = 2011,
	C2S_AttackToEnemy = 2012,
	S2C_AttackToEnemy = 2013,
	S2C_AppearItem = 2014,
	S2C_AppearEnemy = 2015,
	S2C_TickEnemy = 2016,
	S2C_MovementEnemy = 2017,
	S2C_AttackToPlayer = 2018,
	S2C_DisAppearGameObject = 2019,
	C2S_LoadInventory = 2020,
	S2C_LoadInventory = 2021,
	C2S_InsertInventory = 2022,
	S2C_InsertInventory = 2023,
	C2S_UpdateInventory = 2024,
	S2C_UpdateInventory = 2025,
	C2S_DeleteInventory = 2026,
	S2C_DeleteInventory = 2027,
	S2C_RollbackInventory = 2028,
	C2S_ReplaceEqipment = 2029,
	S2C_ReplaceEqipment = 2030,

	C2S_ReplicatedServerTimeStamp = 9000,
	S2C_ReplicatedServerTimeStamp = 9001,
	C2S_TravelLevel = 9002,
	S2C_TravelLevel = 9003,
	C2S_TravelServer = 9004,
	S2C_TravelServer = 9005,
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
	friend class FGamePacketHandler;

public:
	static PacketFunc PacketHandler[UINT16_MAX];
};
