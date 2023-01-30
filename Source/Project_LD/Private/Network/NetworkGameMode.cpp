// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkGameMode.h"
#include <Network/NetworkService.h>
#include <Framework/Gameinstance/LDGameInstance.h>
#include <Kismet/GameplayStatics.h>

ANetworkGameMode::ANetworkGameMode()
{
	bUseSeamlessTravel = true;
}

ANetworkGameMode::~ANetworkGameMode()
{
}

bool ANetworkGameMode::RequestConnectServer(const FString& inIpAddr, const int32 inPort)
{
	uint16 port = static_cast<uint16>(inPort);

	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(GetGameInstance());
	if (nullptr == gameInstance)
	{
		return false;
	}

	UNetworkService* networkService = gameInstance->GetSubsystem<UNetworkService>();
	if (nullptr == networkService)
	{
		return false;
	}

	networkService->Connect(inIpAddr, inPort);

	return true;
}

bool ANetworkGameMode::RequestKeepConnect()
{
	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(GetGameInstance());
	if (nullptr == gameInstance)
	{
		return false;
	}

	UNetworkService* networkService = gameInstance->GetSubsystem<UNetworkService>();
	if (nullptr == networkService)
	{
		return false;
	}

	networkService->KeepConnect();

	return true;
}

bool ANetworkGameMode::IsConnected()
{
	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(GetGameInstance());
	if (nullptr == gameInstance)
	{
		return false;
	}

	UNetworkService* networkService = gameInstance->GetSubsystem<UNetworkService>();
	if (nullptr == networkService)
	{
		return false;
	}



	return false;
}

void ANetworkGameMode::RequestTravelLevel(const FString& inLevel)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*inLevel));
}

bool ANetworkGameMode::RequestExitGame(const bool inForce)
{
	FGenericPlatformMisc::RequestExit(inForce);
	return true;
}

void ANetworkGameMode::ProcessConnect()
{
}

void ANetworkGameMode::ProcessDisconnect()
{
}
