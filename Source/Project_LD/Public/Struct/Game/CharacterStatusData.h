// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "CharacterStatusData.generated.h"

USTRUCT(BlueprintType)
struct FStatusData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FStatusData() :
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 character_class_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_armor_penetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_attack_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_attack_speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_critical_strike_chance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_cirtical_strike_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_life_steal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_ability_power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_mage_penetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_omnivamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_physical_vamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_heal_and_shield_power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_health_regeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_magic_resistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_tenacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_slow_resist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_ability_haste;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_mana_regeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_movement_speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
	int32 base_range;	
};

USTRUCT(BlueprintType)
struct FStatusGrowthData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FStatusGrowthData() :
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 character_class_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_armor_penetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_attack_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_attack_speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_critical_strike_chance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_cirtical_strike_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_life_steal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_ability_power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_mage_penetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_omnivamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_physical_vamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_heal_and_shield_power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_health_regeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_magic_resistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_tenacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_slow_resist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_ability_haste;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_mana_regeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_movement_speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusGrowth")
	int32 grow_range;
};

UCLASS()
class PROJECT_LD_API ACharacterStatusData : public AActor
{
	GENERATED_BODY()
};
