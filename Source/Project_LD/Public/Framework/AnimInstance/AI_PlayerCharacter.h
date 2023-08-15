// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AI_PlayerCharacter.generated.h"

/**
 * 
 */
class AC_Game;
class ANC_Game;
class UAnimMontage;

UCLASS()
class PROJECT_LD_API UAI_PlayerCharacter : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAI_PlayerCharacter();
	~UAI_PlayerCharacter();

public:
	void PlayClientAttackMontage();
	void PlayClientSkillMontage(const int32 inSkillid);
	void PlaySkillMontage(const int32 inSkillid, const float inTimeStamp);
	void JumpAttackMontageSection(const int32 inAttackCount, const float inTimeStamp);

public:
	void SetClientAnimWorking(bool InClientAnimWorking) { bClientAnimWorking = InClientAnimWorking; }

public:
	int32 GetAttackCount() const { return mAttackCount; }
	bool GetClientAnimWorking() const { return bClientAnimWorking; }

protected:
	virtual void NativeInitializeAnimation() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Properties", meta = (AllowPrivateAccess = "true"))
	float mMovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Properties", meta = (AllowPrivateAccess = "true"))
	float mMovementDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	ANC_Game* mMainCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Attack | Anim", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> mAttackFullMontage;	
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Attack | Anim", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> mAttackClientMontage;	
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Skill | Anim", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> mSkillFullMontage;	
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Skill | Anim", meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> mSkillClientMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Attack | Bool", meta = (AllowPrivateAccess = "true"))
	bool bIsAttack;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Attack | Bool", meta = (AllowPrivateAccess = "true"))
	bool bSaveAttack;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Attack | Bool", meta = (AllowPrivateAccess = "true"))
	bool bAttackLoop;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Attack | Client", meta = (AllowPrivateAccess = "true"))
	bool bClientAnimWorking;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Attack | Int", meta = (AllowPrivateAccess = "true"))
	int32 mAttackCount;

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
	void InitAttackMontage();
	void InitSkillMontage();
};
