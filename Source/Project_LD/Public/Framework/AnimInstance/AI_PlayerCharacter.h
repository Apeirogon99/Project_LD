// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AI_PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UAI_PlayerCharacter : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Properties", meta = (AllowPrivateAccess = "true"))
	float mMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Properties", meta = (AllowPrivateAccess = "true"))
	float mMovementDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Properties", meta = (AllowPrivateAccess = "true"))
	class APawn* mPawn; //Character�� �����ؼ� ���� ����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement Properties", meta = (AllowPrivateAccess = "true"))
	class AC_Game* mMainCharacter;

private:
	UFUNCTION(BlueprintCallable, Category = "Update Properties")
	void UpdateProperties();
};
