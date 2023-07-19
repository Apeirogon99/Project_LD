// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AI_PlayerCharacter.generated.h"

/**
 * 
 */
class AC_Game;
class UAnimMontage;

UCLASS()
class PROJECT_LD_API UAI_PlayerCharacter : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAI_PlayerCharacter();
	~UAI_PlayerCharacter();

	void PlayAttackMontage();

protected:
	virtual void NativeInitializeAnimation() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Properties", meta = (AllowPrivateAccess = "true"))
	float mMovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Properties", meta = (AllowPrivateAccess = "true"))
	float mMovementDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	AC_Game* mMainCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = "true"))
	UAnimMontage* mAttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = "true"))
	bool bIsAttack;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = "true"))
	bool bSaveAttack;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = "true"))
	int32 mAttackCount;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = "true"))
	bool bAttackLoop;

private:
	UFUNCTION(BlueprintCallable, Category = "Update Properties")
	void UpdateProperties();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	UFUNCTION()
	void AnimNotify_ResetCombo();

	UFUNCTION()
	void AnimNotify_AttackServerCheck();

private:
	void JumpAttackMontageSection();
};
