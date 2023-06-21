// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkPlayerState.h"

#include <Struct/Game/CharacterDatas.h>
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
	void InitializeLocalPlayerState();
	void SetRemotePlayerID(const int64 inRemoteID);
	void SetCharacterData(const FCharacterData& InCharacterDatas);
	void SetCharacterEqipment(const FCharacterEquipment& inCharacterEquipment);
	void calculationStatus();

public:
	const int64				GetRemoteID() const { return mRemoteID; }
	const FCharacterData&	GetCharacterData() const { return mCharacterData; }

protected:
	UPROPERTY()
	int64			mRemoteID;

	UPROPERTY()
	FCharacterData	mCharacterData;

	UPROPERTY()
	FCharacterStatus mCharacterStatus;

};
