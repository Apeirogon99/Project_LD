// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/DarkKnight/DarkKnight_SwingAndSlamAttack.h"

// Sets default values
ADarkKnight_SwingAndSlamAttack::ADarkKnight_SwingAndSlamAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADarkKnight_SwingAndSlamAttack::ActiveSkill(FVector InLocation, FRotator InRotation)
{
}

void ADarkKnight_SwingAndSlamAttack::ReactionSkill(FVector InLocation, FRotator InRotation)
{
}

void ADarkKnight_SwingAndSlamAttack::DeactiveSkill(FVector InLocation, FRotator InRotation)
{
}

// Called when the game starts or when spawned
void ADarkKnight_SwingAndSlamAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADarkKnight_SwingAndSlamAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

