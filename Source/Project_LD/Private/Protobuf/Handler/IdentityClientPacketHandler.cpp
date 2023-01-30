// Fill out your copyright notice in the Description page of Project Settings.


#include "Protobuf/Handler/IdentityClientPacketHandler.h"
#include <Framework/Gameinstance/LDGameInstance.h>
#include <Network/NetworkCharacter.h>
#include <Network/NetworkGameMode.h>
#include <Network/NetworkGameState.h>
#include <Network/NetworkPawn.h>
#include <Network/NetworkPlayerState.h>
#include <Network/NetworkService.h>
#include <Network/NetworkUtils.h>
#include <Network/NetworkSession.h>

#include <Framework/Identity/IdentityGameMode.h>
#include <Framework/Identity/IdentityPlayerController.h>

//PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(ANetworkController* session, BYTE* buffer, int32 len)
{
	UNetworkUtils::NetworkConsoleLog("PacketHandle : Handle_INVALID", ELogLevel::Error);
	return true;
}

bool Handle_S2C_Singin(ANetworkController* session, Protocol::S2C_Singin& pkt)
{
	AIdentityPlayerController* controller = Cast<AIdentityPlayerController>(session);
	if (nullptr == controller)
	{
		return false;
	}

	ULDGameInstance* gameInstance =  Cast<ULDGameInstance>(controller->GetGameInstance());
	if (nullptr == gameInstance)
	{
		return false;
	}

	int32	error = pkt.error();
	FString ticket = pkt.id_token().c_str();

	gameInstance->mTicket = ticket;
	
	AGameModeBase* gameMode = session->GetWorld()->GetAuthGameMode();
	ANetworkGameMode* networkGameMode = Cast<ANetworkGameMode>(gameMode);

	//networkGameMode->RequestTravelLevel("L_SelectCharacter");
	networkGameMode->RequestTravelLevel("L_CustomCharacter");

	return true;
}

bool Handle_S2C_Singup(ANetworkController* session, Protocol::S2C_Singup& pkt)
{
	return true;
}

bool Handle_S2C_EmailVerified(ANetworkController* session, Protocol::S2C_EmailVerified& pkt)
{
	return true;
}
