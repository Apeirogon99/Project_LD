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

public:
	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnSpawn(float inStartTime);
	virtual float OnSpawn_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnIdle(float inStartTime);
	virtual float OnIdle_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnRound(float inStartTime);
	virtual float OnRound_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnRecovery(float inStartTime);
	virtual float OnRecovery_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnChase(float inStartTime);
	virtual float OnChase_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnAttack(float inStartTime);
	virtual float OnAttack_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnAttackCritical(float inStartTime);
	virtual float OnAttackCritical_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnHit(float inStartTime);
	virtual float OnHit_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnStun(float inStartTime);
	virtual float OnStun_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnDeath(float inStartTime);
	virtual float OnDeath_Implementation(float inStartTime);

};
