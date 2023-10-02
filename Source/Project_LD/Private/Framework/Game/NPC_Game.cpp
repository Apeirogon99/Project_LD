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
	mIsLocationCorrection = false;
	mCorrectionVelocity = 0.0f;
}

ANPC_Game::~ANPC_Game()
{
}

void ANPC_Game::Tick(float DeltaTime)
{
	if (mIsLocationCorrection)
	{
		MoveCorrection(DeltaTime);
	}
}

void ANPC_Game::OnTeleport(const FVector& DestLocation)
{
	ACharacter* character = Cast<ACharacter>(this->GetPawn());
	if (nullptr == character)
	{
		return;
	}

	mIsLocationCorrection = false;
	mTargetLoction = DestLocation;
	character->SetActorLocation(DestLocation, false, nullptr, ETeleportType::ResetPhysics);
	this->StopMovement();

	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("NPC OnTeleport")), ELogLevel::Error);
}

void ANPC_Game::NPCMoveDestination(const FVector inOldMovementLocation, const FVector inNewMovementLocation, const int64 inTime)
{

	ACharacter* character = Cast<ACharacter>(this->GetPawn());
	if (nullptr == character)
	{
		return;
	}

	ANPS_Game* playerState = this->GetPlayerState<ANPS_Game>();
	if (nullptr == playerState)
	{
		return;
	}
	FCharacterStats stats = playerState->GetCharacterStats();
	float speed = stats.GetCurrentStats().GetMovementSpeed();

	character->GetCharacterMovement()->MaxWalkSpeed = speed;

	FVector		direction = inNewMovementLocation - inOldMovementLocation;
	FRotator	rotation = direction.Rotation();
	FVector		foward = rotation.Quaternion().GetForwardVector();

	FVector curLocation;
	FVector deadReckoningLocation;
	FVector overDeadReckoningLocation;

	FVector velocity = foward * speed;
	float duration = inTime / 1000.0f;


	float distance = FVector::Dist(inOldMovementLocation, inNewMovementLocation);
	if (distance <= 1.0f)
	{
		mIsLocationCorrection = false;
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
			mIsLocationCorrection = true;
			mTargetLoction = deadReckoningLocation;
			mCorrectionVelocity = 0.1f;
		}

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, inNewMovementLocation);
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

	if (false == mIsLocationCorrection)
	{
		return;
	}

	FVector curLocation = pawn->GetActorLocation();

	FVector correctionLocation = FMath::VInterpTo(curLocation, mTargetLoction, inDeltaTime, mCorrectionVelocity);

	float distance = FVector::Dist(curLocation, correctionLocation);
	if (distance <= 1.0f)
	{
		pawn->SetActorLocation(mTargetLoction, false, nullptr, ETeleportType::ResetPhysics);
		mIsLocationCorrection = false;
	}
	else
	{
		pawn->SetActorLocation(correctionLocation, false, nullptr, ETeleportType::ResetPhysics);
	}

	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("cur[%ws], dead[%ws], old[%ws], new[%ws], distance[%f], duration[%f]"), *curLocation.ToString(), *deadReckoningLocation.ToString(), *inOldMovementLocation.ToString(), *inNewMovementLocation.ToString(), distance, duration), ELogLevel::Error);
}

void ANPC_Game::StopMovementController(const FVector& inStopLocation)
{
	ACharacter* character = Cast<ACharacter>(this->GetPawn());
	if (nullptr == character)
	{
		return;
	}

	mIsLocationCorrection = false;
	mTargetLoction = inStopLocation;
	character->SetActorLocation(inStopLocation);

	this->StopMovement();
}
