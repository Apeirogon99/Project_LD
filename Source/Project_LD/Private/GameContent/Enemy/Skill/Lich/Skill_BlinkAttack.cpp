// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_BlinkAttack.h"

// Sets default values
ASkill_BlinkAttack::ASkill_BlinkAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkill_BlinkAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_BlinkAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

