#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Protobuf/Handler/FClientPacketHandler.h>

enum class EPakcetID: uint16
{
	S2C_EnterServer = 1000,
	S2C_LeaveServer = 1001,
	C2S_Singin = 1002,
	S2C_Singin = 1003,
	C2S_Singup = 1004,
	S2C_Singup = 1005,
	C2S_EmailVerified = 1006,
	S2C_EmailVerified = 1007,
	C2S_Nickname = 1008,
	S2C_Nickname = 1009,
};

// Custom Handlers
bool Handle_S2C_EnterServer(ANetworkController* controller, Protocol::S2C_EnterServer& pkt);
bool Handle_S2C_LeaveServer(ANetworkController* controller, Protocol::S2C_LeaveServer& pkt);
bool Handle_S2C_Singin(ANetworkController* controller, Protocol::S2C_Singin& pkt);
bool Handle_S2C_Singup(ANetworkController* controller, Protocol::S2C_Singup& pkt);
bool Handle_S2C_EmailVerified(ANetworkController* controller, Protocol::S2C_EmailVerified& pkt);
bool Handle_S2C_Nickname(ANetworkController* controller, Protocol::S2C_Nickname& pkt);

class FIdentityPacketHandler
{
public:
	static void Init(PacketFunc inPacketFunc[UINT16_MAX])
	{
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_EnterServer)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_EnterServer>(Handle_S2C_EnterServer, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_LeaveServer)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_LeaveServer>(Handle_S2C_LeaveServer, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_Singin)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_Singin>(Handle_S2C_Singin, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_Singup)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_Singup>(Handle_S2C_Singup, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_EmailVerified)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_EmailVerified>(Handle_S2C_EmailVerified, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_Nickname)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_Nickname>(Handle_S2C_Nickname, controller, buffer, len); };
	}
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_Singin& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_Singin)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_Singup& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_Singup)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_EmailVerified& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_EmailVerified)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_Nickname& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_Nickname)); }

};