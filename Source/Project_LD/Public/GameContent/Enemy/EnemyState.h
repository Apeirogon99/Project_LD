// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Struct/Game/EnemyData.h>
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

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;

public:
	void SetEnemyDatas(const FEnemyData& inEnemeyDatas);
	void SetEnemyCurrentStats(const FEnemyStatData& inEnemeyDatas);
	void SetEnemyStats(const FEnemyStatData& inEnemyStats);

public:
	const FEnemyData& GetEnemyDatas() { return mDatas; }
	const FEnemyStatData& GetEnemyCurrentStats() { return mCurrentStats; }
	const FEnemyStatData& GetEnemeyStats() { return mStats; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | Datas")
		FEnemyData	mDatas;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | Stats")
		FEnemyStatData	mCurrentStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy | Stats")
		FEnemyStatData	mStats;
};
