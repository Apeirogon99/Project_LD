// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */

class AEnemyBase;
class AEnemyState;

UCLASS()
class PROJECT_LD_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeInitializeAnimation() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Properties", meta = (AllowPrivateAccess = "true"))
	float mMovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	AEnemyBase* mCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	AEnemyState* mEnemyState;

private:
	UFUNCTION(BlueprintCallable, Category = "Update Properties")
	void UpdateProperties();
};
