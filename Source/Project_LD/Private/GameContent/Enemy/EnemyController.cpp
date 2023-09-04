// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/EnemyController.h"
#include "GameContent/Enemy/EnemyState.h"
#include "GameContent/Enemy/EnemyBase.h"

#include <Network/NetworkUtils.h>

#include <GameFramework/PawnMovementComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <Kismet/KismetMathLibrary.h>

AEnemyController::AEnemyController()
{
	IsCorrection = false;
	IsRotationCorrection = false;
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

		if (IsRotationCorrection)
		{
			RotationCorrection(DeltaTime);
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

	ACharacter* character = Cast<ACharacter>(pawn);
	if (nullptr == pawn)
	{
		return;
	}

	AEnemyState* enemyState = GetPlayerState<AEnemyState>();
	if (nullptr == enemyState)
	{
		return;
	}
	const float speed = enemyState->GetEnemyStats().GetMovementSpeed();
	character->GetCharacterMovement()->MaxWalkSpeed = speed;

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

	//FVector velocity = foward * speed;
	FVector velocity = character->GetVelocity();
	float	duration = inTime / 1000.0f;

	FVector deadReckoningLocation = inOldMovementLocation + (velocity * duration);

	//현재 위치와 비교하여 차이가 얼마나 나는지 판단
	FVector curLocation = character->GetActorLocation();
	float locationDistance = FVector::Dist2D(curLocation, deadReckoningLocation);
	if (locationDistance > 1.0f)
	{
		IsCorrection = true;
		mTargetLoction = deadReckoningLocation;
		mCorrectionVelocity = 0.2f;
	}

	IsRotationCorrection = true;
	mTargetRotation = direction.Rotation();

	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("cur[%ws], dead[%ws], new[%ws] distance[%f]"), *inOldMovementLocation.ToString(), *deadReckoningLocation.ToString(), *inNewMovementLocation.ToString(), locationDistance), ELogLevel::Error);


}

void AEnemyController::AnimationMoveDestination(const FVector inStartLocation, const FVector inEndLocation, const int64 inMoveDuration, const int64 inTimeDuration)
{
	APawn* pawn = this->GetPawn();
	if (nullptr == pawn)
	{
		return;
	}

	ACharacter* character = Cast<ACharacter>(pawn);
	if (nullptr == pawn)
	{
		return;
	}

	FRotator	direction = (inEndLocation - inStartLocation).Rotation();
	FVector		foward = direction.Quaternion().GetForwardVector();

	float		moveDuration = inMoveDuration / 1000.0f;
	float		timeDuration = inTimeDuration / 1000.0f;

	float		speed = (FVector::Distance(inStartLocation, inEndLocation)) / moveDuration;

	FVector velocity = foward * speed;

	//아마 이거하면 뒤 돌아버릴듯
	character->GetCharacterMovement()->MaxWalkSpeed = speed;
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, inEndLocation);

	FVector deadReckoningLocation = inStartLocation + (velocity * timeDuration);
	//character->SetActorLocation(deadReckoningLocation);

	IsCorrection = true;
	mStartLocation = deadReckoningLocation;
	mTargetLoction = inEndLocation;
	mCorrectionVelocity = speed;
	mStartTime = timeDuration - moveDuration;
	mTimeElapsed = 0.0f;

	IsRotationCorrection = true;
	mTargetRotation = direction;
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

	if (mCorrectionVelocity <= 1.0f)
	{
		FVector curLocation = pawn->GetActorLocation();
		FVector correctionLocation = FMath::VInterpTo(curLocation, mTargetLoction, inDeltaTime, mCorrectionVelocity);

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
	else
	{
		mTimeElapsed += inDeltaTime;
		FVector correctionLocation = FMath::VInterpConstantTo(mStartLocation, mTargetLoction, mTimeElapsed, mCorrectionVelocity);

		if (mTimeElapsed > mStartTime)
		{
			pawn->SetActorLocation(mTargetLoction, false, nullptr, ETeleportType::ResetPhysics);
			IsCorrection = false;
		}
		else
		{
			pawn->SetActorLocation(correctionLocation, false, nullptr, ETeleportType::ResetPhysics);
		}
	}

}

void AEnemyController::RotationCorrection(const float inDeltaTime)
{
	APawn* pawn = this->GetPawn();
	if (nullptr == pawn)
	{
		return;
	}

	if (false == IsRotationCorrection)
	{
		return;
	}

	FRotator curRotation = pawn->GetActorRotation();
	float	velocity = 1.0f;

	FRotator correctionRotation = FMath::Lerp(curRotation, mTargetRotation, velocity * inDeltaTime);

	if (correctionRotation.Equals(mTargetRotation, 0.1f))
	{
		pawn->SetActorRotation(mTargetRotation, ETeleportType::ResetPhysics);
		IsRotationCorrection = false;
	}
	else
	{
		pawn->SetActorRotation(correctionRotation, ETeleportType::ResetPhysics);
	}
}
