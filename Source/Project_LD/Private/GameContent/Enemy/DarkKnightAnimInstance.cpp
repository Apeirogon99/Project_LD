// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/DarkKnightAnimInstance.h"

UDarkKnightAnimInstance::UDarkKnightAnimInstance()
{
}

UDarkKnightAnimInstance::~UDarkKnightAnimInstance()
{
}

void UDarkKnightAnimInstance::PlayDarkKnightAnimMontage(int32 InSkillID)
{
	Montage_Play(mDarkKnightSkillMontage[InSkillID]);
}

void UDarkKnightAnimInstance::InitSkillMontage()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DARKKNIGHT_SKILL(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/DarkKnight/AnimAsset/M_DarkKnight_RunningAttack.M_DarkKnight_RunningAttack'"));
	if (DARKKNIGHT_SKILL.Succeeded())
	{
		mDarkKnightSkillMontage.Add(DARKKNIGHT_SKILL.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DARKKNIGHT_SKILL(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/DarkKnight/AnimAsset/M_DarkKnight_ChargedComboAttack.M_DarkKnight_ChargedComboAttack'"));
	if (DARKKNIGHT_SKILL.Succeeded())
	{
		mDarkKnightSkillMontage.Add(DARKKNIGHT_SKILL.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DARKKNIGHT_SKILL(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/DarkKnight/AnimAsset/M_DarkKnight_Uppercut.M_DarkKnight_Uppercut'"));
	if (DARKKNIGHT_SKILL.Succeeded())
	{
		mDarkKnightSkillMontage.Add(DARKKNIGHT_SKILL.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DARKKNIGHT_SKILL(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/DarkKnight/AnimAsset/M_DarkKnight_Swing.M_DarkKnight_Swing'"));
	if (DARKKNIGHT_SKILL.Succeeded())
	{
		mDarkKnightSkillMontage.Add(DARKKNIGHT_SKILL.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DARKKNIGHT_SKILL(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/DarkKnight/AnimAsset/M_DarkKnight_SwingAndSlam.M_DarkKnight_SwingAndSlam'"));
	if (DARKKNIGHT_SKILL.Succeeded())
	{
		mDarkKnightSkillMontage.Add(DARKKNIGHT_SKILL.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DARKKNIGHT_SKILL(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/DarkKnight/AnimAsset/M_DarkKnight_HandAndSwordSwing.M_DarkKnight_HandAndSwordSwing'"));
	if (DARKKNIGHT_SKILL.Succeeded())
	{
		mDarkKnightSkillMontage.Add(DARKKNIGHT_SKILL.Object);
	}
}
