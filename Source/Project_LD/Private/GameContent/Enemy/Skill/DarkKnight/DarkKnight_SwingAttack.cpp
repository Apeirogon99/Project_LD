// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/DarkKnight/DarkKnight_SwingAttack.h"

// Sets default values
ADarkKnight_SwingAttack::ADarkKnight_SwingAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADarkKnight_SwingAttack::ActiveSkill(FVector InLocation, FRotator InRotation)
{
}

void ADarkKnight_SwingAttack::ReactionSkill(FVector InLocation, FRotator InRotation)
{
}

void ADarkKnight_SwingAttack::DeactiveSkill()
{
}

// Called when the game starts or when spawned
void ADarkKnight_SwingAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADarkKnight_SwingAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

