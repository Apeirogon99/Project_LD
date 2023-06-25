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

UCLASS()
class PROJECT_LD_API APS_Game : public ANPS_Game
{
	GENERATED_BODY()

public:
	APS_Game();
	~APS_Game();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState | Component", meta = (AllowPrivateAccess = "true"))
	UACInventoryComponent* mInventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState | Component")
	UACEquipment* mEquipmentComponent;

public:
	void InitializeLocalPlayerState();

};
