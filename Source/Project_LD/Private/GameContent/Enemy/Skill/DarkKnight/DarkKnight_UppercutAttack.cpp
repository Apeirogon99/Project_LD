// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/DarkKnight/DarkKnight_UppercutAttack.h"

// Sets default values
ADarkKnight_UppercutAttack::ADarkKnight_UppercutAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADarkKnight_UppercutAttack::ActiveSkill(FVector InLocation, FRotator InRotation)
{
}

void ADarkKnight_UppercutAttack::ReactionSkill(FVector InLocation, FRotator InRotation)
{
}

void ADarkKnight_UppercutAttack::DeactiveSkill(FVector InLocation, FRotator InRotation)
{
}

// Called when the game starts or when spawned
void ADarkKnight_UppercutAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADarkKnight_UppercutAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

