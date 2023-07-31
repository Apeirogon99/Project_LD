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

	ANPS_Game* playerState = this->GetPlayerState<ANPS_Game>();
	if (nullptr == playerState)
	{
		return;
	}

	FVector	direction = inNewMovementLocation - inOldMovementLocation;
	direction.Normalize();

	FVector velocity = direction * playerState->GetCharacterStats().GetCurrentStats().GetMovementSpeed();
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

	character->SetActorLocation(FVector(inStopLocation.X, inStopLocation.Y, character->GetActorLocation().Z), false, nullptr, ETeleportType::ResetPhysics);
}
