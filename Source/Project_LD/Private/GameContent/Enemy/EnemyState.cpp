// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/EnemyState.h"

AEnemyState::AEnemyState()
{
}

AEnemyState::~AEnemyState()
{
}

void AEnemyState::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AEnemyState::Destroyed()
{
	Super::Destroyed();
}

void AEnemyState::SetEnemyDatas(const FEnemyData& inEnemeyDatas)
{
	mDatas = inEnemeyDatas;
}

void AEnemyState::SetEnemyStats(const FEnemyStatData& inEnemyStats)
{
	mStats = inEnemyStats;
}
