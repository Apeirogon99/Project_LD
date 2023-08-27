// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkController.h"
#include "MovementController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AMovementController : public ANetworkController
{
	GENERATED_BODY()

public:
	AMovementController();
	~AMovementController();
	
public:
	void PlayerTick(float DeltaTime) override;
	void SetupInputComponent() override;

	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void OnSetCameraZoomAxis(const float inValue);

public:
	void SwitchMovementMode();
	void MoveToMouseCursor();

public:
	void SetNewMoveDestination(FVector& DestLocation);
	void MoveDestination(const FVector& inOldMovementLocation, const FVector& inNewMovementLocation, const int64& inTime);
	void MoveCorrection(const float inDeltaTime);
	void RotationDestination(const FRotator& inNewRotation, const int64& inTime);
	void RotationCorrection(const float inDeltaTime);

	void StopMovementController(const FVector& inStopLocation);

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UParticleSystem* mMouseCursorParticle;

private:
	bool		mIsMoveToMouseCursor;
	bool		mIsLocationCorrection;
	bool		mIsRotationCorrection;

	FVector		mTargetLoction;
	FRotator	mTargetRotation;

	float		mCorrectionVelocity;
};
