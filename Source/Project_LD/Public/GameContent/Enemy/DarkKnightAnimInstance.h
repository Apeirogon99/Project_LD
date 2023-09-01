// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameContent/Enemy/EnemyAnimInstance.h"
#include "DarkKnightAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UDarkKnightAnimInstance : public UEnemyAnimInstance
{
	GENERATED_BODY()
	
public:
	UDarkKnightAnimInstance();
	~UDarkKnightAnimInstance();

public:
	void PlayDarkKnightAnimMontage(int32 InSkillID);

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Skill | Anim", meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> mDarkKnightSkillMontage;

private:
	void InitSkillMontage();
};
