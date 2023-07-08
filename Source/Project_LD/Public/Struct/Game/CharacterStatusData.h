// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "CharacterStatusData.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FStatsBaseData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	FStatsBaseData() :
		character_class_id(0),
		base_armor_penetration(0),
		base_attack_damage(0),
		base_attack_speed(0),
		base_critical_strike_chance(0),
		base_cirtical_strike_damage(0),
		base_life_steal	(0),
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
	int32 character_class_id;

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
struct FCharacterBaseStats
{
	GENERATED_USTRUCT_BODY()

public:
	FCharacterBaseStats();
	FCharacterBaseStats(const FCharacterBaseStats& inCharacterStats) { UpdateCharacterBaseStats(inCharacterStats); }
	FCharacterBaseStats& operator=(const FCharacterBaseStats& inCharacterStats) { UpdateCharacterBaseStats(inCharacterStats); return *this; }

	void UpdateCharacterBaseStats(const FCharacterBaseStats& inCharacterStats);
	TArray<float> FDataToFloat();

public:
	void SetStatsBaseData(const FStatsBaseData InBaseStats) { mBaseStats = InBaseStats; }
	
public:
	FStatsBaseData GetStatsBaseData() const { return mBaseStats; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FStatsBaseData mBaseStats;
};

USTRUCT(Atomic, BlueprintType)
struct FStatsGrowthData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FStatsGrowthData() :
		character_class_id(0),
		grow_armor_penetration(0),
		grow_attack_damage(0),
		grow_attack_speed(0),
		grow_critical_strike_chance(0),
		grow_cirtical_strike_damage(0),
		grow_life_steal(0),
		grow_ability_power(0),
		grow_mage_penetration(0),
		grow_omnivamp(0),
		grow_physical_vamp(0),
		grow_armor(0),
		grow_heal_and_shield_power(0),
		grow_health(0),
		grow_health_regeneration(0),
		grow_magic_resistance(0),
		grow_tenacity(0),
		grow_slow_resist(0),
		grow_ability_haste(0),
		grow_mana(0),
		grow_mana_regeneration(0),
		grow_movement_speed(0),
		grow_range(0) {}

public:
	UPROPERTY()
	int32 character_class_id;

	UPROPERTY()
	float grow_armor_penetration;

	UPROPERTY()
	float grow_attack_damage;

	UPROPERTY()
	float grow_attack_speed;

	UPROPERTY()
	float grow_critical_strike_chance;

	UPROPERTY()
	float grow_cirtical_strike_damage;

	UPROPERTY()
	float grow_life_steal;

	UPROPERTY()
	float grow_ability_power;

	UPROPERTY()
	float grow_mage_penetration;

	UPROPERTY()
	float grow_omnivamp;

	UPROPERTY()
	float grow_physical_vamp;

	UPROPERTY()
	float grow_armor;

	UPROPERTY()
	float grow_heal_and_shield_power;

	UPROPERTY()
	float grow_health;

	UPROPERTY()
	float grow_health_regeneration;

	UPROPERTY()
	float grow_magic_resistance;

	UPROPERTY()
	float grow_tenacity;

	UPROPERTY()
	float grow_slow_resist;

	UPROPERTY()
	float grow_ability_haste;

	UPROPERTY()
	float grow_mana;

	UPROPERTY()
	float grow_mana_regeneration;

	UPROPERTY()
	float grow_movement_speed;

	UPROPERTY()
	float grow_range;
};

USTRUCT(Atomic, BlueprintType)
struct FCharacterGrowStats
{
	GENERATED_USTRUCT_BODY()
		
public:
	FCharacterGrowStats();
	FCharacterGrowStats(const FCharacterGrowStats& inCharacterStats) { UpdateCharacterGrowStats(inCharacterStats); }
	FCharacterGrowStats& operator=(const FCharacterGrowStats& inCharacterStats) { UpdateCharacterGrowStats(inCharacterStats); return *this; }

	void UpdateCharacterGrowStats(const FCharacterGrowStats& inCharacterStatus);
	TArray<float> FDataToFloat();

public:
	void SetStatsGrowData(const FStatsGrowthData InGrowStats) { mGrowStats = InGrowStats; }

public:
	FStatsGrowthData GetStatsGrowData() const { return mGrowStats; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FStatsGrowthData mGrowStats;
};

USTRUCT(Atomic, BlueprintType)
struct FEquipmentItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FEquipmentItemData() :
		item_id(0),
		armor_penteration(0),
		attack_damage(0),
		attack_speed(0),
		critical_strike_chance(0),
		cirtical_strike_damage(0),
		life_steal(0),
		ability_power(0),
		mage_penetration(0),
		omnivamp(0),
		physical_vamp(0),
		armor(0),
		heal_and_shield_power(0),
		health(0),
		health_regeneration(0),
		magic_resistance(0),
		tenacity(0),
		slow_resist(0),
		ability_haste(0),
		mana(0),
		mana_regeneration(0),
		movement_speed(0),
		range(0) {}
	
public:
	UPROPERTY()
		float item_id;

	UPROPERTY()
		float armor_penteration;

	UPROPERTY()
		float attack_damage;

	UPROPERTY()
		float attack_speed;

	UPROPERTY()
		float critical_strike_chance;
	
	UPROPERTY()
		float cirtical_strike_damage;

	UPROPERTY()
		float life_steal;

	UPROPERTY()
		float ability_power;

	UPROPERTY()
		float mage_penetration;

	UPROPERTY()
		float omnivamp;

	UPROPERTY()
		float physical_vamp;

	UPROPERTY()
		float armor;

	UPROPERTY()
		float heal_and_shield_power;

	UPROPERTY()
		float health;

	UPROPERTY()
		float health_regeneration;

	UPROPERTY()
		float magic_resistance;

	UPROPERTY()
		float tenacity;

	UPROPERTY()
		float slow_resist;

	UPROPERTY()
		float ability_haste;

	UPROPERTY()
		float mana;

	UPROPERTY()
		float mana_regeneration;

	UPROPERTY()
		float movement_speed;

	UPROPERTY()
		float range;
};

USTRUCT(Atomic, BlueprintType)
struct FCharacterEquipmentStats
{
	GENERATED_USTRUCT_BODY()

public:
	FCharacterEquipmentStats();
	FCharacterEquipmentStats(const FCharacterEquipmentStats& inCharacterStats) { UpdateEquipmentStats(inCharacterStats); }
	FCharacterEquipmentStats& operator=(const FCharacterEquipmentStats& inCharacterStats) { UpdateEquipmentStats(inCharacterStats); return *this; }

	void UpdateEquipmentStats(const FCharacterEquipmentStats& inCharacterStats);
	TArray<float> FDataToFloat();

public:
	void SetStatsData(const FEquipmentItemData InEquipmentStats) { mEquipmentStats = InEquipmentStats; }

public:
	FEquipmentItemData GetStatsData() const { return mEquipmentStats; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FEquipmentItemData mEquipmentStats;
};

UCLASS()
class PROJECT_LD_API ACharacterStatusData : public AActor
{
	GENERATED_BODY()
};
