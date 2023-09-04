// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_MultiCasting.h"

// Sets default values
ASkill_MultiCasting::ASkill_MultiCasting()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_MultiCasting::ActiveSkill(FVector InLocation, FRotator InRotation)
{
}

void ASkill_MultiCasting::ReactionSkill(FVector InLocation, FRotator InRotation)
{
}

void ASkill_MultiCasting::DeactiveSkill()
{
}

// Called when the game starts or when spawned
void ASkill_MultiCasting::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_MultiCasting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

