#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Protobuf/Handler/FClientPacketHandler.h>

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
	C2S_TravelServer = 1021,
	S2C_TravelServer = 1022,
};

// Custom Handlers
bool Handle_S2C_EnterIdentityServer(ANetworkController* controller, Protocol::S2C_EnterIdentityServer& pkt);
bool Handle_S2C_LeaveIdentityServer(ANetworkController* controller, Protocol::S2C_LeaveIdentityServer& pkt);
bool Handle_S2C_Singin(ANetworkController* controller, Protocol::S2C_Singin& pkt);
bool Handle_S2C_Singup(ANetworkController* controller, Protocol::S2C_Singup& pkt);
bool Handle_S2C_EmailVerified(ANetworkController* controller, Protocol::S2C_EmailVerified& pkt);
bool Handle_S2C_LoadServer(ANetworkController* controller, Protocol::S2C_LoadServer& pkt);
bool Handle_S2C_LoadCharacters(ANetworkController* controller, Protocol::S2C_LoadCharacters& pkt);
bool Handle_S2C_CreateCharacter(ANetworkController* controller, Protocol::S2C_CreateCharacter& pkt);
bool Handle_S2C_UpdateAppearance(ANetworkController* controller, Protocol::S2C_UpdateAppearance& pkt);
bool Handle_S2C_DeleteCharacter(ANetworkController* controller, Protocol::S2C_DeleteCharacter& pkt);
bool Handle_S2C_UpdateNickName(ANetworkController* controller, Protocol::S2C_UpdateNickName& pkt);
bool Handle_S2C_TravelServer(ANetworkController* controller, Protocol::S2C_TravelServer& pkt);

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
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_LoadCharacters)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_LoadCharacters>(Handle_S2C_LoadCharacters, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_CreateCharacter)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_CreateCharacter>(Handle_S2C_CreateCharacter, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_UpdateAppearance)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_UpdateAppearance>(Handle_S2C_UpdateAppearance, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_DeleteCharacter)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_DeleteCharacter>(Handle_S2C_DeleteCharacter, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_UpdateNickName)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_UpdateNickName>(Handle_S2C_UpdateNickName, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_TravelServer)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_TravelServer>(Handle_S2C_TravelServer, controller, buffer, len); };
	}
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_EnterIdentityServer& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_EnterIdentityServer)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_LeaveIdentityServer& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_LeaveIdentityServer)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_Singin& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_Singin)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_Singup& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_Singup)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_EmailVerified& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_EmailVerified)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_LoadCharacters& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_LoadCharacters)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_CreateCharacter& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_CreateCharacter)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_UpdateAppearance& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_UpdateAppearance)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_DeleteCharacter& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_DeleteCharacter)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_UpdateNickName& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_UpdateNickName)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_TravelServer& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_TravelServer)); }

};