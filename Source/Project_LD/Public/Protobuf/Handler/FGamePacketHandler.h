#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Protobuf/Handler/FClientPacketHandler.h>

/*
enum class EPakcetID: uint16
{
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
	C2S_Chat = 2015,
	S2C_Chat = 2016,
	C2S_LoadFriendList = 2017,
	S2C_LoadFriendList = 2018,
	C2S_RequestFriend = 2019,
	S2C_RequestFriend = 2020,
	C2S_BlockFriend = 2021,
	S2C_BlockFriend = 2022,
	S2C_ConnectFriend = 2023,
	S2C_DisConnectFriend = 2024,
	S2C_AppearItem = 2025,
	S2C_AppearArrow = 2026,
	S2C_MovementProjectile = 2027,
	S2C_AppearEnemy = 2028,
	S2C_DetectChangeEnemy = 2029,
	S2C_MovementEnemy = 2030,
	S2C_EnemyAutoAttack = 2031,
	S2C_HitEnemy = 2032,
	S2C_DeathEnemy = 2033,
	S2C_DisAppearGameObject = 2034,
	C2S_LoadInventory = 2035,
	S2C_LoadInventory = 2036,
	C2S_InsertInventory = 2037,
	S2C_InsertInventory = 2038,
	C2S_UpdateInventory = 2039,
	S2C_UpdateInventory = 2040,
	C2S_DeleteInventory = 2041,
	S2C_DeleteInventory = 2042,
	S2C_RollbackInventory = 2043,
	C2S_ReplaceEqipment = 2044,
	S2C_ReplaceEqipment = 2045,
};
*/

// Custom Handlers
bool Handle_S2C_EnterGameServer(ANetworkController* controller, Protocol::S2C_EnterGameServer& pkt);
bool Handle_S2C_LeaveGameServer(ANetworkController* controller, Protocol::S2C_LeaveGameServer& pkt);
bool Handle_S2C_Tick(ANetworkController* controller, Protocol::S2C_Tick& pkt);
bool Handle_S2C_AppearCharacter(ANetworkController* controller, Protocol::S2C_AppearCharacter& pkt);
bool Handle_S2C_DisAppearCharacter(ANetworkController* controller, Protocol::S2C_DisAppearCharacter& pkt);
bool Handle_S2C_MovementCharacter(ANetworkController* controller, Protocol::S2C_MovementCharacter& pkt);
bool Handle_S2C_PlayAnimation(ANetworkController* controller, Protocol::S2C_PlayAnimation& pkt);
bool Handle_S2C_DetectChangePlayer(ANetworkController* controller, Protocol::S2C_DetectChangePlayer& pkt);
bool Handle_S2C_PlayerAutoAttack(ANetworkController* controller, Protocol::S2C_PlayerAutoAttack& pkt);
bool Handle_S2C_Chat(ANetworkController* controller, Protocol::S2C_Chat& pkt);
bool Handle_S2C_LoadFriendList(ANetworkController* controller, Protocol::S2C_LoadFriendList& pkt);
bool Handle_S2C_RequestFriend(ANetworkController* controller, Protocol::S2C_RequestFriend& pkt);
bool Handle_S2C_BlockFriend(ANetworkController* controller, Protocol::S2C_BlockFriend& pkt);
bool Handle_S2C_ConnectFriend(ANetworkController* controller, Protocol::S2C_ConnectFriend& pkt);
bool Handle_S2C_DisConnectFriend(ANetworkController* controller, Protocol::S2C_DisConnectFriend& pkt);
bool Handle_S2C_AppearItem(ANetworkController* controller, Protocol::S2C_AppearItem& pkt);
bool Handle_S2C_AppearArrow(ANetworkController* controller, Protocol::S2C_AppearArrow& pkt);
bool Handle_S2C_MovementProjectile(ANetworkController* controller, Protocol::S2C_MovementProjectile& pkt);
bool Handle_S2C_AppearEnemy(ANetworkController* controller, Protocol::S2C_AppearEnemy& pkt);
bool Handle_S2C_DetectChangeEnemy(ANetworkController* controller, Protocol::S2C_DetectChangeEnemy& pkt);
bool Handle_S2C_MovementEnemy(ANetworkController* controller, Protocol::S2C_MovementEnemy& pkt);
bool Handle_S2C_EnemyAutoAttack(ANetworkController* controller, Protocol::S2C_EnemyAutoAttack& pkt);
bool Handle_S2C_HitEnemy(ANetworkController* controller, Protocol::S2C_HitEnemy& pkt);
bool Handle_S2C_DeathEnemy(ANetworkController* controller, Protocol::S2C_DeathEnemy& pkt);
bool Handle_S2C_DisAppearGameObject(ANetworkController* controller, Protocol::S2C_DisAppearGameObject& pkt);
bool Handle_S2C_LoadInventory(ANetworkController* controller, Protocol::S2C_LoadInventory& pkt);
bool Handle_S2C_InsertInventory(ANetworkController* controller, Protocol::S2C_InsertInventory& pkt);
bool Handle_S2C_UpdateInventory(ANetworkController* controller, Protocol::S2C_UpdateInventory& pkt);
bool Handle_S2C_DeleteInventory(ANetworkController* controller, Protocol::S2C_DeleteInventory& pkt);
bool Handle_S2C_RollbackInventory(ANetworkController* controller, Protocol::S2C_RollbackInventory& pkt);
bool Handle_S2C_ReplaceEqipment(ANetworkController* controller, Protocol::S2C_ReplaceEqipment& pkt);

