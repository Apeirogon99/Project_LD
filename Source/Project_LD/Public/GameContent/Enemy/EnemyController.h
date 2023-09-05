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

	UFUNCTION(BlueprintNativeEvent)
		void OnTeleport(const FVector& DestLocation);
	virtual void OnTeleport_Implementation(const FVector& DestLocation);

public:
	void MoveDestination(const FVector inOldMovementLocation, const FVector inNewMovementLocation, const int64 inTime);
	void AnimationMoveDestination(const FVector inStartLocation, const FVector inEndLocation, const int64 inMoveDuration, const int64 inTimeDuration);
	void MoveCorrection(const float inDeltaTime);
	void RotationCorrection(const float inDeltaTime);

private:
	bool IsMoveCorrection;
	bool IsLocationCorrection;
	bool IsRotationCorrection;
	bool mTeleport;

	FVector mStartLocation;
	FVector mTargetLoction;
	FRotator mTargetRotation;

	float mStartTime;
	float mTimeElapsed;

	float mTeleportCool;
	float mCorrectionVelocity;
};
