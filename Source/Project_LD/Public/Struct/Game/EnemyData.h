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
	void SetBaseArmorPenetration(const float inbase_armor_penetration)											{ base_armor_penetration = inbase_armor_penetration; }
	void SetBaseAttackDamage(const float inbase_attack_damage)														{ base_attack_damage = inbase_attack_damage; }
	void SetBaseAttackSpeed(const float inbase_attack_speed)																{ base_attack_speed = inbase_attack_speed; }
	void SetBaseCriticalStrikeChance(const float inbase_critical_strike_chance)								{ base_critical_strike_chance = inbase_critical_strike_chance; }
	void SetBaseCriticalStrikeDamage(const float inbase_cirtical_strike_damage)								{ base_cirtical_strike_damage = inbase_cirtical_strike_damage; }
	void SetBaseLifeSteal(const float inbase_life_steal)																		{ base_life_steal = inbase_life_steal; }
	void SetBaseAbilityPower(const float inbase_ability_power)															{ base_ability_power = inbase_ability_power; }
	void SetBaseMagePenetration(const float inbase_mage_penetration)												{ base_mage_penetration = inbase_mage_penetration; }
	void SetBaseOmniVamp(const float inbase_omnivamp)																	{ base_omnivamp = inbase_omnivamp; }
	void SetBasePhysicalVamp(const float inbase_physical_vamp)														{ base_physical_vamp = inbase_physical_vamp; }
	void SetBaseArmor(const float inbase_armor)																					{ base_armor = inbase_armor; }
	void SetBaseHealAndShieldPower(const float inbase_heal_and_shield_power)								{ base_heal_and_shield_power = inbase_heal_and_shield_power; }
	void SetBaseHealth(const float inbase_health)																					{ base_health = inbase_health; }
	void SetBaseHealthRegeneration(const float inbase_health_regeneration)										{ base_health_regeneration = inbase_health_regeneration; }
	void SetBaseMagicResistance(const float inbase_magic_resistance)												{ base_magic_resistance = inbase_magic_resistance; }
	void SetBaseTenacity(const float inbase_tenacity)																			{ base_tenacity = inbase_tenacity; }
	void SetBaseSlowResist(const float inbase_slow_resist)																	{ base_slow_resist = inbase_slow_resist; }
	void SetBaseAbilityHaste(const float inbase_ability_haste)																{ base_ability_haste = inbase_ability_haste; }
	void SetBaseMana(const float inbase_mana)																						{ base_mana = inbase_mana; }
	void SetBaseManaRegeneration(const float inbase_mana_regeneration)											{ base_mana_regeneration  = inbase_mana_regeneration; }
	void SetBaseMovementSpeed(const float inbase_movement_speed)													{ base_movement_speed = inbase_movement_speed; }
	void SetBaseRange(const float inbase_range)																					{ base_range = inbase_range; }

public:
	float GetBaseArmorPenetration() const						{ return base_armor_penetration; }
	float GetBaseAttackDamage() const							{ return base_attack_damage; }
	float GetBaseAttackSpeed() const								{ return base_attack_speed; }
	float GetBaseCriticalStrikeChance() const				{ return base_critical_strike_chance; }
	float GetBaseCriticalStrikeDamage() const				{ return base_cirtical_strike_damage; }
	float GetBaseLifeSteal() const									{ return base_life_steal; }
	float GetBaseAbilityPower() const								{ return base_ability_power; }
	float GetBaseMagePenetration() const						{ return base_mage_penetration; }
	float GetBaseOmniVamp() const								{ return base_omnivamp; }
	float GetBasePhysicalVamp() const							{ return base_physical_vamp; }
	float GetBaseArmor() const										{ return base_armor; }
	float GetBaseHealAndShieldPower() const				{ return base_heal_and_shield_power; }
	float GetBaseHealth() const										{ return base_health; }
	float GetBaseHealthRegeneration() const					{ return base_health_regeneration; }
	float GetBaseMagicResistance() const						{ return base_magic_resistance; }
	float GetBaseTenacity() const									{ return base_tenacity; }
	float GetBaseSlowResist() const								{ return base_slow_resist; }
	float GetBaseAbilityHaste() const								{ return base_ability_haste; }
	float GetBaseMana() const											{ return base_mana; }
	float GetBaseManaRegeneration() const					{ return base_mana_regeneration; }
	float GetBaseMovementSpeed() const						{ return base_movement_speed; }
	float GetBaseRange() const										{ return base_range; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		int32 enemy_class_id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_armor_penetration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_attack_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_attack_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_critical_strike_chance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_cirtical_strike_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_life_steal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_ability_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_mage_penetration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_omnivamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_physical_vamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_armor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_heal_and_shield_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_health_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_magic_resistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_tenacity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_slow_resist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_ability_haste;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_mana_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_movement_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float base_range;
};