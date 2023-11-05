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
	IsMoveCorrection = false;
	IsLocationCorrection = false;
	IsRotationCorrection = false;
	mTeleport = false;

	mTeleportCool = 0.0f;
	mCorrectionVelocity = 0.0f;
}

AEnemyController::~AEnemyController()
{

}

void AEnemyController::Destroyed()
{
	Super::Destroyed();
}

void AEnemyController::OnTeleport(const FVector& DestLocation, const FRotator& DestRotation)
{
	ACharacter* character = Cast<ACharacter>(this->GetPawn());
	if (nullptr == character)
	{
		return;
	}

	mTargetLoction = DestLocation;
	IsMoveCorrection = false;
	IsLocationCorrection = false;

	character->TeleportTo(DestLocation, DestRotation, false, false);
	this->StopMovement();

	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("Enemy OnTeleport")), ELogLevel::Warning);
}

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (IsMoveCorrection || IsLocationCorrection)
	{
		MoveCorrection(DeltaTime);
	}

	if (IsRotationCorrection)
	{
		RotationCorrection(DeltaTime);
	}

}

void AEnemyController::MoveDestination(const FVector inOldMovementLocation, const FVector inNewMovementLocation, const int64 inTime)
{
	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("MoveDestination")), ELogLevel::Warning);

	ACharacter* character = Cast<ACharacter>(this->GetPawn());
	if (nullptr == character)
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

	FVector	direction = inNewMovementLocation - inOldMovementLocation;
	FRotator rotation = direction.Rotation();
	FVector foward = rotation.Quaternion().GetForwardVector();

	FVector curLocation;
	FVector deadReckoningLocation;
	FVector overDeadReckoningLocation;

	FVector velocity = foward * speed;
	float	duration = inTime / 1000.0f;

	float distance = FVector::Dist(inOldMovementLocation, inNewMovementLocation);
	if (distance <= 1.0f)
	{
		IsMoveCorrection = false;
		IsLocationCorrection = false;
		mTargetLoction = inNewMovementLocation;
		character->SetActorLocation(inNewMovementLocation);
		this->StopMovement();
	}
	else
	{

		curLocation = character->GetActorLocation();
		deadReckoningLocation = inOldMovementLocation + (velocity * duration);
		overDeadReckoningLocation = inOldMovementLocation + (velocity * 0.2f);

		float nowDistance = FVector::Dist(curLocation, deadReckoningLocation);
		float overDistance = FVector::Dist(curLocation, overDeadReckoningLocation);

		if (nowDistance > overDistance)
		{
			IsMoveCorrection = true;
			IsLocationCorrection = false;
			mTargetLoction = deadReckoningLocation;
			mCorrectionVelocity = 0.1f;

			IsRotationCorrection = true;
			mTargetRotation = direction.Rotation();
		}

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, inNewMovementLocation);
	}

	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("cur[%ws], dead[%ws], old[%ws], new[%ws] distance[%f]"), *curLocation.ToString(), *deadReckoningLocation.ToString(), *inOldMovementLocation.ToString(), *inNewMovementLocation.ToString(), distance), ELogLevel::Error);


}

void AEnemyController::AnimationMoveDestination(const FVector inStartLocation, const FVector inEndLocation, const int64 inMoveDuration, const int64 inTimeDuration)
{
	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("AnimationMoveDestination")), ELogLevel::Warning);

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

	character->GetCharacterMovement()->MaxWalkSpeed = speed;
	FVector deadReckoningLocation = inStartLocation + (velocity * timeDuration);

	IsMoveCorrection = false;
	IsLocationCorrection= true;

	mStartLocation = deadReckoningLocation;
	mTargetLoction = inEndLocation;
	mCorrectionVelocity = speed;
	mStartTime = moveDuration - timeDuration;
	mTimeElapsed = 0.0f;

	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("start[%ws], end[%ws], dead[%ws], speed[%f], move[%f], time[%f]"), *inStartLocation.ToString(), *inEndLocation.ToString(), *deadReckoningLocation.ToString(), speed, moveDuration, timeDuration), ELogLevel::Error);
}

void AEnemyController::MoveCorrection(const float inDeltaTime)
{
	APawn* pawn = this->GetPawn();
	if (nullptr == pawn)
	{
		return;
	}

	if (false == IsLocationCorrection && false == IsMoveCorrection)
	{
		return;
	}

	if (IsMoveCorrection)
	{
		FVector curLocation = pawn->GetActorLocation();
		FVector correctionLocation = FMath::VInterpTo(curLocation, mTargetLoction, inDeltaTime, mCorrectionVelocity);

		float distance = FVector::Dist2D(curLocation, correctionLocation);
		if (distance <= 1.0f)
		{
			pawn->SetActorLocation(mTargetLoction, false, nullptr, ETeleportType::ResetPhysics);
			IsMoveCorrection = false;
		}
		else
		{
			pawn->SetActorLocation(correctionLocation, false, nullptr, ETeleportType::ResetPhysics);
		}
	}
	else if(IsLocationCorrection)
	{
		mTimeElapsed += inDeltaTime;
		FVector correctionLocation = FMath::VInterpConstantTo(mStartLocation, mTargetLoction, mTimeElapsed, mCorrectionVelocity);

		if (mTimeElapsed > mStartTime)
		{
			pawn->SetActorLocation(mTargetLoction, false, nullptr, ETeleportType::ResetPhysics);
			IsLocationCorrection = false;
		}
		else
		{
			pawn->SetActorLocation(correctionLocation, false, nullptr, ETeleportType::ResetPhysics);
		}

		//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("mStartTime[%f], TimeElapsed [%f], DeltaTime [%f]"), mStartTime, mTimeElapsed, inDeltaTime), ELogLevel::Error);
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
