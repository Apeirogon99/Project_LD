// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_RealmOfDeath.h"

// Sets default values
ASkill_RealmOfDeath::ASkill_RealmOfDeath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_RealmOfDeath::ActiveSkill(FVector InLocation, FRotator InRotation)
{
}

void ASkill_RealmOfDeath::ReactionSkill(FVector InLocation, FRotator InRotation)
{
}

void ASkill_RealmOfDeath::DeactiveSkill()
{
}

// Called when the game starts or when spawned
void ASkill_RealmOfDeath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_RealmOfDeath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

