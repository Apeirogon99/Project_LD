// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_Explosion.h"

// Sets default values
ASkill_Explosion::ASkill_Explosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkill_Explosion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_Explosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

