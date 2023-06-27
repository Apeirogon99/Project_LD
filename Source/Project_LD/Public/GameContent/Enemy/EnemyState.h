// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Struct/Game/EnemyData.h>
#include "GameFramework/PlayerState.h"
#include "EnemyState.generated.h"

/**
 * 
 */
class UEnemyBaseState;

UCLASS()
class PROJECT_LD_API AEnemyState : public APlayerState
{
	GENERATED_BODY()

public:
	AEnemyState();
	~AEnemyState();

public:
	void SetEnemyDatas(const FEnemyData& inEnemeyDatas);
	void SetEnemyCurrentStats(const FEnemyStatData& inEnemeyDatas);
	void SetEnemyStats(const FEnemyStatData& inEnemyStats);
	void SetState(UEnemyBaseState* StateBase);

public:
	const FEnemyData& GetEnemyDatas()																	{ return mDatas; }
	const FEnemyStatData& GetEnemyCurrentStats()												{ return mCurrentStats; }
	const FEnemyStatData& GetEnemyStats()															{ return mStats; }
	const UEnemyBaseState* GetEnemyStateBase()													{ return mState; }

public:
	void Hit();
	void Attack();
	void Chase();
	void Kill();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | Datas")
	FEnemyData	mDatas;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | Stats")
	FEnemyStatData	mCurrentStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | Stats")
	FEnemyStatData	mStats;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;

private:
	UEnemyBaseState* mState;
};