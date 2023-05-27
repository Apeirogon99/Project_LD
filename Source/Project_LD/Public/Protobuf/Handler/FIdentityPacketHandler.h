#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Protobuf/Handler/FClientPacketHandler.h>

/*
enum class EPakcetID: uint16
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
};
*/

// Custom Handlers
bool Handle_S2C_EnterIdentityServer(ANetworkController* controller, Protocol::S2C_EnterIdentityServer& pkt);
bool Handle_S2C_LeaveIdentityServer(ANetworkController* controller, Protocol::S2C_LeaveIdentityServer& pkt);
bool Handle_S2C_Singin(ANetworkController* controller, Protocol::S2C_Singin& pkt);
bool Handle_S2C_Singup(ANetworkController* controller, Protocol::S2C_Singup& pkt);
bool Handle_S2C_EmailVerified(ANetworkController* controller, Protocol::S2C_EmailVerified& pkt);
bool Handle_S2C_LoadServer(ANetworkController* controller, Protocol::S2C_LoadServer& pkt);
bool Handle_S2C_SelectServer(ANetworkController* controller, Protocol::S2C_SelectServer& pkt);
bool Handle_S2C_StartGame(ANetworkController* controller, Protocol::S2C_StartGame& pkt);
bool Handle_S2C_LoadCharacters(ANetworkController* controller, Protocol::S2C_LoadCharacters& pkt);
bool Handle_S2C_CreateCharacter(ANetworkController* controller, Protocol::S2C_CreateCharacter& pkt);
bool Handle_S2C_DeleteCharacter(ANetworkController* controller, Protocol::S2C_DeleteCharacter& pkt);

class FIdentityPacketHandler
{
public:
	static void Init(PacketFunc inPacketFunc[UINT16_MAX])
	{
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_EnterIdentityServer)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_EnterIdentityServer>(Handle_S2C_EnterIdentityServer, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_LeaveIdentityServer)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_LeaveIdentityServer>(Handle_S2C_LeaveIdentityServer, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_Singin)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_Singin>(Handle_S2C_Singin, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_Singup)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_Singup>(Handle_S2C_Singup, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_EmailVerified)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_EmailVerified>(Handle_S2C_EmailVerified, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_LoadServer)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_LoadServer>(Handle_S2C_LoadServer, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_SelectServer)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_SelectServer>(Handle_S2C_SelectServer, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_StartGame)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_StartGame>(Handle_S2C_StartGame, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_LoadCharacters)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_LoadCharacters>(Handle_S2C_LoadCharacters, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_CreateCharacter)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_CreateCharacter>(Handle_S2C_CreateCharacter, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_DeleteCharacter)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_DeleteCharacter>(Handle_S2C_DeleteCharacter, controller, buffer, len); };
	}
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_EnterIdentityServer& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_EnterIdentityServer)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_LeaveIdentityServer& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_LeaveIdentityServer)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_Singin& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_Singin)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_Singup& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_Singup)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_EmailVerified& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_EmailVerified)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_LoadServer& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_LoadServer)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_SelectServer& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_SelectServer)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_StartGame& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_StartGame)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_LoadCharacters& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_LoadCharacters)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_CreateCharacter& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_CreateCharacter)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_DeleteCharacter& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_DeleteCharacter)); }

};