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
	S2C_DetectChangePlayer = 2012,
	C2S_PlayerAutoAttack = 2013,
	S2C_PlayerAutoAttack = 2014,
	S2C_UpdateExperience = 2015,
	S2C_LevelUp = 2016,
	C2S_Chat = 2017,
	S2C_Chat = 2018,
	C2S_LoadFriendList = 2019,
	S2C_LoadFriendList = 2020,
	C2S_RequestFriend = 2021,
	S2C_RequestFriend = 2022,
	C2S_BlockFriend = 2023,
	S2C_BlockFriend = 2024,
	S2C_ConnectFriend = 2025,
	S2C_DisConnectFriend = 2026,
	S2C_AppearItem = 2027,
	S2C_AppearArrow = 2028,
	S2C_MovementProjectile = 2029,
	S2C_AppearEnemy = 2030,
	S2C_DetectChangeEnemy = 2031,
	S2C_MovementEnemy = 2032,
	S2C_EnemyAutoAttack = 2033,
	S2C_HitEnemy = 2034,
	S2C_DeathEnemy = 2035,
	S2C_DisAppearGameObject = 2036,
	C2S_LoadInventory = 2037,
	S2C_LoadInventory = 2038,
	C2S_InsertInventory = 2039,
	S2C_InsertInventory = 2040,
	C2S_UpdateInventory = 2041,
	S2C_UpdateInventory = 2042,
	C2S_DeleteInventory = 2043,
	S2C_DeleteInventory = 2044,
	S2C_RollbackInventory = 2045,
	C2S_ReplaceEqipment = 2046,
	S2C_ReplaceEqipment = 2047,

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
