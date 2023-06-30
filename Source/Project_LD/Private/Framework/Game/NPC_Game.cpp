// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/NPC_Game.h"
#include "Framework/Game/NC_Game.h"

#include <Network/NetworkUtils.h>

#include <GameFramework/PawnMovementComponent.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>

ANPC_Game::ANPC_Game()
{
	IsCorrection = false;
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
}

void ANPC_Game::NPCMoveDestination(const FVector inOldMovementLocation, const FVector inNewMovementLocation, const int64 inTime)
{
	APawn* pawn = this->GetPawn();
	if (nullptr == pawn)
	{
		return;
	}

	FVector	direction = inNewMovementLocation - inOldMovementLocation;
	direction.Normalize();

	FVector velocity = direction * 330.0f;
	float	duration = inTime / 1000.0f;

	FVector deadReckoningLocation = inOldMovementLocation + (velocity * duration);

	//현재 위치와 비교하여 차이가 얼마나 나는지 판단
	FVector curLocation = pawn->GetActorLocation();
	float locationDistance = FVector::Dist2D(curLocation, deadReckoningLocation);
	if (locationDistance > 10.0f)
	{
		IsCorrection = true;
		mTargetLoction = inOldMovementLocation;
	}
	else
	{
		IsCorrection = true;
		mTargetLoction = deadReckoningLocation;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, inNewMovementLocation);
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
	float	velocity = 10.0f;

	FVector correctionLocation = FMath::VInterpTo(curLocation, mTargetLoction, inDeltaTime, velocity);

	float distance = FVector::Dist2D(curLocation, correctionLocation);
	if (distance <= 10.0f)
	{
		IsCorrection = false;
	}
	else
	{
		pawn->SetActorLocation(correctionLocation, false, nullptr, ETeleportType::ResetPhysics);
	}

	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("NPC Pos %ws"), *correctionLocation.ToString()), ELogLevel::Warning);
}
