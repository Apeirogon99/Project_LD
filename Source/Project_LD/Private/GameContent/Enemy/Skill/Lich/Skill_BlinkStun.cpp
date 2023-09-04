// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_BlinkStun.h"

// Sets default values
ASkill_BlinkStun::ASkill_BlinkStun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_BlinkStun::ActiveSkill(FVector InLocation, FRotator InRotation)
{
}

void ASkill_BlinkStun::ReactionSkill(FVector InLocation, FRotator InRotation)
{
}

void ASkill_BlinkStun::DeactiveSkill()
{
}

// Called when the game starts or when spawned
void ASkill_BlinkStun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_BlinkStun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

