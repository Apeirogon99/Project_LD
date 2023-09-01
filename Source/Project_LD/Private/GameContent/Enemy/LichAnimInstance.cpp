// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/LichAnimInstance.h"

ULichAnimInstance::ULichAnimInstance()
{
	InitSkillMontage();
}

ULichAnimInstance::~ULichAnimInstance()
{
}

void ULichAnimInstance::InitSkillMontage()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LICH_SKILL1(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_RiseSkeleton.M_Lich_RiseSkeleton'"));
	if (LICH_SKILL1.Succeeded())
	{
		mLichSkillMontage.Add(LICH_SKILL1.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LICH_SKILL2(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_RiseDarkKnight.M_Lich_RiseDarkKnight'"));
	if (LICH_SKILL2.Succeeded())
	{
		mLichSkillMontage.Add(LICH_SKILL2.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LICH_SKILL3(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_BlinkAttack.M_Lich_BlinkAttack'"));
	if (LICH_SKILL3.Succeeded())
	{
		mLichSkillMontage.Add(LICH_SKILL3.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LICH_SKILL4(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_BlinkStun.M_Lich_BlinkStun'"));
	if (LICH_SKILL4.Succeeded())
	{
		mLichSkillMontage.Add(LICH_SKILL4.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LICH_SKILL5(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_SoulSpark_Start.M_Lich_SoulSpark_Start'"));
	if (LICH_SKILL5.Succeeded())
	{
		mLichSkillMontage.Add(LICH_SKILL5.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LICH_SKILL6(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_SoulShackles.M_Lich_SoulShackles'"));
	if (LICH_SKILL6.Succeeded())
	{
		mLichSkillMontage.Add(LICH_SKILL6.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LICH_SKILL7(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_Explosion.M_Lich_Explosion'"));
	if (LICH_SKILL7.Succeeded())
	{
		mLichSkillMontage.Add(LICH_SKILL7.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LICH_SKILL8(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_MultiCasting_Start.M_Lich_MultiCasting_Start'"));
	if (LICH_SKILL8.Succeeded())
	{
		mLichSkillMontage.Add(LICH_SKILL8.Object);
	}
}
