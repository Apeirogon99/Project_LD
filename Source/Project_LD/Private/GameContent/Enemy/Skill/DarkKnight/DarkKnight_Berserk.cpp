// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/DarkKnight/DarkKnight_Berserk.h"

// Sets default values
ADarkKnight_Berserk::ADarkKnight_Berserk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADarkKnight_Berserk::ActiveSkill(FVector InLocation, FRotator InRotation)
{
}

void ADarkKnight_Berserk::ReactionSkill(FVector InLocation, FRotator InRotation)
{
}

void ADarkKnight_Berserk::DeactiveSkill()
{
}

// Called when the game starts or when spawned
void ADarkKnight_Berserk::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADarkKnight_Berserk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

