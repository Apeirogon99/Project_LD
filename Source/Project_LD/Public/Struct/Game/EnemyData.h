// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECT_LD_API FEnemyData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	FEnemyData() : enemy_class_id(0), level(0), name(""), enemy_class_path("") {}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	int32 enemy_class_id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	int32 level;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Data")
	FString	name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 enemy_class_id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_armor_penetration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_attack_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_attack_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_critical_strike_chance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_cirtical_strike_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_life_steal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_ability_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_mage_penetration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_omnivamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_physical_vamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_armor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_heal_and_shield_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_health_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_magic_resistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_tenacity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_slow_resist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_ability_haste;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_mana_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_movement_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		float base_range;
};