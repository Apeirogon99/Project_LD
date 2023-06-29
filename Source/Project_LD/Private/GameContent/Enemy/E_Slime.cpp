// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/E_Slime.h"
#include <Framework/Game/GS_Game.h>
#include "GameContent/Enemy/EnemyStateBase.h"

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

void AE_Slime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AE_Slime::Interactive(AC_Game* inPlayer)
{
	AEnemyState* state = GetPlayerState<AEnemyState>();
	if (state == nullptr)
	{
		return;
	}
	if(!IsValid(state->GetEnemyStateBase()))
	{ 
		return;
	}

	float damage = 10.f;

	FEnemyStatData stateData = state->GetEnemyCurrentStats();
	stateData.base_health -= damage;
	state->SetEnemyCurrentStats(stateData);

	state->Hit();
}