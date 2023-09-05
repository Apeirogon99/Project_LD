// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_LifeVessel.h"
#include "GameContent/Enemy/EnemyController.h"
#include "GameContent/Enemy/EnemyState.h"
#include <Framework/Game/GS_Game.h>

#include <Network/NetworkUtils.h>

// Sets default values
ASkill_LifeVessel::ASkill_LifeVessel()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ASkill_LifeVessel::ActiveSkill(FVector InLocation, FRotator InRotation)
{
}

void ASkill_LifeVessel::ReactionSkill(FVector InLocation, FRotator InRotation)
{
}

void ASkill_LifeVessel::DeactiveSkill()
{
}

// Called when the game starts or when spawned
void ASkill_LifeVessel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkill_LifeVessel::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASkill_LifeVessel::Destroyed()
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

// Called every frame
void ASkill_LifeVessel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

