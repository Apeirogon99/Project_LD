// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/DarkKnight/DarkKnight_HandSwordSwipeAttack.h"

// Sets default values
ADarkKnight_HandSwordSwipeAttack::ADarkKnight_HandSwordSwipeAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADarkKnight_HandSwordSwipeAttack::ActiveSkill(FVector InLocation, FRotator InRotation)
{
}

void ADarkKnight_HandSwordSwipeAttack::ReactionSkill(FVector InLocation, FRotator InRotation)
{
}

void ADarkKnight_HandSwordSwipeAttack::DeactiveSkill()
{
}

// Called when the game starts or when spawned
void ADarkKnight_HandSwordSwipeAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADarkKnight_HandSwordSwipeAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

