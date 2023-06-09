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

	//클라이언트가 유추한 시간
	const int64 clientTimeStamp = timeStamp->GetServerTimeStamp();
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("Prediction [%lld] - [%lld] = [%lld]"), clientTimeStamp, pkt.time_stamp(), clientTimeStamp - pkt.time_stamp()), ELogLevel::Warning);

	//서버 시간으로 업데이트
	const int64 serverTimeStamp = pkt.time_stamp();
	const int64 serverUtcTime = pkt.utc_time();
	timeStamp->UpdateTimeStamp(serverTimeStamp, serverUtcTime);

	return true;
}
