// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/GM_Game.h"
#include <Framework/Gameinstance/LDGameInstance.h>
#include <Game/C_Game.h>
#include <Game/PC_Game.h>
#include <Game/PS_Game.h>
#include <Game/GS_Game.h>
#include "GameFramework/SpectatorPawn.h"
#include <Widget/Handler/ClientHUD.h>

#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>
#include <Network/NetworkUtils.h>

#include <UObject/ConstructorHelpers.h>

AGM_Game::AGM_Game()
{

	static ConstructorHelpers::FClassFinder<AC_Game> character(TEXT("/Game/Blueprint/Framework/Game/BC_Game"));
	DefaultPawnClass		= character.Class;

	static ConstructorHelpers::FClassFinder<APC_Game> controller(TEXT("/Game/Blueprint/Framework/Game/BPC_Game"));
	PlayerControllerClass	= controller.Class;

	static ConstructorHelpers::FClassFinder<AGS_Game> gameState(TEXT("/Game/Blueprint/Framework/Game/BGS_Game"));
	GameStateClass			= gameState.Class;

	static ConstructorHelpers::FClassFinder<APS_Game> playerState(TEXT("/Game/Blueprint/Framework/Game/BPS_Game"));
	PlayerStateClass		= playerState.Class;

	static ConstructorHelpers::FClassFinder<ASpectatorPawn> spectator(TEXT("/Game/Blueprint/Framework/Game/BSP_Game"));
	SpectatorClass			= spectator.Class;
}

AGM_Game::~AGM_Game()
{
}

void AGM_Game::BeginPlay()
{
	Super::BeginPlay();
}

void AGM_Game::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGM_Game::InitNetwork()
{
	if (true == IsConnectedServer())
	{
		if (false == RequestKeepConnectServer(TEXT("116.41.116.247"), 10000))
		{
			NetworkGameModeLog(FString(TEXT("failed to requset keep connect server")));
		}
	}
	else
	{
		if (false == RequestConnectServer(TEXT("116.41.116.247"), 10000))
		{
			NetworkGameModeLog(FString(TEXT("failed to requset connect server")));
		}
	}
}

void AGM_Game::BeginNetwork()
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

	std::string token = UNetworkUtils::ConvertString(instance->mToken);

	Protocol::C2S_EnterGameServer enterPacket;
	enterPacket.set_token(token);
	controller->Send(FGamePacketHandler::MakeSendBuffer(controller, enterPacket));

	GetClientHUD()->ShowWidgetFromName(FString(TEXT("MainGame")));
}

ACharacter* AGM_Game::SpawnCharacter(FVector inLocation, FVector inVelocity, FRotator inRotator)
{
	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FRotator newRotator = inRotator;
		FVector newLocation = inLocation;
		
		AC_Game* Character = world->SpawnActor<AC_Game>(DefaultPawnClass, newLocation, newRotator, spawnParams);
		return Character;
	}

	return nullptr;
}
