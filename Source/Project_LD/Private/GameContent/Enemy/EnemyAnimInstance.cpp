// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/EnemyAnimInstance.h"
#include "GameContent/Enemy/EnemyBase.h"
#include "GameContent/Enemy/EnemyState.h"
#include "GameContent/Enemy/EnemyStateBase.h"

#include "Kismet/KismetMathLibrary.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (mCharacter == nullptr)
	{
		mCharacter = Cast<AEnemyBase>(TryGetPawnOwner());
	}
}

void UEnemyAnimInstance::UpdateProperties()
{
	if (mCharacter == nullptr)
	{
		mCharacter = Cast<AEnemyBase>(TryGetPawnOwner());
	}
	else
	{
		if (mEnemyState == nullptr)
		{
			if (IsValid(mCharacter->GetPlayerState()))
			{
				mEnemyState = mCharacter->GetPlayerState<AEnemyState>();
			}
		}
	}

	if (mCharacter && mEnemyState)
	{
		FVector Velocity = mCharacter->GetVelocity();
		mMovementSpeed = UKismetMathLibrary::VSize(Velocity);

		//상태값 반환
		mCurrentState = mEnemyState->GetEnemyStateType();

		float health = mEnemyState->GetEnemyCurrentStats().base_health;
		if (health <= 0)
		{
			//death
		}
	}
}
