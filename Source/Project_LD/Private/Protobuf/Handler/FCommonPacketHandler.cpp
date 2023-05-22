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

	//서버의 UTC시간과 클라이언트의 UTC시간의 차이를 구함 (절대시간)
	const int64 serverUtcTimeStamp = pkt.utc_time();
	timeStamp->UpdateUtcDelta(serverUtcTimeStamp);
	const int64 utcTimeStampDelta = timeStamp->GetTimeStampDelta();

	//서버 시간
	const int64 serverTimeStamp = pkt.time_stamp();
	timeStamp->UpdateTimeStamp(serverTimeStamp);

	//보정 후 시간
	const int64 updateTimeStamp = (clientTimeStamp - serverTimeStamp);
	//timeStamp->UpdateTimeStamp(updateTimeStamp);

	//TEST Widget
	AClientHUD* clientHUD = Cast<AClientHUD>(controller->GetHUD());
	if (nullptr == clientHUD)
	{
		return false;
	}

	UW_Test* testWidget = nullptr;
	UUserWidget* outWidget = clientHUD->GetWidgetFromName(TEXT("Test"));
	if (outWidget)
	{
		testWidget = Cast<UW_Test>(outWidget);
		if (testWidget == nullptr)
		{
			return false;
		}

		testWidget->Update(clientTimeStamp, serverTimeStamp, utcTimeStampDelta, updateTimeStamp);
		return true;
	}

	return true;
}
