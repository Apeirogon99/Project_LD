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

class UACPartyComponent;

DECLARE_MULTICAST_DELEGATE(FOnCharacterHealthChanged)
DECLARE_MULTICAST_DELEGATE(FOnCharacterManaChanged)

UCLASS()
class PROJECT_LD_API ANPS_Game : public ANetworkPlayerState
{
	GENERATED_BODY()
	
public:
	ANPS_Game();
	~ANPS_Game();

public:
	FOnCharacterHealthChanged		OnCharacterHealthChanged;
	FOnCharacterManaChanged			OnCharacterManaChanged;

public:
	void UpdateCurrentStatsBar(); // stats Update
	void SetRemotePlayerID(const int64 inRemoteID);
	void SetCharacterData(const FCharacterData& InCharacterDatas);
	void SetCharacterEqipment(const FCharacterEquipment& inCharacterEquipment);
	void calculationStats();
	void DetectChangeCurrentStats(FCharacterEquipment oldData, FCharacterEquipment newData);
	void PutOnEquipment(const int32 InIndex);
	void TakeOffEquipment(const int32 InIndex);
	void InitCurrentStats();
	void InitCurrentEquipmentStats();
	void InitPartySetting();

public:
	const int64			GetRemoteID() const		{ return mRemoteID; }
	FCharacterData&		GetCharacterData()		{ return mCharacterData; }
	FCharacterStats&	GetCharacterStats()		{ return mCharacterStats; }

public:
	UACPartyComponent* GetPartyComponent();

protected:
	virtual void Destroyed() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState")
	int64 mRemoteID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState | Data")
	FCharacterData mCharacterData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState | Status")
	FCharacterStats	mCharacterStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerState | Component", meta = (AllowPrivateAccess = "true"))
	UACPartyComponent* mPartyComponent;

protected:
	virtual void UpdateHealthBar();
	virtual void UpdateManaBar();
};
