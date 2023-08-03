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

UCLASS()
class PROJECT_LD_API APS_Game : public ANPS_Game
{
	GENERATED_BODY()

public:
	APS_Game();
	~APS_Game();

public:
	FOnCharacterHealthChanged OnCharacterHealthChanged;
	FOnCharacterManaChanged OnCharacterManaChanged;

public:
	void UpdateCurrentStats();
	void InitializeLocalPlayerState();

public:
	UFUNCTION(BlueprintPure, Category = "ProgressBar")
		float GetHealthBarPercent() const;

	UFUNCTION(BlueprintPure, Category = "ProgressBar")
		float GetManaBarPercent() const;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState | Component")
	UACInventoryComponent* mInventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState | Component")
	UACEquipment* mEquipmentComponent;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "ProgressBar", meta = (AllowPrivateAccess = "true"))
	float mHealthBarPercent;

	UPROPERTY(BlueprintReadOnly, Category = "ProgressBar", meta = (AllowPrivateAccess = "true"))
	float mManaBarPercent;

protected:
	virtual void UpdateHealthBar();
	virtual void UpdateManaBar();
};
