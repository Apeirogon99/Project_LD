// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPS_Game.h"
#include <Struct/Inventory/InventoryFrame.h>
#include <Component/ACInventoryComponent.h>
#include <Component/ACEquipment.h>
#include <Component/ACPartyComponent.h>
#include "PS_Game.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnCharacterExpChanged)

UCLASS()
class PROJECT_LD_API APS_Game : public ANPS_Game
{
	GENERATED_BODY()

public:
	APS_Game();
	~APS_Game();

public:
	FOnCharacterExpChanged				OnCharacterExpChanged;

protected:
	virtual void BeginPlay() override;

public:
	void UpdateExpValue(int InExp);
	void InitializeLocalPlayerState();
	void InitializeLocalPlayerData();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState | Component")
	UACInventoryComponent* mInventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState | Component")
	UACEquipment* mEquipmentComponent;

public:
	UACPartyComponent* GetPartyComponent();

protected:
	virtual void UpdateExpBar();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState | Component", meta = (AllowPrivateAccess = "true"))
		UACPartyComponent* mPartyComponent;
};
