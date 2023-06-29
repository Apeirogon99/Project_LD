// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/EnemyState.h"
#include "GameContent/Enemy/EnemyStateBase.h"


AEnemyState::AEnemyState()
{
}

AEnemyState::~AEnemyState()
{

}

void AEnemyState::BeginPlay()
{
	Super::BeginPlay();

	mState = NewObject<AEnemyStateMachine>();
	mStateType = EEnemyStateType::Idle;
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

void AEnemyState::SetState(EEnemyStateType Type)
{
	mStateType = Type;
}

AEnemyStateMachine* AEnemyState::GetEnemyStateBase()
{
	return mState;
}

void AEnemyState::Idle()
{
	mState->Idle();
	SetState(mState->GetType());
}

void AEnemyState::Hit()
{
	mState->Hit();
	auto a = mState->GetType();
	SetState(a);
}

void AEnemyState::Attack()
{
	mState->Attack();
	SetState(mState->GetType());
}

void AEnemyState::Chase()
{
	mState->Chase();
	SetState(mState->GetType());
}

void AEnemyState::Kill()
{
	mState->Kill();
	SetState(mState->GetType());
}
