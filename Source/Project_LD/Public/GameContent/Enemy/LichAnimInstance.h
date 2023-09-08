// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameContent/Enemy/EnemyAnimInstance.h"
#include "LichAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API ULichAnimInstance : public UEnemyAnimInstance
{
	GENERATED_BODY()
	
public:
	ULichAnimInstance();
	~ULichAnimInstance();

public:
	void PlayLichAnimMontage(int32 Index);
	
private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Skill | Anim", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> mLichSkillMontage;

private:
	void InitSkillMontage();
};
