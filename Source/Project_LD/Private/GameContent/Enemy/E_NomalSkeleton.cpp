// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/E_NomalSkeleton.h"

AE_NomalSkeleton::AE_NomalSkeleton()
{
}

AE_NomalSkeleton::~AE_NomalSkeleton()
{
}

void AE_NomalSkeleton::BeginPlay()
{
	Super::BeginPlay();
}

void AE_NomalSkeleton::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AE_NomalSkeleton::Destroyed()
{
	Super::Destroyed();
}

void AE_NomalSkeleton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AE_NomalSkeleton::Interactive(AC_Game* inPlayer)
{
}
