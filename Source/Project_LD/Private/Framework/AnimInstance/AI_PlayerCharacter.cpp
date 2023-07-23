// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/AnimInstance/AI_PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Pawn.h"
#include "Game/C_Game.h"

UAI_PlayerCharacter::UAI_PlayerCharacter()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/GameContent/Animation/Male/Attack/M_Attack_Hu_M.M_Attack_Hu_M"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		mAttackMontage = ATTACK_MONTAGE.Object;
	}

	bIsAttack = false;
	bSaveAttack = false;
	bAttackLoop = false;
	mAttackCount = 0;
}

UAI_PlayerCharacter::~UAI_PlayerCharacter()
{
}

void UAI_PlayerCharacter::PlayAttackMontage()
{
	if (bIsAttack)
	{
		bSaveAttack = true;
	}
	else
	{
		bIsAttack = true;
		JumpAttackMontageSection(mAttackCount, 0.0f);
	}
}

void UAI_PlayerCharacter::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (mMainCharacter == nullptr)
	{
		mMainCharacter = Cast<AC_Game>(TryGetPawnOwner());
	}
}

void UAI_PlayerCharacter::UpdateProperties()
{
	if (mMainCharacter == nullptr)
	{
		mMainCharacter = Cast<AC_Game>(TryGetPawnOwner());
	}

	if (mMainCharacter)
	{
		FVector Velocity = mMainCharacter->GetVelocity();
		mMovementSpeed = UKismetMathLibrary::VSize(Velocity);

		FRotator BaseRotation = UKismetMathLibrary::MakeRotator(0.f,0.f, mMainCharacter->GetBaseAimRotation().Yaw);
		mMovementDirection = CalculateDirection(Velocity, BaseRotation);
	}
}

void UAI_PlayerCharacter::AnimNotify_NextAttackCheck()
{
	if (bSaveAttack)
	{
		bSaveAttack = false;
		JumpAttackMontageSection(mAttackCount, 0.0f);
	}
}

void UAI_PlayerCharacter::AnimNotify_ResetCombo()
{
	bIsAttack = false;
	bSaveAttack = false;
	bAttackLoop = false;
	mAttackCount = 0;
}

void UAI_PlayerCharacter::AnimNotify_AttackServerCheck()
{
	if (mMainCharacter->GetIsZoom() == false)
	{
		mMainCharacter->SetIsZoom(true);
		mMainCharacter->OnAttackCameraZoomIn();
	}
	if (bAttackLoop && bIsAttack)
	{
		bAttackLoop = false;
		Montage_JumpToSection(FName(TEXT("Combo4")), mAttackMontage);
		mMainCharacter->SetIsZoom(false);
		mMainCharacter->OnAttackCameraZoomOut();
	}
}

void UAI_PlayerCharacter::JumpAttackMontageSection(const int32 inAttackCount, const float inTimeStamp)
{
	switch (inAttackCount)
	{
	case 0:
		Montage_Play(mAttackMontage, 1.f);
		break;
	case 1:
		Montage_JumpToSection(FName(TEXT("Combo2")), mAttackMontage);
		break;
	case 2:
		Montage_JumpToSection(FName(TEXT("Combo3")), mAttackMontage);
		break;
	default:
		break;
	}
	mAttackCount++;
}
