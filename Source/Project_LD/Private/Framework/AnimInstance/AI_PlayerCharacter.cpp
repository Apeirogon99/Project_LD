// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/AnimInstance/AI_PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Pawn.h"
#include "Game/C_Game.h"

void UAI_PlayerCharacter::NativeInitializeAnimation()
{
	if (mPawn == nullptr)
	{
		mPawn = TryGetPawnOwner();
	}
	/*
	if (mMainCharacter == nullptr)
	{
		mMainCharacter = Cast<AC_Game>(TryGetPawnOwner());
	}
	*/
}

void UAI_PlayerCharacter::UpdateProperties()
{
	if (mPawn == nullptr)
	{
		mPawn = TryGetPawnOwner();
	}
	/*
	if (mMainCharacter == nullptr)
	{
		mMainCharacter = Cast<AC_Game>(TryGetPawnOwner());
	}
	*/

	if (mPawn)
	{
		FVector Velocity = mPawn->GetVelocity();
		mMovementSpeed = UKismetMathLibrary::VSize(Velocity);

		FRotator BaseRotation = UKismetMathLibrary::MakeRotator(0.f,0.f, mPawn->GetBaseAimRotation().Yaw);
		mMovementDirection = CalculateDirection(Velocity,BaseRotation);
	}
	/*
	if (mMainCharacter)
	{
		FVector Velocity = mMainCharacter->GetVelocity();
		mMovementSpeed = UKismetMathLibrary::VSize(Velocity);

		FRotator BaseRotation = UKismetMathLibrary::MakeRotator(0.f,0.f, mMainCharacter->GetBaseAimRotation().Yaw);
		mMovementDirection = CalculateDirection(Velocity, BaseRotation);
	}
	*/
}
