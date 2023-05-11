// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Character/AppearanceCharacter.h"
#include "GameCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AGameCharacter : public AAppearanceCharacter
{
	GENERATED_BODY()
	
public:
	AGameCharacter();
	virtual ~AGameCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* GameCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class UUWInventory* InventoryWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UUserWidget>    MainWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UACInventoryComponent* InventoryComponent;

	/*
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;
		*/

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
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return GameCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	//FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
	FORCEINLINE float GetAttackRange() const { return AttackRange; }
	FORCEINLINE float GetAttackRadius() const { return AttackRadius; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
	FORCEINLINE float GetMaxMana() const { return MaxMana; }
	FORCEINLINE float GetCurrentMana() const { return CurrentMana; }
	FORCEINLINE bool GetIsAttacking() const { return IsAttacking; }
	FORCEINLINE int32 GetCharacterLevel() const { return CharacterLevel; }

public:
	void SetAttackRange(float NewRange) { AttackRange = NewRange; }
	void SetAttackRadius(float NewRadius) { AttackRadius = NewRadius; }
	void SetMaxHealth(float NewMaxHealth) { MaxHealth = NewMaxHealth; }
	void SetCurrentHealth(float NewCurrentHealth) { CurrentHealth = NewCurrentHealth; }
	void SetMaxMana(float NewMaxMana) { MaxMana = NewMaxMana; }
	void SetCurrentMana(float NewCurrentMana) { CurrentMana = NewCurrentMana; }
	void SetIsAttacking(bool NewIsAttacking) { IsAttacking = NewIsAttacking; }
	void SetCharacterLevel(int32 NewLevel) { CharacterLevel = NewLevel; }

public:
	UFUNCTION()
	void OpenInventory();

	UFUNCTION()
	void InteractItem();
};
