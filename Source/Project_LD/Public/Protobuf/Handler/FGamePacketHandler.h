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
	S2C_PlayerEndAutoAttack = 2015,
	S2C_UpdateExperience = 2016,
	S2C_LevelUp = 2017,
	C2S_Chat = 2018,
	S2C_Chat = 2019,
	C2S_LoadFriendList = 2020,
	S2C_LoadFriendList = 2021,
	C2S_RequestFriend = 2022,
	S2C_RequestFriend = 2023,
	C2S_BlockFriend = 2024,
	S2C_BlockFriend = 2025,
	S2C_ConnectFriend = 2026,
	S2C_DisConnectFriend = 2027,
	C2S_CreateParty = 2028,
	S2C_CreateParty = 2029,
	C2S_RequestEnterParty = 2030,
	S2C_RequestEnterParty = 2031,
	S2C_RequestParty = 2032,
	C2S_RequestLeaveParty = 2033,
	S2C_RequestLeaveParty = 2034,
	C2S_RequestLeaderParty = 2035,
	S2C_RequestLeaderParty = 2036,
	C2S_ResponeParty = 2037,
	S2C_ResponeParty = 2038,
	S2C_LoadParty = 2039,
	S2C_NotifyParty = 2040,
	S2C_EnterPartyPlayer = 2041,
	S2C_LeavePartyPlayer = 2042,
	S2C_AppearItem = 2043,
	S2C_AppearArrow = 2044,
	S2C_AppearProtal = 2045,
	S2C_AppearObstruction = 2046,
	S2C_AppearNPC = 2047,
	C2S_InteractiveObject = 2048,
	S2C_MovementProjectile = 2049,
	S2C_Teleport = 2050,
	S2C_AppearEnemy = 2051,
	S2C_DetectChangeEnemy = 2052,
	S2C_MovementEnemy = 2053,
	S2C_AnimationMovementEnemy = 2054,
	S2C_EnemyAutoAttack = 2055,
	S2C_HitEnemy = 2056,
	S2C_DeathEnemy = 2057,
	S2C_DisAppearGameObject = 2058,
	C2S_LoadInventory = 2059,
	S2C_LoadInventory = 2060,
	C2S_InsertInventory = 2061,
	S2C_InsertInventory = 2062,
	C2S_UpdateInventory = 2063,
	S2C_UpdateInventory = 2064,
	C2S_DeleteInventory = 2065,
	S2C_DeleteInventory = 2066,
	S2C_RollbackInventory = 2067,
	C2S_ReplaceEqipment = 2068,
	S2C_ReplaceEqipment = 2069,
	S2C_LoadSkillTree = 2070,
	C2S_UpdateSkillTree = 2071,
	S2C_UpdateSkillTree = 2072,
	C2S_SetUseKeyAction = 2073,
	S2C_SetUseKeyAction = 2074,
	C2S_PressedUseKeyAction = 2075,
	C2S_ReleaseUseKeyAction = 2076,
	S2C_ResponseUseKeyAction = 2077,
	S2C_AppearSkill = 2078,
	S2C_ReactionSkill = 2079,
	S2C_EndReactionSkill = 2080,
	S2C_SkillCoolTime = 2081,
	S2C_PushBuff = 2082,
	S2C_ReleaseBuff = 2083,
	S2C_DebugBox = 2084,
	S2C_DebugCircle = 2085,
	C2S_RequestEnterDungeon = 2086,
	S2C_RequestEnterDungeon = 2087,
	S2C_ResponseEnterDungeon = 2088,
	C2S_CompleteLoadDungeon = 2089,
	S2C_WaitingLoadDungeon = 2090,
	S2C_CompleteLoadDungeon = 2091,
	S2C_EnterPortal = 2092,
	S2C_LeavePortal = 2093,
	S2C_PlaySequence = 2094,
	C2S_SkipSequence = 2095,
	S2C_SkipSequence = 2096,
	S2C_EndSequence = 2097,
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
bool Handle_S2C_PlayerEndAutoAttack(ANetworkController* controller, Protocol::S2C_PlayerEndAutoAttack& pkt);
bool Handle_S2C_UpdateExperience(ANetworkController* controller, Protocol::S2C_UpdateExperience& pkt);
bool Handle_S2C_LevelUp(ANetworkController* controller, Protocol::S2C_LevelUp& pkt);
bool Handle_S2C_Chat(ANetworkController* controller, Protocol::S2C_Chat& pkt);
bool Handle_S2C_LoadFriendList(ANetworkController* controller, Protocol::S2C_LoadFriendList& pkt);
bool Handle_S2C_RequestFriend(ANetworkController* controller, Protocol::S2C_RequestFriend& pkt);
bool Handle_S2C_BlockFriend(ANetworkController* controller, Protocol::S2C_BlockFriend& pkt);
bool Handle_S2C_ConnectFriend(ANetworkController* controller, Protocol::S2C_ConnectFriend& pkt);
bool Handle_S2C_DisConnectFriend(ANetworkController* controller, Protocol::S2C_DisConnectFriend& pkt);
bool Handle_S2C_CreateParty(ANetworkController* controller, Protocol::S2C_CreateParty& pkt);
bool Handle_S2C_RequestEnterParty(ANetworkController* controller, Protocol::S2C_RequestEnterParty& pkt);
bool Handle_S2C_RequestParty(ANetworkController* controller, Protocol::S2C_RequestParty& pkt);
bool Handle_S2C_RequestLeaveParty(ANetworkController* controller, Protocol::S2C_RequestLeaveParty& pkt);
bool Handle_S2C_RequestLeaderParty(ANetworkController* controller, Protocol::S2C_RequestLeaderParty& pkt);
bool Handle_S2C_ResponeParty(ANetworkController* controller, Protocol::S2C_ResponeParty& pkt);
bool Handle_S2C_LoadParty(ANetworkController* controller, Protocol::S2C_LoadParty& pkt);
bool Handle_S2C_NotifyParty(ANetworkController* controller, Protocol::S2C_NotifyParty& pkt);
bool Handle_S2C_EnterPartyPlayer(ANetworkController* controller, Protocol::S2C_EnterPartyPlayer& pkt);
bool Handle_S2C_LeavePartyPlayer(ANetworkController* controller, Protocol::S2C_LeavePartyPlayer& pkt);
bool Handle_S2C_AppearItem(ANetworkController* controller, Protocol::S2C_AppearItem& pkt);
bool Handle_S2C_AppearArrow(ANetworkController* controller, Protocol::S2C_AppearArrow& pkt);
bool Handle_S2C_AppearProtal(ANetworkController* controller, Protocol::S2C_AppearProtal& pkt);
bool Handle_S2C_AppearObstruction(ANetworkController* controller, Protocol::S2C_AppearObstruction& pkt);
bool Handle_S2C_AppearNPC(ANetworkController* controller, Protocol::S2C_AppearNPC& pkt);
bool Handle_S2C_MovementProjectile(ANetworkController* controller, Protocol::S2C_MovementProjectile& pkt);
bool Handle_S2C_Teleport(ANetworkController* controller, Protocol::S2C_Teleport& pkt);
bool Handle_S2C_AppearEnemy(ANetworkController* controller, Protocol::S2C_AppearEnemy& pkt);
bool Handle_S2C_DetectChangeEnemy(ANetworkController* controller, Protocol::S2C_DetectChangeEnemy& pkt);
bool Handle_S2C_MovementEnemy(ANetworkController* controller, Protocol::S2C_MovementEnemy& pkt);
bool Handle_S2C_AnimationMovementEnemy(ANetworkController* controller, Protocol::S2C_AnimationMovementEnemy& pkt);
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
bool Handle_S2C_LoadSkillTree(ANetworkController* controller, Protocol::S2C_LoadSkillTree& pkt);
bool Handle_S2C_UpdateSkillTree(ANetworkController* controller, Protocol::S2C_UpdateSkillTree& pkt);
bool Handle_S2C_SetUseKeyAction(ANetworkController* controller, Protocol::S2C_SetUseKeyAction& pkt);
bool Handle_S2C_ResponseUseKeyAction(ANetworkController* controller, Protocol::S2C_ResponseUseKeyAction& pkt);
bool Handle_S2C_AppearSkill(ANetworkController* controller, Protocol::S2C_AppearSkill& pkt);
bool Handle_S2C_ReactionSkill(ANetworkController* controller, Protocol::S2C_ReactionSkill& pkt);
bool Handle_S2C_EndReactionSkill(ANetworkController* controller, Protocol::S2C_EndReactionSkill& pkt);
bool Handle_S2C_SkillCoolTime(ANetworkController* controller, Protocol::S2C_SkillCoolTime& pkt);
bool Handle_S2C_PushBuff(ANetworkController* controller, Protocol::S2C_PushBuff& pkt);
bool Handle_S2C_ReleaseBuff(ANetworkController* controller, Protocol::S2C_ReleaseBuff& pkt);
bool Handle_S2C_DebugBox(ANetworkController* controller, Protocol::S2C_DebugBox& pkt);
bool Handle_S2C_DebugCircle(ANetworkController* controller, Protocol::S2C_DebugCircle& pkt);
bool Handle_S2C_RequestEnterDungeon(ANetworkController* controller, Protocol::S2C_RequestEnterDungeon& pkt);
bool Handle_S2C_ResponseEnterDungeon(ANetworkController* controller, Protocol::S2C_ResponseEnterDungeon& pkt);
bool Handle_S2C_WaitingLoadDungeon(ANetworkController* controller, Protocol::S2C_WaitingLoadDungeon& pkt);
bool Handle_S2C_CompleteLoadDungeon(ANetworkController* controller, Protocol::S2C_CompleteLoadDungeon& pkt);
bool Handle_S2C_EnterPortal(ANetworkController* controller, Protocol::S2C_EnterPortal& pkt);
bool Handle_S2C_LeavePortal(ANetworkController* controller, Protocol::S2C_LeavePortal& pkt);
bool Handle_S2C_PlaySequence(ANetworkController* controller, Protocol::S2C_PlaySequence& pkt);
bool Handle_S2C_SkipSequence(ANetworkController* controller, Protocol::S2C_SkipSequence& pkt);
bool Handle_S2C_EndSequence(ANetworkController* controller, Protocol::S2C_EndSequence& pkt);

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
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_PlayerEndAutoAttack)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_PlayerEndAutoAttack>(Handle_S2C_PlayerEndAutoAttack, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_UpdateExperience)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_UpdateExperience>(Handle_S2C_UpdateExperience, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_LevelUp)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_LevelUp>(Handle_S2C_LevelUp, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_Chat)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_Chat>(Handle_S2C_Chat, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_LoadFriendList)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_LoadFriendList>(Handle_S2C_LoadFriendList, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_RequestFriend)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_RequestFriend>(Handle_S2C_RequestFriend, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_BlockFriend)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_BlockFriend>(Handle_S2C_BlockFriend, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_ConnectFriend)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_ConnectFriend>(Handle_S2C_ConnectFriend, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_DisConnectFriend)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_DisConnectFriend>(Handle_S2C_DisConnectFriend, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_CreateParty)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_CreateParty>(Handle_S2C_CreateParty, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_RequestEnterParty)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_RequestEnterParty>(Handle_S2C_RequestEnterParty, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_RequestParty)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_RequestParty>(Handle_S2C_RequestParty, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_RequestLeaveParty)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_RequestLeaveParty>(Handle_S2C_RequestLeaveParty, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_RequestLeaderParty)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_RequestLeaderParty>(Handle_S2C_RequestLeaderParty, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_ResponeParty)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_ResponeParty>(Handle_S2C_ResponeParty, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_LoadParty)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_LoadParty>(Handle_S2C_LoadParty, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_NotifyParty)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_NotifyParty>(Handle_S2C_NotifyParty, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_EnterPartyPlayer)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_EnterPartyPlayer>(Handle_S2C_EnterPartyPlayer, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_LeavePartyPlayer)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_LeavePartyPlayer>(Handle_S2C_LeavePartyPlayer, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AppearItem)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AppearItem>(Handle_S2C_AppearItem, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AppearArrow)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AppearArrow>(Handle_S2C_AppearArrow, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AppearProtal)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AppearProtal>(Handle_S2C_AppearProtal, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AppearObstruction)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AppearObstruction>(Handle_S2C_AppearObstruction, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AppearNPC)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AppearNPC>(Handle_S2C_AppearNPC, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_MovementProjectile)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_MovementProjectile>(Handle_S2C_MovementProjectile, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_Teleport)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_Teleport>(Handle_S2C_Teleport, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AppearEnemy)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AppearEnemy>(Handle_S2C_AppearEnemy, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_DetectChangeEnemy)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_DetectChangeEnemy>(Handle_S2C_DetectChangeEnemy, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_MovementEnemy)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_MovementEnemy>(Handle_S2C_MovementEnemy, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AnimationMovementEnemy)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AnimationMovementEnemy>(Handle_S2C_AnimationMovementEnemy, controller, buffer, len); };
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
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_LoadSkillTree)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_LoadSkillTree>(Handle_S2C_LoadSkillTree, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_UpdateSkillTree)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_UpdateSkillTree>(Handle_S2C_UpdateSkillTree, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_SetUseKeyAction)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_SetUseKeyAction>(Handle_S2C_SetUseKeyAction, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_ResponseUseKeyAction)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_ResponseUseKeyAction>(Handle_S2C_ResponseUseKeyAction, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_AppearSkill)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_AppearSkill>(Handle_S2C_AppearSkill, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_ReactionSkill)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_ReactionSkill>(Handle_S2C_ReactionSkill, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_EndReactionSkill)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_EndReactionSkill>(Handle_S2C_EndReactionSkill, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_SkillCoolTime)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_SkillCoolTime>(Handle_S2C_SkillCoolTime, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_PushBuff)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_PushBuff>(Handle_S2C_PushBuff, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_ReleaseBuff)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_ReleaseBuff>(Handle_S2C_ReleaseBuff, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_DebugBox)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_DebugBox>(Handle_S2C_DebugBox, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_DebugCircle)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_DebugCircle>(Handle_S2C_DebugCircle, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_RequestEnterDungeon)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_RequestEnterDungeon>(Handle_S2C_RequestEnterDungeon, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_ResponseEnterDungeon)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_ResponseEnterDungeon>(Handle_S2C_ResponseEnterDungeon, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_WaitingLoadDungeon)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_WaitingLoadDungeon>(Handle_S2C_WaitingLoadDungeon, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_CompleteLoadDungeon)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_CompleteLoadDungeon>(Handle_S2C_CompleteLoadDungeon, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_EnterPortal)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_EnterPortal>(Handle_S2C_EnterPortal, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_LeavePortal)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_LeavePortal>(Handle_S2C_LeavePortal, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_PlaySequence)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_PlaySequence>(Handle_S2C_PlaySequence, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_SkipSequence)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_SkipSequence>(Handle_S2C_SkipSequence, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_EndSequence)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_EndSequence>(Handle_S2C_EndSequence, controller, buffer, len); };
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
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_CreateParty& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_CreateParty)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_RequestEnterParty& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_RequestEnterParty)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_RequestLeaveParty& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_RequestLeaveParty)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_RequestLeaderParty& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_RequestLeaderParty)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_ResponeParty& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_ResponeParty)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_InteractiveObject& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_InteractiveObject)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_LoadInventory& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_LoadInventory)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_InsertInventory& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_InsertInventory)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_UpdateInventory& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_UpdateInventory)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_DeleteInventory& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_DeleteInventory)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_ReplaceEqipment& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_ReplaceEqipment)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_UpdateSkillTree& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_UpdateSkillTree)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_SetUseKeyAction& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_SetUseKeyAction)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_PressedUseKeyAction& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_PressedUseKeyAction)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_ReleaseUseKeyAction& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_ReleaseUseKeyAction)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_RequestEnterDungeon& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_RequestEnterDungeon)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_CompleteLoadDungeon& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_CompleteLoadDungeon)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_SkipSequence& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_SkipSequence)); }

};