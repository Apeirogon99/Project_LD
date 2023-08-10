// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkPlayerState.h"
#include <Struct/Game/CharacterDatas.h>
#include <Struct/Game/GameDatas.h>
#include "NPS_Game.generated.h"

/**
 * 
 */


UCLASS()
class PROJECT_LD_API ANPS_Game : public ANetworkPlayerState
{
	GENERATED_BODY()
	
public:
	ANPS_Game();
	~ANPS_Game();

public:
	void UpdateCurrentStats(); // stats Update
	void SetRemotePlayerID(const int64 inRemoteID);
	void SetCharacterData(const FCharacterData& InCharacterDatas);
	void SetCharacterEqipment(const FCharacterEquipment& inCharacterEquipment);
	void calculationStats();

public:
	const int64				GetRemoteID() const { return mRemoteID; }
	FCharacterData&	GetCharacterData()	 { return mCharacterData; }
	FCharacterStats&	GetCharacterStats() { return mCharacterStats; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState")
	int64 mRemoteID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState | Data")
	FCharacterData mCharacterData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState | Status")
	FCharacterStats	mCharacterStats;
};
