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

	FVector	direction = inNewMovementLocation - inOldMovementLocation;
	direction.Normalize();

	FVector velocity = direction * 330.0f;
	float	duration = inTime / 1000.0f;

	FVector deadReckoningLocation = inOldMovementLocation + (velocity * duration);

	//현재 위치와 비교하여 차이가 얼마나 나는지 판단
	FVector curLocation = pawn->GetActorLocation();
	float locationDistance = FVector::Dist2D(curLocation, deadReckoningLocation);
	if (locationDistance > 50.0f)
	{
		pawn->SetActorLocation(inNewMovementLocation, false, nullptr, ETeleportType::ResetPhysics);
		pawn->SetActorRotation(direction.Rotation());
	}
	else
	{
		//pawn->SetActorLocation(deadReckoningLocation, false, nullptr, ETeleportType::ResetPhysics);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, inNewMovementLocation);
	}
}
