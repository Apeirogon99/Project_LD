// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/AnimInstance/AI_PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Framework/Game/NPC_Game.h"
#include "Game/PC_Game.h"
#include "Game/C_Game.h"

UAI_PlayerCharacter::UAI_PlayerCharacter()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE1(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Attack/M_ComboAttack1_Full_Hu_M.M_ComboAttack1_Full_Hu_M'"));
	if (ATTACK_MONTAGE1.Succeeded())
	{
		mAttackFullMontage.Add(ATTACK_MONTAGE1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE2(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Attack/M_ComboAttack2_Full_Hu_M.M_ComboAttack2_Full_Hu_M'"));
	if (ATTACK_MONTAGE2.Succeeded())
	{
		mAttackFullMontage.Add(ATTACK_MONTAGE2.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE3(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Attack/M_ComboAttack3_Full_Hu_M.M_ComboAttack3_Full_Hu_M'"));
	if (ATTACK_MONTAGE3.Succeeded())
	{
		mAttackFullMontage.Add(ATTACK_MONTAGE3.Object);
	}	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE1Client(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Attack/M_ComboAttack1_Client_Hu_M.M_ComboAttack1_Client_Hu_M'"));
	if (ATTACK_MONTAGE1.Succeeded())
	{
		mAttackClientMontage.Add(ATTACK_MONTAGE1Client.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE2Client(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Attack/M_ComboAttack2_Client_Hu_M.M_ComboAttack2_Client_Hu_M'"));
	if (ATTACK_MONTAGE2.Succeeded())
	{
		mAttackClientMontage.Add(ATTACK_MONTAGE2Client.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE3Client(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Attack/M_ComboAttack3_Client_Hu_M.M_ComboAttack3_Client_Hu_M'"));
	if (ATTACK_MONTAGE3.Succeeded())
	{
		mAttackClientMontage.Add(ATTACK_MONTAGE3Client.Object);
	}

	bIsAttack = false;
	bSaveAttack = false;
	bAttackLoop = false;
	bClientAnimWorking = false;
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

void UAI_PlayerCharacter::PlayClientMontage()
{
	if (mMainCharacter != nullptr)
	{
		if (mAttackCount < 3)
		{
			if (bClientAnimWorking == false)
			{
				mMainCharacter->UpdateCharacterMontage(mAttackClientMontage[mAttackCount], 0.f);
			}
		}
	}
}

void UAI_PlayerCharacter::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (mMainCharacter == nullptr)
	{
		mMainCharacter = Cast<ANC_Game>(TryGetPawnOwner());
	}
}

void UAI_PlayerCharacter::UpdateProperties()
{
	if (mMainCharacter == nullptr)
	{
		mMainCharacter = Cast<ANC_Game>(TryGetPawnOwner());
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

	if (mMainCharacter)
	{
		mMainCharacter->SetIsAttack(false);

		auto movement = Cast<UCharacterMovementComponent>(mMainCharacter->GetMovementComponent());
		movement->MovementMode = EMovementMode::MOVE_Walking;
	}
}

void UAI_PlayerCharacter::AnimNotify_AttackServerCheck()
{
	if (mMainCharacter)
	{
		mMainCharacter->SetIsAttack(true);

		auto movement = Cast<UCharacterMovementComponent>(mMainCharacter->GetMovementComponent());
		movement->MovementMode = EMovementMode::MOVE_None;
	}
	//if (mMainCharacter->GetIsZoom() == false)
	//{
	//	mMainCharacter->SetIsZoom(true);
	//	mMainCharacter->OnAttackCameraZoomIn();
	//}
	//if (bAttackLoop && bIsAttack)
	//{
	//	bAttackLoop = false;
	//	Montage_JumpToSection(FName(TEXT("Combo4")), mAttackMontage);
	//	mMainCharacter->SetIsZoom(false);
	//	mMainCharacter->OnAttackCameraZoomOut();
	//}
}

void UAI_PlayerCharacter::JumpAttackMontageSection(const int32 inAttackCount, const float inTimeStamp)
{
	APawn* pawn = this->TryGetPawnOwner();
	if (nullptr == pawn)
	{
		return;
	}

	AAppearanceCharacter* character = Cast<AAppearanceCharacter>(pawn);
	if (nullptr == character)
	{
		return;
	}
	character->UpdateCharacterMontage(mAttackFullMontage[inAttackCount], inTimeStamp);
	mAttackCount++;
	bClientAnimWorking = false;
}
