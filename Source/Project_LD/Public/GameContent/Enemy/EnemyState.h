// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Struct/Game/EnemyData.h"
#include "Struct/Game/CharacterDatas.h"
#include <Protobuf/Packet/PacketStruct.pb.h>
#include "GameFramework/PlayerState.h"
#include "EnemyState.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnHealthChanged)
DECLARE_MULTICAST_DELEGATE(FOnMovementSpeedChanged)

UCLASS()
class PROJECT_LD_API AEnemyState : public APlayerState
{
	GENERATED_BODY()

public:
	AEnemyState();
	~AEnemyState();

public:
	FOnHealthChanged						OnHealthChanged;
	FOnMovementSpeedChanged		OnMovementSpeedChanged;

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;

public:
	void UpdateCurrentStats(const google::protobuf::RepeatedPtrField<Protocol::SStat>& inStats);

	void SetObjectID(const int64 inObjectID);
	void SetEnemyDatas(const FEnemyData& inEnemeyDatas);
	void SetEnemyStats(const FEnemyStatData& inMaxData);
	void SetEnemyState(const EEnemyStateType& inStateType, const float inStartTime);

public:
	const int64									GetObjectID()							{ return mObjectID; }
	const FEnemyData&					GetEnemyDatas()					{ return mDatas; }
	UFUNCTION(BlueprintCallable)
	const FStatsData							GetEnemyStats()						{ return mStats.GetMaxStats(); }
	UFUNCTION(BlueprintCallable)
	const FStatsData							GetEnemyCurrentStats()		{ return mStats.GetCurrentStats(); }
	const EEnemyStateType&			GetCurrentStateType()			{ return mCurrentState; }
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | Datas")
	int64								mObjectID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | Datas")
	FEnemyData					mDatas;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | Stats")
	FCharacterStats				mStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | State")
	EEnemyStateType			mCurrentState;

private:
	void UpdateHealthBar();
	void UpdateMovementSpeed();
};