// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/NPC_Game.h"
#include "Framework/Game/NC_Game.h"

#include <GameFramework/PawnMovementComponent.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>

ANPC_Game::ANPC_Game()
{
}

ANPC_Game::~ANPC_Game()
{
}

void ANPC_Game::NPCMoveDestination(const FVector inOldMovementLocation, const FVector inNewMovementLocation, const int64 inTime)
{
	APawn* pawn = this->GetPawn();
	if (nullptr == pawn)
	{
		return;
	}

	FVector		direction = inNewMovementLocation - inOldMovementLocation;
	direction.Normalize();

	FRotator	rotation = direction.Rotation();
	FVector		velocity = rotation.Vector() * pawn->GetMovementComponent()->GetMaxSpeed();
	float		duration = inTime / 1000.0f;
	FVector		deadReckoningLocation = inOldMovementLocation + pawn->GetVelocity() * duration + 0.5f * velocity * duration * duration;

	float distance1 = FVector::Distance(deadReckoningLocation, inOldMovementLocation);
	float distance2 = FVector::Distance(inNewMovementLocation, inOldMovementLocation);

	if (distance1 >= distance2)
	{
		pawn->SetActorLocation(inNewMovementLocation, false, nullptr, ETeleportType::ResetPhysics);
		pawn->SetActorRotation(rotation);
	}
	else
	{
		pawn->SetActorLocation(deadReckoningLocation, false, nullptr, ETeleportType::ResetPhysics);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, inNewMovementLocation);
	}
}
