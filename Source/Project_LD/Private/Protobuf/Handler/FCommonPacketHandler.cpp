#include "FCommonPacketHandler.h"
#include <Framework/Gameinstance/LDGameInstance.h>
#include <Network/NetworkCharacter.h>
#include <Network/NetworkGameMode.h>
#include <Network/NetworkGameState.h>
#include <Network/NetworkPawn.h>
#include <Network/NetworkPlayerState.h>
#include <Network/NetworkService.h>
#include <Network/NetworkUtils.h>
#include <PacketUtils.h>
#include <Network/NetworkSession.h>
#include <Network/NetworkTimeStamp.h>

#include <Widget/WidgetUtils.h>
#include <Widget/Test/W_Test.h>

#include <DatabaseErrorTypes.h>

bool Handle_S2C_ReplicatedServerTimeStamp(ANetworkController* controller, Protocol::S2C_ReplicatedServerTimeStamp& pkt)
{

	UNetworkTimeStamp* timeStamp = controller->GetTimeStamp();
	if (timeStamp == nullptr)
	{
		return false;
	}

	const int64 serverTimeStamp = pkt.time_stamp();
	const int64 serverUtcTime = pkt.utc_time();
	const int64 rtt = pkt.rtt();
	timeStamp->UpdateTimeStamp(serverTimeStamp, serverUtcTime, rtt);

	return true;
}
