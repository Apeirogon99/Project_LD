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
	virtual void OnSpawn_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnIdle(float inStartTime);
	virtual void OnIdle_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnRound(float inStartTime);
	virtual void OnRound_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnRecovery(float inStartTime);
	virtual void OnRecovery_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnChase(float inStartTime);
	virtual void OnChase_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnAttack(float inStartTime);
	virtual void OnAttack_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnAttackCritical(float inStartTime);
	virtual void OnAttackCritical_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnHit(float inStartTime);
	virtual void OnHit_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnStun(float inStartTime);
	virtual void OnStun_Implementation(float inStartTime);

	UFUNCTION(BlueprintNativeEvent, Category = "State")
	void OnDeath(float inStartTime);
	virtual void OnDeath_Implementation(float inStartTime);

};
