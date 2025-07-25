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
		return true;
	}

	int64 predict = timeStamp->GetServerTimeStamp();

	const int64 serverTimeStamp = pkt.time_stamp();

	const int64 serverUtcTime	= pkt.utc_time();
	const int64 clinetUtcTime	= timeStamp->GetUtcTimeStmap();

	const int64 rtt				= clinetUtcTime - serverUtcTime;
	
	if (false == timeStamp->IsInit())
	{
		timeStamp->InitTimeStamp(serverTimeStamp, clinetUtcTime, rtt);
		//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("InitTimeStamp")), ELogLevel::Warning);
	}
	else
	{
		if (predict - serverTimeStamp <= 500 && rtt <= 500)
		{
			timeStamp->UpdateTimeStamp(serverTimeStamp, clinetUtcTime, rtt);
		}
	}

	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[SUTC::%lld] [CUTC::%lld]"), serverUtcTime, clinetUtcTime), ELogLevel::Warning);
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[RTT::%lld] [HRTT::%lld] [CRTT::%lld]"), timeStamp->GetRTT(), timeStamp->GetRTT() / 2, rtt), ELogLevel::Warning);
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Server : %lld] - [Client : %lld] = [Diff : %lld]"), serverTimeStamp, predict, predict - serverTimeStamp), ELogLevel::Warning);

	return true;
}

bool Handle_S2C_TravelLevel(ANetworkController* controller, Protocol::S2C_TravelLevel& pkt)
{
	UWorld* world = controller->GetWorld();
	if (nullptr == world)
	{
		return false;
	}

	ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
	if (nullptr == gameMode)
	{
		return false;
	}
	FString level = UNetworkUtils::ConvertFString(pkt.level());
	gameMode->RequestTravelLevel(level);

	UNetworkTimeStamp* timeStamp = controller->GetTimeStamp();
	if (timeStamp == nullptr)
	{
		return true;
	}

	return true;
}

bool Handle_S2C_TravelServer(ANetworkController* controller, Protocol::S2C_TravelServer& pkt)
{
	return true;
}

bool Handle_S2C_StateServer(ANetworkController* controller, Protocol::S2C_StateServer& pkt)
{
	return true;
}
