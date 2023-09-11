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
	InitAttackMontage();
	InitSkillMontage();

	bIsAttack = false;
	bSaveAttack = false;
	bAttackLoop = false;
	bClientAnimWorking = false;
	mAttackCount = 0;
}

UAI_PlayerCharacter::~UAI_PlayerCharacter()
{
}

void UAI_PlayerCharacter::PlayClientAttackMontage()
{
	if (mMainCharacter != nullptr)
	{
		if (mAttackCount < 3)
		{
			if (bClientAnimWorking == false)
			{
				bClientAnimWorking = true;

				if (bIsAttack)
				{
					bSaveAttack = true;
				}
				else
				{
					bIsAttack = true;
					mMainCharacter->UpdateCharacterMontage(mAttackClientMontage[mAttackCount], 0.f);
				}
			}
		}
	}
}

void UAI_PlayerCharacter::PlayClientSkillMontage(const int32 inSkillid)
{
	if (mMainCharacter != nullptr)
	{
		if (bClientAnimWorking == false)
		{
			bClientAnimWorking = true;

			mMainCharacter->UpdateCharacterMontage(mSkillClientMontage[inSkillid], 0.f);
		}
	}
}

void UAI_PlayerCharacter::PlaySkillMontage(const int32 inSkillid, const float inTimeStamp)
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
	mMainCharacter->UpdateCharacterMontage(mSkillFullMontage[inSkillid], inTimeStamp);
	//bClientAnimWorking = false;
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
	mAttackCount = inAttackCount + 1;
	bClientAnimWorking = false;
}

// Protected //

void UAI_PlayerCharacter::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (mMainCharacter == nullptr)
	{
		mMainCharacter = Cast<ANC_Game>(TryGetPawnOwner());
	}
}

// Private //

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
	if (mMainCharacter != nullptr)
	{
		if (bSaveAttack)
		{
			bSaveAttack = false;
			mMainCharacter->UpdateCharacterMontage(mAttackClientMontage[mAttackCount], 0.0f);
		}
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

void UAI_PlayerCharacter::InitAttackMontage()
{
	// Server //
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

	// Client //

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
}

void UAI_PlayerCharacter::InitSkillMontage()
{
	// Server //
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_E_MONTAGE(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Skill/Buff/M_Buff_Full_Hu_M.M_Buff_Full_Hu_M'"));
	if (SKILL_E_MONTAGE.Succeeded())
	{
		mSkillFullMontage.Add(SKILL_E_MONTAGE.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_Q_MONTAGE(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Skill/Counter/M_Counter_Full_Hu_M.M_Counter_Full_Hu_M'"));
	if (SKILL_Q_MONTAGE.Succeeded())
	{
		mSkillFullMontage.Add(SKILL_Q_MONTAGE.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_W_MONTAGE(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Skill/SlamAttack/M_Skill_Full_SlamAttack.M_Skill_Full_SlamAttack'"));
	if (SKILL_W_MONTAGE.Succeeded())
	{
		mSkillFullMontage.Add(SKILL_W_MONTAGE.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_R_Charge_MONTAGE(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Skill/SwordSpirit/M_SwordSpirit_Charge_Full_Hu_M.M_SwordSpirit_Charge_Full_Hu_M'"));
	if (SKILL_R_Charge_MONTAGE.Succeeded())
	{
		mSkillFullMontage.Add(SKILL_R_Charge_MONTAGE.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_R_Attack_MONTAGE(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Skill/SwordSpirit/M_SwordSpirit_Attack_Full_Hu_M.M_SwordSpirit_Attack_Full_Hu_M'"));
	if (SKILL_R_Attack_MONTAGE.Succeeded())
	{
		mSkillFullMontage.Add(SKILL_R_Attack_MONTAGE.Object);
	}

	// Client //

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_E_MONTAGEClient(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Skill/Buff/M_Buff_Client_Hu_M.M_Buff_Client_Hu_M'	"));
	if (SKILL_E_MONTAGEClient.Succeeded())
	{
		mSkillClientMontage.Add(SKILL_E_MONTAGEClient.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_Q_MONTAGEClient(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Skill/Counter/M_Counter_Client_Hu_M.M_Counter_Client_Hu_M'"));
	if (SKILL_Q_MONTAGEClient.Succeeded())
	{
		mSkillClientMontage.Add(SKILL_Q_MONTAGEClient.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_W_MONTAGEClient(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Skill/SlamAttack/M_Skill_Client_SlamAttack.M_Skill_Client_SlamAttack'"));
	if (SKILL_W_MONTAGEClient.Succeeded())
	{
		mSkillClientMontage.Add(SKILL_W_MONTAGEClient.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_R_Charge_MONTAGEClient(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Skill/SwordSpirit/M_SwordSpirit_Charge_Client_Hu_M.M_SwordSpirit_Charge_Client_Hu_M'"));
	if (SKILL_R_Charge_MONTAGEClient.Succeeded())
	{
		mSkillClientMontage.Add(SKILL_R_Charge_MONTAGEClient.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_R_Attack_MONTAGEClient(TEXT("AnimMontage'/Game/GameContent/Animation/Male/Skill/SwordSpirit/M_SwordSpirit_Attack_Client_Hu_M.M_SwordSpirit_Attack_Client_Hu_M'"));
	if (SKILL_R_Attack_MONTAGEClient.Succeeded())
	{
		mSkillClientMontage.Add(SKILL_R_Attack_MONTAGEClient.Object);
	}
}
