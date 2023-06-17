// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkPlayerState.h"
#include <Struct/Game/GameDatas.h>
#include <Struct/Inventory/InventoryFrame.h>
#include <Component/ACInventoryComponent.h>
#include <Component/ACEquipment.h>
#include "PS_Game.generated.h"

/**
 * 
 */

UCLASS()
class PROJECT_LD_API APS_Game : public ANetworkPlayerState
{
	GENERATED_BODY()

public:
	APS_Game();
	~APS_Game();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UACInventoryComponent* mInventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	UACEquipment* mEquipmentComponent;

public:
	void Init(const int64 inRemoteID);
	
public:
	int64 GetRemoteID();

public:
	int64 mRemoteID;

};
