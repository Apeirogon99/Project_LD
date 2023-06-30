// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyController();
	~AEnemyController();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void Destroyed() override;

public:
	void MoveDestination(const FVector inOldMovementLocation, const FVector inNewMovementLocation, const int64 inTime);
	void MoveCorrection(const float inDeltaTime);

private:
	bool IsCorrection;
	FVector mTargetLoction;
};
