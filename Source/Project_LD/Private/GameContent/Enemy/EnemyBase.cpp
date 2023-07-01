// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Enemy/EnemyBase.h"
#include "GameContent/Enemy/EnemyController.h"
#include "GameContent/Enemy/EnemyState.h"

#include "Components/CapsuleComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyCollision"));
}

AEnemyBase::~AEnemyBase()
{
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AEnemyBase::Destroyed()
{
	Super::Destroyed();

}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::Interactive(AC_Game* inPlayer)
{
	AEnemyState* state = GetPlayerState<AEnemyState>();
	if (state == nullptr)
	{
		return;
	}

	float damage = 10.f;

	FEnemyStatData stateData = state->GetEnemyCurrentStats();
	stateData.base_health -= damage;
	state->SetEnemyCurrentStats(stateData);

}