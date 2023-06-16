#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Protobuf/Handler/FClientPacketHandler.h>

/*
enum class EPakcetID: uint16
{
	C2S_ReplicatedServerTimeStamp = 9000,
	S2C_ReplicatedServerTimeStamp = 9001,
	C2S_TravelLevel = 9002,
	S2C_TravelLevel = 9003,
	C2S_TravelServer = 9004,
	S2C_TravelServer = 9005,
};
*/

// Custom Handlers
bool Handle_S2C_ReplicatedServerTimeStamp(ANetworkController* controller, Protocol::S2C_ReplicatedServerTimeStamp& pkt);
bool Handle_S2C_TravelLevel(ANetworkController* controller, Protocol::S2C_TravelLevel& pkt);
bool Handle_S2C_TravelServer(ANetworkController* controller, Protocol::S2C_TravelServer& pkt);

class FCommonPacketHandler
{
public:
	static void Init(PacketFunc inPacketFunc[UINT16_MAX])
	{
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_ReplicatedServerTimeStamp)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_ReplicatedServerTimeStamp>(Handle_S2C_ReplicatedServerTimeStamp, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_TravelLevel)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_TravelLevel>(Handle_S2C_TravelLevel, controller, buffer, len); };
		inPacketFunc[static_cast<uint16>(EPakcetID::S2C_TravelServer)] = [](ANetworkController* controller, BYTE* buffer, int32 len) { return FClientPacketHandler::HandlePacket<Protocol::S2C_TravelServer>(Handle_S2C_TravelServer, controller, buffer, len); };
	}
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_ReplicatedServerTimeStamp& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_ReplicatedServerTimeStamp)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_TravelLevel& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_TravelLevel)); }
	static SendBufferPtr MakeSendBuffer(ANetworkController* controller, Protocol::C2S_TravelServer& pkt) { return FClientPacketHandler::MakeSendBuffer(controller, pkt, static_cast<uint16>(EPakcetID::C2S_TravelServer)); }

};