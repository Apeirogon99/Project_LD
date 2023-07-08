// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyData.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EEnemyStateType : uint8
{
	State_Unspecified	UMETA(DisPlayNone = "None"),
	State_Idle			UMETA(DisplayName = "Idle"),
	State_Round			UMETA(DisplayName = "Round"),
	State_Recovery		UMETA(DisplayName = "Recovery"),
	State_Chase			UMETA(DisplayName = "Chase"),
	State_Attack		UMETA(DisplayName = "Attack"),
	State_Hit			UMETA(DisplayName = "Hit"),
	State_Stun			UMETA(DisplayName = "Stun"),
	State_Death			UMETA(DisplayName = "Death")
};

USTRUCT(BlueprintType)
struct PROJECT_LD_API FEnemyData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	FEnemyData() : enemy_class_id(0), level(0), name(""), enemy_class_path("") {}

public:
	void SetEnemyClassID(const int32 inEnemyClassID) { enemy_class_id = inEnemyClassID; }
	void SetLevel(const int32 inLevel) { level = inLevel; }
	void SetName(const FString inName) { name = inName; }
	void SetEnemyClassPath(const FString inEnemyClassPath) { enemy_class_path = inEnemyClassPath; }

public:
	int32			GetEnemyClassID()	 const			{ return enemy_class_id; }
	int32			GetLevel() const							{ return level; }
	FString		GetName() const							{ return name; }
	FString		GetEnemyClassPath() const		{ return enemy_class_path; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32 enemy_class_id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32 level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FString	name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FString enemy_class_path;

};

USTRUCT(BlueprintType)
struct PROJECT_LD_API FEnemyStatData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FEnemyStatData() :
		enemy_class_id(0),
		base_armor_penetration(0),
		base_attack_damage(0),
		base_attack_speed(0),
		base_critical_strike_chance(0),
		base_cirtical_strike_damage(0),
		base_life_steal(0),
		base_ability_power(0),
		base_mage_penetration(0),
		base_omnivamp(0),
		base_physical_vamp(0),
		base_armor(0),
		base_heal_and_shield_power(0),
		base_health(0),
		base_health_regeneration(0),
		base_magic_resistance(0),
		base_tenacity(0),
		base_slow_resist(0),
		base_ability_haste(0),
		base_mana(0),
		base_mana_regeneration(0),
		base_movement_speed(0),
		base_range(0) {}

public:
	UPROPERTY()
		int32 enemy_class_id;

	UPROPERTY()
		float base_armor_penetration;

	UPROPERTY()
		float base_attack_damage;

	UPROPERTY()
		float base_attack_speed;

	UPROPERTY()
		float base_critical_strike_chance;

	UPROPERTY()
		float base_cirtical_strike_damage;

	UPROPERTY()
		float base_life_steal;

	UPROPERTY()
		float base_ability_power;

	UPROPERTY()
		float base_mage_penetration;

	UPROPERTY()
		float base_omnivamp;

	UPROPERTY()
		float base_physical_vamp;

	UPROPERTY()
		float base_armor;

	UPROPERTY()
		float base_heal_and_shield_power;

	UPROPERTY()
		float base_health;

	UPROPERTY()
		float base_health_regeneration;

	UPROPERTY()
		float base_magic_resistance;

	UPROPERTY()
		float base_tenacity;

	UPROPERTY()
		float base_slow_resist;

	UPROPERTY()
		float base_ability_haste;

	UPROPERTY()
		float base_mana;

	UPROPERTY()
		float base_mana_regeneration;

	UPROPERTY()
		float base_movement_speed;

	UPROPERTY()
		float base_range;
};

USTRUCT(Atomic, BlueprintType)
struct FEnemyBaseStats
{
	GENERATED_USTRUCT_BODY()

public:
	FEnemyBaseStats();
	FEnemyBaseStats(const FEnemyBaseStats& inEnemyStats) { UpdateEnemyStats(inEnemyStats); }
	FEnemyBaseStats& operator=(const FEnemyBaseStats& inEnemyStats) { UpdateEnemyStats(inEnemyStats); return *this; }

	void UpdateEnemyStats(const FEnemyBaseStats& inCharacterStats);
	TArray<float> FDataToFloat();

public:
	void SetStatsBaseData(const FEnemyStatData InBaseStats) { mBaseStats = InBaseStats; }

public:
	FEnemyStatData GetStatsBaseData() const { return mBaseStats; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FEnemyStatData mBaseStats;
};