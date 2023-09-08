// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/LichAnimInstance.h"

ULichAnimInstance::ULichAnimInstance()
{
	InitSkillMontage();
}

ULichAnimInstance::~ULichAnimInstance()
{
}

void ULichAnimInstance::PlayLichAnimMontage(int32 Index)
{
	Montage_Play(mLichSkillMontage[Index]);
}

void ULichAnimInstance::InitSkillMontage()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RISEHAND(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_RasieHand.M_Lich_RasieHand'"));
	if (RISEHAND.Succeeded())
	{
		mLichSkillMontage.Add(RISEHAND.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BLINKATTACK_ACTIVE(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_BlinkAttack_Active.M_Lich_BlinkAttack_Active'"));
	if (BLINKATTACK_ACTIVE.Succeeded())
	{
		mLichSkillMontage.Add(BLINKATTACK_ACTIVE.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BLINKATTACK_REACTION(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_BlinkAttack_Reaction.M_Lich_BlinkAttack_Reaction'"));
	if (BLINKATTACK_REACTION.Succeeded())
	{
		mLichSkillMontage.Add(BLINKATTACK_REACTION.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BLINKSTUN_ACTIVE(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_BlinkStun_Active.M_Lich_BlinkStun_Active'"));
	if (BLINKSTUN_ACTIVE.Succeeded())
	{
		mLichSkillMontage.Add(BLINKSTUN_ACTIVE.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BLINKSTUN_REACTION(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_BlinkStun_Reaction.M_Lich_BlinkStun_Reaction'"));
	if (BLINKSTUN_REACTION.Succeeded())
	{
		mLichSkillMontage.Add(BLINKSTUN_REACTION.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SOULSPARK_ACTIVE(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_SoulSpark_Active.M_Lich_SoulSpark_Active'"));
	if (SOULSPARK_ACTIVE.Succeeded())
	{
		mLichSkillMontage.Add(SOULSPARK_ACTIVE.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SOULSPARK_REACTION(TEXT("AnimMontage'/Game/GameContent/Animation/Enemy/Lich/AnimAsset/M_Lich_SoulSpark_Reaction.M_Lich_SoulSpark_Reaction'"));
	if (SOULSPARK_REACTION.Succeeded())
	{
		mLichSkillMontage.Add(SOULSPARK_REACTION.Object);
	}
}
