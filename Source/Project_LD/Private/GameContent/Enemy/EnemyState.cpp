// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/EnemyState.h"
#include "GameContent/Enemy/EnemyStateBase.h"


AEnemyState::AEnemyState()
{
	mState = UEnemyIdleState::GetInstance();
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

void AEnemyState::SetEnemyCurrentStats(const FEnemyStatData& inEnemeyDatas)
{
	mCurrentStats = inEnemeyDatas;
}

void AEnemyState::SetEnemyStats(const FEnemyStatData& inEnemyStats)
{
	mStats = inEnemyStats;
}

void AEnemyState::SetState(UEnemyBaseState* StateBase)
{
	mState = StateBase;
}

void AEnemyState::Hit()
{
	mState->Hit(this);
}

void AEnemyState::Attack()
{
	mState->Attack(this);
}

void AEnemyState::Chase()
{
	mState->Chase(this);
}

void AEnemyState::Kill()
{
	mState->Kill(this);
}
