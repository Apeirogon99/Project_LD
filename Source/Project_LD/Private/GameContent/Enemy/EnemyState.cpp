// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/EnemyState.h"
#include "GameContent/Enemy/EnemyController.h"
#include "GameContent/Enemy/EnemyBase.h"

#include <Struct/Game/EnemyData.h>
#include <Struct/Game/CharacterDatas.h>
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

	if (OnStatsChanged.IsBound())
	{
		OnStatsChanged.Broadcast();
	}
}

void AEnemyState::Destroyed()
{
	Super::Destroyed();
}

void AEnemyState::UpdateCurrentStats(const google::protobuf::RepeatedPtrField<Protocol::SStat>& inStats)
{
	const int32 maxSize = inStats.size();
	for (int32 index = 0; index < maxSize; ++index)
	{
		const Protocol::SStat&	stat = inStats.Get(index);
		ECharacterStatus		type = StaticCast<ECharacterStatus>(stat.stat_type()); //EStatsType
		const float					value = stat.stat_value();

		mStats.UpdateStats(type, value);
	}
	UpdateHealthBar();
}

void AEnemyState::SetObjectID(const int64 inObjectID)
{
	mObjectID = inObjectID;
}

void AEnemyState::SetEnemyDatas(const FEnemyData& inEnemeyDatas)
{
	mDatas = inEnemeyDatas;
}

void AEnemyState::SetEnemyStats(const FEnemyStatData& inEnemyStats)
{
	FEnemyBaseStats EnemyStat;
	EnemyStat.SetStatsBaseData(inEnemyStats);

	mStats.FloatToFData(EnemyStat.FDataToFloat());
	mStats.SetCurrentStats(mStats.GetMaxStats());
}

void AEnemyState::SetEnemyState(const EEnemyStateType& inStateType, const float inStartTime)
{
	if (EEnemyStateType::State_Unspecified == mCurrentState)
	{
		mCurrentState = inStateType;
	}

	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("Change state [%d] -> [%d] [Duration %f]"), StaticCast<int32>(mCurrentState), StaticCast<int32>(inStateType), inStartTime), ELogLevel::Warning);

	AEnemyBase* enemy = Cast<AEnemyBase>(GetPawn());
	if (nullptr == enemy)
	{
		return;
	}

	mCurrentState = inStateType;

	enemy->ChangeState(mCurrentState, inStartTime);
}

float AEnemyState::GetHealthBarPercent() const
{
	return HealthBarPercent;
}

void AEnemyState::UpdateHealthBar()
{
	HealthBarPercent = mStats.GetCurrentStats().GetHealth() / mStats.GetMaxStats().GetHealth();
	if (OnStatsChanged.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("AEnemyState::UpdateHealthBar"));
		OnStatsChanged.Broadcast();
	}
}
