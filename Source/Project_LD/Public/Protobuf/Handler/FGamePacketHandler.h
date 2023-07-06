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
bool Handle_S2C_AttackToEnemy(ANetworkController* controller, Protocol::S2C_AttackToEnemy& pkt);
bool Handle_S2C_AppearItem(ANetworkController* controller, Protocol::S2C_AppearItem& pkt);
bool Handle_S2C_AppearEnemy(ANetworkController* controller, Protocol::S2C_AppearEnemy& pkt);
bool Handle_S2C_TickEnemy(ANetworkController* controller, Protocol::S2C_TickEnemy& pkt);
bool Handle_S2C_MovementEnemy(ANetworkController* controller, Protocol::S2C_MovementEnemy& pkt);
bool Handle_S2C_AttackToPlayer(ANetworkController* controller, Protocol::S2C_AttackToPlayer& pkt);
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
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AttackToEnemy)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AttackToEnemy>(Handle_S2C_AttackToEnemy, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AppearItem)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AppearItem>(Handle_S2C_AppearItem, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AppearEnemy)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AppearEnemy>(Handle_S2C_AppearEnemy, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_TickEnemy)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_TickEnemy>(Handle_S2C_TickEnemy, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_MovementEnemy)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_MovementEnemy>(Handle_S2C_MovementEnemy, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AttackToPlayer)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AttackToPlayer>(Handle_S2C_AttackToPlayer, controller, buffer, len); };
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
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_AttackToEnemy& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_AttackToEnemy)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_LoadInventory& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_LoadInventory)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_InsertInventory& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_InsertInventory)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_UpdateInventory& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_UpdateInventory)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_DeleteInventory& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_DeleteInventory)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_ReplaceEqipment& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_ReplaceEqipment)); }

};