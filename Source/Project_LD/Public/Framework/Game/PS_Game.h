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
	float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Attack", meta = (AllowPrivateAccess = "true"))
	float AttackRadius;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Health", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Mana", meta = (AllowPrivateAccess = "true"))
	float MaxMana;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Mana", meta = (AllowPrivateAccess = "true"))
	float CurrentMana;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Level", meta = (AllowPrivateAccess = "true"))
	int32 CharacterLevel;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "PlayerState | Condition", meta = (AllowPrivateAccess = "true"))
	bool IsAttacking;

public:
	void Init(const int64 inRemoteID);
	
public:
	int64 GetRemoteID();

public:
	int64 mRemoteID;
};
