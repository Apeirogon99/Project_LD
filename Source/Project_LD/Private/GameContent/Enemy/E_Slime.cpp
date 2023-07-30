// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/E_Slime.h"
#include "GameContent/Enemy/EnemyController.h"
#include "GameContent/Enemy/EnemyState.h"
#include <Framework/Game/GS_Game.h>

#include <Network/NetworkUtils.h>

AE_Slime::AE_Slime()
{
}

AE_Slime::~AE_Slime()
{
}

void AE_Slime::BeginPlay()
{
	Super::BeginPlay();
}

void AE_Slime::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AE_Slime::Destroyed()
{

	Super::Destroyed();

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

	//Super::Destroyed();

}

void AE_Slime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}