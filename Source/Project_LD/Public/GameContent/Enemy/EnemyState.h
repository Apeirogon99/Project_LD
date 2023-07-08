// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Struct/Game/EnemyData.h"
#include <Protobuf/Packet/PacketStruct.pb.h>
#include "GameFramework/PlayerState.h"
#include "EnemyState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AEnemyState : public APlayerState
{
	GENERATED_BODY()

public:
	AEnemyState();
	~AEnemyState();

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;

public:
	void UpdateCurrentStats(const google::protobuf::RepeatedPtrField<Protocol::SStat>& inStats);

	void SetObjectID(const int64 inObjectID);
	void SetEnemyDatas(const FEnemyData& inEnemeyDatas);
	void SetEnemyCurrentStats(const FEnemyStatData& inEnemeyDatas);
	void SetEnemyStats(const FEnemyStatData& inEnemyStats);
	void SetEnemyState(const EEnemyStateType& inStateType, const float inStartTime);

public:
	const int64									GetObjectID()						{ return mObjectID; }
	const FEnemyData&					GetEnemyDatas()				{ return mDatas; }
	const FEnemyStatData&				GetEnemyCurrentStats()	{ return mCurrentStats; }
	const FEnemyStatData&				GetEnemyStats()					{ return mStats; }
	const EEnemyStateType&			GetCurrentStateType()		{ return mCurrentState; }
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | Datas")
	int64						mObjectID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | Datas")
	FEnemyData					mDatas;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | Stats")
	FEnemyStatData				mCurrentStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | Stats")
	FEnemyStatData				mStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | State")
	EEnemyStateType				mCurrentState;
};