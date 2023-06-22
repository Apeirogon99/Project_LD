// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "CharacterStatusData.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FStatusBaseData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	FStatusBaseData() :
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	int32 character_class_id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_armor_penetration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_attack_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_attack_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_critical_strike_chance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_cirtical_strike_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_life_steal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_ability_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_mage_penetration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_omnivamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_physical_vamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_armor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_heal_and_shield_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_health_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_magic_resistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_tenacity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_slow_resist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_ability_haste;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_mana_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_movement_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
	float base_range;	
};

USTRUCT(Atomic, BlueprintType)
struct FCharacterBaseStatus
{
	GENERATED_USTRUCT_BODY()

public:
	FCharacterBaseStatus();
	FCharacterBaseStatus(const FCharacterBaseStatus& inCharacterStatus) { UpdateCharacterBaseStatus(inCharacterStatus); }
	FCharacterBaseStatus& operator=(const FCharacterBaseStatus& inCharacterStatus) { UpdateCharacterBaseStatus(inCharacterStatus); return *this; }

	void UpdateCharacterBaseStatus(const FCharacterBaseStatus& inCharacterStatus);
	TArray<float> FDataToFloat();

public:
	FStatusBaseData mBaseStatus;
};

USTRUCT(Atomic, BlueprintType)
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	int32 character_class_id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_armor_penetration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_attack_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_attack_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_critical_strike_chance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_cirtical_strike_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_life_steal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_ability_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_mage_penetration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_omnivamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_physical_vamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_armor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_heal_and_shield_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_health_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_magic_resistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_tenacity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_slow_resist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_ability_haste;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_mana_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_movement_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth")
	float grow_range;
};

USTRUCT(Atomic, BlueprintType)
struct FCharacterGrowStatus
{
	GENERATED_USTRUCT_BODY()
		
public:
	FCharacterGrowStatus();
	FCharacterGrowStatus(const FCharacterGrowStatus& inCharacterStatus) { UpdateCharacterGrowStatus(inCharacterStatus); }
	FCharacterGrowStatus& operator=(const FCharacterGrowStatus& inCharacterStatus) { UpdateCharacterGrowStatus(inCharacterStatus); return *this; }

	void UpdateCharacterGrowStatus(const FCharacterGrowStatus& inCharacterStatus);
	TArray<float> FDataToFloat();

public:
	FStatusGrowthData mGrowStatus;
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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float item_id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float armor_penteration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float attack_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float attack_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float critical_strike_chance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float cirtical_strike_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float life_steal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float ability_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float mage_penetration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float omnivamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float physical_vamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float armor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float heal_and_shield_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float health_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float magic_resistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float tenacity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float slow_resist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float ability_haste;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float mana_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float movement_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status")
		float range;
};

USTRUCT(Atomic, BlueprintType)
struct FCharacterEquipmentStatus
{
	GENERATED_USTRUCT_BODY()

public:
	FCharacterEquipmentStatus();
	FCharacterEquipmentStatus(const FCharacterEquipmentStatus& inCharacterStatus) { UpdateEquipmentStatus(inCharacterStatus); }
	FCharacterEquipmentStatus& operator=(const FCharacterEquipmentStatus& inCharacterStatus) { UpdateEquipmentStatus(inCharacterStatus); return *this; }

	void UpdateEquipmentStatus(const FCharacterEquipmentStatus& inCharacterStatus);
	TArray<float> FDataToFloat();

public:
	FEquipmentItemData mEquipmentStatus;
};

UCLASS()
class PROJECT_LD_API ACharacterStatusData : public AActor
{
	GENERATED_BODY()
};
