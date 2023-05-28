// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkPlayerState.h"
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
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Attack", meta = (AllowPrivateAccess = "true"))
	float mAttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Attack", meta = (AllowPrivateAccess = "true"))
	float mAttackRadius;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Health", meta = (AllowPrivateAccess = "true"))
	float mMaxHealth;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Health", meta = (AllowPrivateAccess = "true"))
	float mCurrentHealth;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Mana", meta = (AllowPrivateAccess = "true"))
	float mMaxMana;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Mana", meta = (AllowPrivateAccess = "true"))
	float mCurrentMana;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Level", meta = (AllowPrivateAccess = "true"))
	int32 mCharacterLevel;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Condition", meta = (AllowPrivateAccess = "true"))
	bool mIsAttacking;

public:
	void Init(const int64 inRemoteID);
	
public:
	int64 GetRemoteID();

public:
	int64 mRemoteID;
};
