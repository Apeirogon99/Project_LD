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
}

AEnemyController::~AEnemyController()
{

}

void AEnemyController::Destroyed()
{

}

void AEnemyController::Tick(float DeltaTime)
{
	if (IsCorrection)
	{
		MoveCorrection(DeltaTime);
	}
}

void AEnemyController::MoveDestination(const FVector inOldMovementLocation, const FVector inNewMovementLocation, const int64 inTime)
{
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

	FVector	direction = inNewMovementLocation - inOldMovementLocation;
	direction.Normalize();

	FVector velocity = direction * enemyState->GetEnemyStats().GetMovementSpeed();
	float	duration = inTime / 1000.0f;

	FVector deadReckoningLocation = inOldMovementLocation + (velocity * duration);

	//현재 위치와 비교하여 차이가 얼마나 나는지 판단
	FVector curLocation = pawn->GetActorLocation();
	float locationDistance = FVector::Dist2D(curLocation, deadReckoningLocation);
	if (locationDistance >= 5.0f)
	{
		IsCorrection = true;
		mTargetLoction = inOldMovementLocation;
	}
	else
	{
		IsCorrection = true;
		mTargetLoction = deadReckoningLocation;
	}

	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("cur[%ws], dead[%ws], new[%ws] distance %f"), *inOldMovementLocation.ToString(), *deadReckoningLocation.ToString(), *inNewMovementLocation.ToString(), locationDistance), ELogLevel::Error);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, inNewMovementLocation);

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
	float	velocity = 3.0f;

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
