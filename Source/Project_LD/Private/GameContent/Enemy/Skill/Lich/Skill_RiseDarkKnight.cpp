// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_RiseDarkKnight.h"

// Sets default values
ASkill_RiseDarkKnight::ASkill_RiseDarkKnight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_RiseDarkKnight::ActiveSkill(FVector InLocation, FRotator InRotation)
{
}

void ASkill_RiseDarkKnight::ReactionSkill()
{
}

void ASkill_RiseDarkKnight::DeactiveSkill()
{
}

// Called when the game starts or when spawned
void ASkill_RiseDarkKnight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_RiseDarkKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

