// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/EnemyState.h"
#include "GameContent/Enemy/EnemyController.h"
#include "GameContent/Enemy/EnemyBase.h"

#include <Network/NetworkUtils.h>

AEnemyState::AEnemyState()
{
}

AEnemyState::~AEnemyState()
{

}

void AEnemyState::BeginPlay()
{
	Super::BeginPlay();
	mCurrentState = EEnemyStateType::State_Unspecified;
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

void AEnemyState::SetEnemyState(const EEnemyStateType& inStateType)
{
	if (EEnemyStateType::State_Unspecified == mCurrentState)
	{
		mCurrentState = inStateType;
	}

	if (inStateType == mCurrentState)
	{
		return;
	}

	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("Change state [%d] -> [%d]"), StaticCast<int32>(mCurrentState), StaticCast<int32>(inStateType)), ELogLevel::Warning);

	AEnemyBase* enemy = Cast<AEnemyBase>(GetPawn());
	if (nullptr == enemy)
	{
		return;
	}

	mCurrentState = inStateType;

	float time = 0.0f;
	enemy->ChangeState(mCurrentState, time);

}
