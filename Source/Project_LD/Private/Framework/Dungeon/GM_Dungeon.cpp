// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Dungeon/GM_Dungeon.h"
#include <Framework/Gameinstance/LDGameInstance.h>
#include <Game/C_Game.h>
#include <Game/PC_Game.h>
#include <Game/PS_Game.h>
#include <Game/GS_Game.h>
#include <GameContent/Enemy/EnemyBase.h>
#include "GameFramework/SpectatorPawn.h"
#include <Widget/Handler/ClientHUD.h>

#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>
#include <Network/NetworkUtils.h>

#include <Struct/Identity/ServerData.h>

#include <UObject/ConstructorHelpers.h>

AGM_Dungeon::AGM_Dungeon()
{
	static ConstructorHelpers::FClassFinder<AC_Game> character(TEXT("/Game/Blueprint/Framework/Game/BC_Game"));
	DefaultPawnClass = character.Class;

	static ConstructorHelpers::FClassFinder<APC_Game> controller(TEXT("/Game/Blueprint/Framework/Game/BPC_Game"));
	PlayerControllerClass = controller.Class;

	static ConstructorHelpers::FClassFinder<AGS_Game> gameState(TEXT("/Game/Blueprint/Framework/Game/BGS_Game"));
	GameStateClass = gameState.Class;

	static ConstructorHelpers::FClassFinder<APS_Game> playerState(TEXT("/Game/Blueprint/Framework/Game/BPS_Game"));
	PlayerStateClass = playerState.Class;

	static ConstructorHelpers::FClassFinder<ASpectatorPawn> spectator(TEXT("/Game/Blueprint/Framework/Game/BSP_Game"));
	SpectatorClass = spectator.Class;
}

AGM_Dungeon::~AGM_Dungeon()
{
}

void AGM_Dungeon::BeginPlay()
{
	Super::BeginPlay();
}

void AGM_Dungeon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGM_Dungeon::InitNetwork()
{
	FString ip;
	int32 port;
#if NETWORK_LOCAL
	ip = FString(TEXT("116.41.116.247"));
	port = 10000;
#else
	//ip = FString(TEXT("125.180.66.59"));
	ip = FString(TEXT("127.0.0.1"));
	port = 10000;
#endif // Local

	ULDGameInstance* instance = Cast<ULDGameInstance>(GetGameInstance());
	if (nullptr == instance)
	{
		return;
	}

	UServerData* serverData = instance->GetServerData();
	if (serverData)
	{
		ip = serverData->GetServerIP();
		port = serverData->GetServerPort();
	}

	if (true == IsConnectedServer())
	{
		//this->RequestKeepConnectServer(ip, port);
		this->ProcessConnect(true);
	}
	else
	{
		if (false == RequestConnectServer(ip, port))
		{
			NetworkGameModeLog(FString(TEXT("failed to requset connect server")));
		}
	}
}

void AGM_Dungeon::BeginNetwork()
{
	Super::BeginNetwork();

	ANetworkController* controller = GetNetworkController();
	if (nullptr == controller)
	{
		return;
	}

	ULDGameInstance* instance = Cast<ULDGameInstance>(GetGameInstance());
	if (nullptr == instance)
	{
		return;
	}

	Protocol::C2S_CompleteLoadDungeon loadDungeon;
	controller->Send(FGamePacketHandler::MakeSendBuffer(controller, loadDungeon));

}

ACharacter* AGM_Dungeon::SpawnCharacter(FVector inLocation, FRotator inRotator)
{
	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AC_Game* Character = world->SpawnActor<AC_Game>(DefaultPawnClass, inLocation, inRotator, spawnParams);
		return Character;
	}

	return nullptr;
}

AController* AGM_Dungeon::CreateController()
{
	UWorld* world = GetWorld();
	if (world)
	{
		APC_Game* controller = world->SpawnActor<APC_Game>();
		return controller;
	}
	return nullptr;
}
