// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Character/AppearanceCharacter.h"
#include "C_Game.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AC_Game : public AAppearanceCharacter
{
	GENERATED_BODY()

public:
	AC_Game();
	~AC_Game();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* GameCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
		class UACInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
		float AttackRadius;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
		float MaxHealth;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
		float CurrentHealth;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Mana", meta = (AllowPrivateAccess = "true"))
		float MaxMana;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Mana", meta = (AllowPrivateAccess = "true"))
		float CurrentMana;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Level", meta = (AllowPrivateAccess = "true"))
		int32 CharacterLevel;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Condition", meta = (AllowPrivateAccess = "true"))
		bool IsAttacking;

public:
	UFUNCTION()
		void InteractItem();
};
