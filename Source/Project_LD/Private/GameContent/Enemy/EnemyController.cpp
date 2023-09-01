// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/EnemyController.h"
#include "GameContent/Enemy/EnemyState.h"
#include "GameContent/Enemy/EnemyBase.h"

#include <Network/NetworkUtils.h>

#include <GameFramework/PawnMovementComponent.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>

AEnemyController::AEnemyController()
{
	IsCorrection = false;
	mTeleport = false;
	mCorrectionVelocity = 0.0f;
}

AEnemyController::~AEnemyController()
{

}

void AEnemyController::Destroyed()
{

}

void AEnemyController::Tick(float DeltaTime)
{

	if (mTeleport)
	{
		static float tpTime = 0.0f;
		tpTime += DeltaTime;
		if (tpTime >= 1.0f)
		{
			mTeleport = false;
		}
		tpTime = 0.0f;
	}
	else
	{
		if (IsCorrection)
		{
			MoveCorrection(DeltaTime);
		}
	}

}

void AEnemyController::OnTeleport_Implementation(const FVector& DestLocation)
{
	APawn* pawn = this->GetPawn();
	if (nullptr == pawn)
	{
		return;
	}

	mTargetLoction = DestLocation;
	IsCorrection = false;
	mTeleport = true;

	pawn->GetMovementComponent()->StopActiveMovement();

	pawn->SetActorLocation(DestLocation, false, nullptr, ETeleportType::ResetPhysics);
}

void AEnemyController::MoveDestination(const FVector inOldMovementLocation, const FVector inNewMovementLocation, const int64 inTime)
{
	if (mTeleport)
	{
		return;
	}

	APawn* pawn = this->GetPawn();
	if (nullptr == pawn)
	{
		return;
	}

	AEnemyState* enemyState = GetPlayerState<AEnemyState>();
	if (nullptr == enemyState)
	{
		return;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, inNewMovementLocation);

	float movedistance = FVector::Dist(inOldMovementLocation, inNewMovementLocation);
	if (movedistance < 1.0f)
	{
		pawn->SetActorLocation(inNewMovementLocation, false, nullptr, ETeleportType::ResetPhysics);
		return;
	}

	FVector	direction = inNewMovementLocation - inOldMovementLocation;
	FRotator rotation = direction.Rotation();
	FVector foward = rotation.Quaternion().GetForwardVector();

	const float speed = enemyState->GetEnemyStats().GetMovementSpeed();
	FVector velocity = foward * speed;
	float	duration = inTime / 1000.0f;

	FVector deadReckoningLocation = inOldMovementLocation + (velocity * duration);

	//현재 위치와 비교하여 차이가 얼마나 나는지 판단
	FVector curLocation = pawn->GetActorLocation();
	float locationDistance = FVector::Dist2D(curLocation, deadReckoningLocation);
	if (locationDistance > 1.0f)
	{
		IsCorrection = true;
		mTargetLoction = deadReckoningLocation;
		pawn->SetActorRotation(direction.Rotation());
	}

	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("cur[%ws], dead[%ws], new[%ws] distance[%f]"), *inOldMovementLocation.ToString(), *deadReckoningLocation.ToString(), *inNewMovementLocation.ToString(), locationDistance), ELogLevel::Error);


}

void AEnemyController::MoveCorrection(const float inDeltaTime)
{
	APawn* pawn = this->GetPawn();
	if (nullptr == pawn)
	{
		return;
	}

	if (false == IsCorrection)
	{
		return;
	}

	FVector curLocation = pawn->GetActorLocation();
	float	velocity = 0.2f;

	FVector correctionLocation = FMath::VInterpTo(curLocation, mTargetLoction, inDeltaTime, velocity);

	float distance = FVector::Dist2D(curLocation, correctionLocation);
	if (distance <= 1.0f)
	{
		pawn->SetActorLocation(mTargetLoction, false, nullptr, ETeleportType::ResetPhysics);
		IsCorrection = false;
	}
	else
	{
		pawn->SetActorLocation(correctionLocation, false, nullptr, ETeleportType::ResetPhysics);
	}

}
