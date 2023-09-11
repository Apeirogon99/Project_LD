// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/NPC_Game.h"
#include "Framework/Game/NC_Game.h"
#include "Framework/Game/NPS_Game.h"

#include <Network/NetworkUtils.h>

#include <GameFramework/PawnMovementComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>

ANPC_Game::ANPC_Game()
{
	IsCorrection = false;
	mTeleport = false;
	mCorrectionVelocity = 0.0f;
}

ANPC_Game::~ANPC_Game()
{
}

void ANPC_Game::Tick(float DeltaTime)
{
	if (IsCorrection)
	{
		MoveCorrection(DeltaTime);
	}

	if (mTeleport)
	{
		static float tpTime = 0.0f;
		tpTime += DeltaTime;
		if (tpTime >= 10.0f)
		{
			mTeleport = false;
		}
		tpTime = 0.0f;
	}

}

void ANPC_Game::OnTeleport_Implementation(const FVector& DestLocation)
{
	APawn* pawn = this->GetPawn();
	if (nullptr == pawn)
	{
		return;
	}

	mTeleport = true;

	pawn->GetMovementComponent()->StopActiveMovement();

	pawn->SetActorLocation(DestLocation, false, nullptr, ETeleportType::ResetPhysics);
}

void ANPC_Game::NPCMoveDestination(const FVector inOldMovementLocation, const FVector inNewMovementLocation, const int64 inTime)
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

	ANPS_Game* playerState = this->GetPlayerState<ANPS_Game>();
	if (nullptr == playerState)
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

	FVector velocity = foward * 330.0f;
	float	duration = inTime / 1000.0f;

	FVector deadReckoningLocation = inOldMovementLocation + (velocity * duration);

	//현재 위치와 비교하여 차이가 얼마나 나는지 판단
	FVector curLocation = pawn->GetActorLocation();
	float locationDistance = FVector::Dist(curLocation, deadReckoningLocation);
	if (locationDistance > 1.0f)
	{
		IsCorrection = true;
		mTargetLoction = deadReckoningLocation;
		mCorrectionVelocity = 0.2f;
		//pawn->SetActorRotation(direction.Rotation());
	}

	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("cur[%ws], old[%ws], new[%ws], vel[%ws], dead[%ws], distance[%f], duration[%f]"), *curLocation.ToString(), *inOldMovementLocation.ToString(), *inNewMovementLocation.ToString() , *velocity.ToString(), *deadReckoningLocation.ToString(), locationDistance, duration), ELogLevel::Error);
}

void ANPC_Game::MoveCorrection(const float inDeltaTime)
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

	FVector correctionLocation = FMath::VInterpTo(curLocation, mTargetLoction, inDeltaTime, mCorrectionVelocity);

	float distance = FVector::Dist(curLocation, correctionLocation);
	if (distance <= 1.0f)
	{
		pawn->SetActorLocation(mTargetLoction, false, nullptr, ETeleportType::ResetPhysics);
		IsCorrection = false;
	}
	else
	{
		pawn->SetActorLocation(correctionLocation, false, nullptr, ETeleportType::ResetPhysics);
	}

	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("NPC Pos %ws"), *correctionLocation.ToString()), ELogLevel::Warning);
}

void ANPC_Game::StopMovementController(const FVector& inStopLocation)
{
	ACharacter* character = Cast<ACharacter>(this->GetPawn());
	if (nullptr == character)
	{
		return;
	}

	IsCorrection = false;
	mTargetLoction = inStopLocation;
	character->SetActorLocation(inStopLocation);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, inStopLocation);

	this->StopMovement();
}
