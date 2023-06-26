// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/E_WarriorSkeleton.h"

AE_WarriorSkeleton::AE_WarriorSkeleton()
{
}

AE_WarriorSkeleton::~AE_WarriorSkeleton()
{
}

void AE_WarriorSkeleton::BeginPlay()
{
	Super::BeginPlay();
}

void AE_WarriorSkeleton::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AE_WarriorSkeleton::Destroyed()
{
	Super::Destroyed();
}

void AE_WarriorSkeleton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AE_WarriorSkeleton::Interactive(AC_Game* inPlayer)
{
}