class FGamePacketHandler
{
public:
	static void Init(PacketFunc inPacketFunc[UINT16_MAX])
	{
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_EnterGameServer)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_EnterGameServer>(Handle_S2C_EnterGameServer, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_LeaveGameServer)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_LeaveGameServer>(Handle_S2C_LeaveGameServer, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_Tick)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_Tick>(Handle_S2C_Tick, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AppearCharacter)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AppearCharacter>(Handle_S2C_AppearCharacter, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_DisAppearCharacter)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_DisAppearCharacter>(Handle_S2C_DisAppearCharacter, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_MovementCharacter)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_MovementCharacter>(Handle_S2C_MovementCharacter, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_PlayAnimation)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_PlayAnimation>(Handle_S2C_PlayAnimation, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_DetectChangePlayer)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_DetectChangePlayer>(Handle_S2C_DetectChangePlayer, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_PlayerAutoAttack)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_PlayerAutoAttack>(Handle_S2C_PlayerAutoAttack, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_Chat)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_Chat>(Handle_S2C_Chat, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_LoadFriendList)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_LoadFriendList>(Handle_S2C_LoadFriendList, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_RequestFriend)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_RequestFriend>(Handle_S2C_RequestFriend, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_BlockFriend)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_BlockFriend>(Handle_S2C_BlockFriend, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_ConnectFriend)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_ConnectFriend>(Handle_S2C_ConnectFriend, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_DisConnectFriend)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_DisConnectFriend>(Handle_S2C_DisConnectFriend, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AppearItem)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AppearItem>(Handle_S2C_AppearItem, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AppearArrow)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AppearArrow>(Handle_S2C_AppearArrow, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_MovementProjectile)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_MovementProjectile>(Handle_S2C_MovementProjectile, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AppearEnemy)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AppearEnemy>(Handle_S2C_AppearEnemy, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_DetectChangeEnemy)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_DetectChangeEnemy>(Handle_S2C_DetectChangeEnemy, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_MovementEnemy)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_MovementEnemy>(Handle_S2C_MovementEnemy, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_EnemyAutoAttack)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_EnemyAutoAttack>(Handle_S2C_EnemyAutoAttack, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_HitEnemy)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_HitEnemy>(Handle_S2C_HitEnemy, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_DeathEnemy)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_DeathEnemy>(Handle_S2C_DeathEnemy, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_DisAppearGameObject)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_DisAppearGameObject>(Handle_S2C_DisAppearGameObject, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_LoadInventory)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_LoadInventory>(Handle_S2C_LoadInventory, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_InsertInventory)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_InsertInventory>(Handle_S2C_InsertInventory, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_UpdateInventory)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_UpdateInventory>(Handle_S2C_UpdateInventory, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_DeleteInventory)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_DeleteInventory>(Handle_S2C_DeleteInventory, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_RollbackInventory)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_RollbackInventory>(Handle_S2C_RollbackInventory, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_ReplaceEqipment)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_ReplaceEqipment>(Handle_S2C_ReplaceEqipment, controller, buffer, len); };
	}
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_EnterGameServer& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_EnterGameServer)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_LeaveGameServer& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_LeaveGameServer)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_Tick& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_Tick)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_MovementCharacter& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_MovementCharacter)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_PlayAnimation& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_PlayAnimation)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_PlayerAutoAttack& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_PlayerAutoAttack)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_Chat& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_Chat)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_LoadFriendList& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_LoadFriendList)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_RequestFriend& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_RequestFriend)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_BlockFriend& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_BlockFriend)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_LoadInventory& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_LoadInventory)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_InsertInventory& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_InsertInventory)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_UpdateInventory& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_UpdateInventory)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_DeleteInventory& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_DeleteInventory)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_ReplaceEqipment& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_ReplaceEqipment)); }

};