// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPS_Game.h"
#include <Struct/Inventory/InventoryFrame.h>
#include <Component/ACInventoryComponent.h>
#include <Component/ACEquipment.h>
#include "PS_Game.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnCharacterHealthChanged)
DECLARE_MULTICAST_DELEGATE(FOnCharacterManaChanged)
DECLARE_MULTICAST_DELEGATE(FOnCharacterExpChanged)

UCLASS()
class PROJECT_LD_API APS_Game : public ANPS_Game
{
	GENERATED_BODY()

public:
	APS_Game();
	~APS_Game();

public:
	FOnCharacterHealthChanged			OnCharacterHealthChanged;
	FOnCharacterManaChanged			OnCharacterManaChanged;
	FOnCharacterExpChanged				OnCharacterExpChanged;

public:
	void UpdateCurrentStats();
	void UpdateExpValue(float InExp);
	void InitializeLocalPlayerState();
	void InitializeLocalPlayerData();

public:
	UFUNCTION(BlueprintPure, Category = "ProgressBar")
	float GetHealthBarPercent() const;

	UFUNCTION(BlueprintPure, Category = "ProgressBar")
	float GetManaBarPercent() const;

	UFUNCTION(BlueprintPure, Category = "ProgressBar")
	float GetExpBarPercent() const;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState | Component")
	UACInventoryComponent* mInventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState | Component")
	UACEquipment* mEquipmentComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProgressBar", meta = (AllowPrivateAccess = "true"))
	float mHealthBarPercent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProgressBar", meta = (AllowPrivateAccess = "true"))
	float mManaBarPercent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProgressBar", meta = (AllowPrivateAccess = "true"))
	float mExpBarPercent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProgressBar", meta = (AllowPrivateAccess = "true"))
	float mCurrentExp;

protected:
	virtual void UpdateHealthBar();
	virtual void UpdateManaBar();
	virtual void UpdateExpBar();
};
