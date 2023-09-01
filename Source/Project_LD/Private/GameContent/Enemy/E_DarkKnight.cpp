// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/E_DarkKnight.h"
#include "GameContent/Enemy/EnemyController.h"
#include "GameContent/Enemy/EnemyState.h"
#include <Framework/Game/GS_Game.h>

#include <Network/NetworkUtils.h>

AE_DarkKnight::AE_DarkKnight()
{
}

AE_DarkKnight::~AE_DarkKnight()
{
}

void AE_DarkKnight::BeginPlay()
{
	Super::BeginPlay();
}

void AE_DarkKnight::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AE_DarkKnight::Destroyed()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
	if (nullptr == gameState)
	{
		return;
	}

	AEnemyController* controller = Cast<AEnemyController>(GetController());
	if (nullptr == controller)
	{
		return;
	}

	AEnemyState* playerState = controller->GetPlayerState<AEnemyState>();
	if (nullptr == playerState)
	{
		return;
	}

	controller->UnPossess();

	gameState->RemovePlayerState(playerState);

	playerState->Destroy();

	world->DestroyActor(playerState);

	world->DestroyActor(controller);
}

void AE_DarkKnight::Tick(float DeltaTime)
{
}
