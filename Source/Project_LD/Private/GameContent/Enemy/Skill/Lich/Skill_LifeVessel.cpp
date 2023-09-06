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

// Called every frame
void ASkill_LifeVessel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

