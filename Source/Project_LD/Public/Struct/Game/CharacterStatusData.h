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

public:
	void SetBaseArmorPenetration(const float inbase_armor_penetration) { base_armor_penetration = inbase_armor_penetration; }
	void SetBaseAttackDamage(const float inbase_attack_damage) { base_attack_damage = inbase_attack_damage; }
	void SetBaseAttackSpeed(const float inbase_attack_speed) { base_attack_speed = inbase_attack_speed; }
	void SetBaseCriticalStrikeChance(const float inbase_critical_strike_chance) { base_critical_strike_chance = inbase_critical_strike_chance; }
	void SetBaseCriticalStrikeDamage(const float inbase_cirtical_strike_damage) { base_cirtical_strike_damage = inbase_cirtical_strike_damage; }
	void SetBaseLifeSteal(const float inbase_life_steal) { base_life_steal = inbase_life_steal; }
	void SetBaseAbilityPower(const float inbase_ability_power) { base_ability_power = inbase_ability_power; }
	void SetBaseMagePenetration(const float inbase_mage_penetration) { base_mage_penetration = inbase_mage_penetration; }
	void SetBaseOmniVamp(const float inbase_omnivamp) { base_omnivamp = inbase_omnivamp; }
	void SetBasePhysicalVamp(const float inbase_physical_vamp) { base_physical_vamp = inbase_physical_vamp; }
	void SetBaseArmor(const float inbase_armor) { base_armor = inbase_armor; }
	void SetBaseHealAndShieldPower(const float inbase_heal_and_shield_power) { base_heal_and_shield_power = inbase_heal_and_shield_power; }
	void SetBaseHealth(const float inbase_health) { base_health = inbase_health; }
	void SetBaseHealthRegeneration(const float inbase_health_regeneration) { base_health_regeneration = inbase_health_regeneration; }
	void SetBaseMagicResistance(const float inbase_magic_resistance) { base_magic_resistance = inbase_magic_resistance; }
	void SetBaseTenacity(const float inbase_tenacity) { base_tenacity = inbase_tenacity; }
	void SetBaseSlowResist(const float inbase_slow_resist) { base_slow_resist = inbase_slow_resist; }
	void SetBaseAbilityHaste(const float inbase_ability_haste) { base_ability_haste = inbase_ability_haste; }
	void SetBaseMana(const float inbase_mana) { base_mana = inbase_mana; }
	void SetBaseManaRegeneration(const float inbase_mana_regeneration) { base_mana_regeneration = inbase_mana_regeneration; }
	void SetBaseMovementSpeed(const float inbase_movement_speed) { base_movement_speed = inbase_movement_speed; }
	void SetBaseRange(const float inbase_range) { base_range = inbase_range; }

public:
	float GetBaseArmorPenetration() const { return base_armor_penetration; }
	float GetBaseAttackDamage() const { return base_attack_damage; }
	float GetBaseAttackSpeed() const { return base_attack_speed; }
	float GetBaseCriticalStrikeChance() const { return base_critical_strike_chance; }
	float GetBaseCriticalStrikeDamage() const { return base_cirtical_strike_damage; }
	float GetBaseLifeSteal() const { return base_life_steal; }
	float GetBaseAbilityPower() const { return base_ability_power; }
	float GetBaseMagePenetration() const { return base_mage_penetration; }
	float GetBaseOmniVamp() const { return base_omnivamp; }
	float GetBasePhysicalVamp() const { return base_physical_vamp; }
	float GetBaseArmor() const { return base_armor; }
	float GetBaseHealAndShieldPower() const { return base_heal_and_shield_power; }
	float GetBaseHealth() const { return base_health; }
	float GetBaseHealthRegeneration() const { return base_health_regeneration; }
	float GetBaseMagicResistance() const { return base_magic_resistance; }
	float GetBaseTenacity() const { return base_tenacity; }
	float GetBaseSlowResist() const { return base_slow_resist; }
	float GetBaseAbilityHaste() const { return base_ability_haste; }
	float GetBaseMana() const { return base_mana; }
	float GetBaseManaRegeneration() const { return base_mana_regeneration; }
	float GetBaseMovementSpeed() const { return base_movement_speed; }
	float GetBaseRange() const { return base_range; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	int32 character_class_id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_armor_penetration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_attack_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_attack_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_critical_strike_chance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_cirtical_strike_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_life_steal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_ability_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_mage_penetration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_omnivamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_physical_vamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_armor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_heal_and_shield_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_health_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_magic_resistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_tenacity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_slow_resist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_ability_haste;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_mana_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
	float base_movement_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
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
	void SetStatusBaseData(const FStatusBaseData InBaseStatus) { mBaseStatus = InBaseStatus; }
	
public:
	FStatusBaseData GetStatusBaseData() const { return mBaseStatus; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
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

public:
	void SetGrowArmorPenetration(const float ingrow_armor_penetration) { grow_armor_penetration = ingrow_armor_penetration; }
	void SetGrowAttackDamage(const float ingrow_attack_damage) { grow_attack_damage = ingrow_attack_damage; }
	void SetGrowAttackSpeed(const float ingrow_attack_speed) { grow_attack_speed = ingrow_attack_speed; }
	void SetGrowCriticalStrikeChance(const float ingrow_critical_strike_chance) { grow_critical_strike_chance = ingrow_critical_strike_chance; }
	void SetGrowCriticalStrikeDamage(const float ingrow_cirtical_strike_damage) { grow_cirtical_strike_damage = ingrow_cirtical_strike_damage; }
	void SetGrowLifeSteal(const float ingrow_life_steal) { grow_life_steal = ingrow_life_steal; }
	void SetGrowAbilityPower(const float ingrow_ability_power) { grow_ability_power = ingrow_ability_power; }
	void SetGrowMagePenetration(const float ingrow_mage_penetration) { grow_mage_penetration = ingrow_mage_penetration; }
	void SetGrowOmniVamp(const float ingrow_omnivamp) { grow_omnivamp = ingrow_omnivamp; }
	void SetGrowPhysicalVamp(const float ingrow_physical_vamp) { grow_physical_vamp = ingrow_physical_vamp; }
	void SetGrowArmor(const float ingrow_armor) { grow_armor = ingrow_armor; }
	void SetGrowHealAndShieldPower(const float ingrow_heal_and_shield_power) { grow_heal_and_shield_power = ingrow_heal_and_shield_power; }
	void SetGrowHealth(const float ingrow_health) { grow_health = ingrow_health; }
	void SetGrowHealthRegeneration(const float ingrow_health_regeneration) { grow_health_regeneration = ingrow_health_regeneration; }
	void SetGrowMagicResistance(const float ingrow_magic_resistance) { grow_magic_resistance = ingrow_magic_resistance; }
	void SetGrowTenacity(const float ingrow_tenacity) { grow_tenacity = ingrow_tenacity; }
	void SetGrowSlowResist(const float ingrow_slow_resist) { grow_slow_resist = ingrow_slow_resist; }
	void SetGrowAbilityHaste(const float ingrow_ability_haste) { grow_ability_haste = ingrow_ability_haste; }
	void SetGrowMana(const float ingrow_mana) { grow_mana = ingrow_mana; }
	void SetGrowManaRegeneration(const float ingrow_mana_regeneration) { grow_mana_regeneration = ingrow_mana_regeneration; }
	void SetGrowMovementSpeed(const float ingrow_movement_speed) { grow_movement_speed = ingrow_movement_speed; }
	void SetGrowRange(const float ingrow_range) { grow_range = ingrow_range; }

public:
	float GetGrowArmorPenetration() const { return grow_armor_penetration; }
	float GetGrowAttackDamage() const { return grow_attack_damage; }
	float GetGrowAttackSpeed() const { return grow_attack_speed; }
	float GetGrowCriticalStrikeChance() const { return grow_critical_strike_chance; }
	float GetGrowCriticalStrikeDamage() const { return grow_cirtical_strike_damage; }
	float GetGrowLifeSteal() const { return grow_life_steal; }
	float GetGrowAbilityPower() const { return grow_ability_power; }
	float GetGrowMagePenetration() const { return grow_mage_penetration; }
	float GetGrowOmniVamp() const { return grow_omnivamp; }
	float GetGrowPhysicalVamp() const { return grow_physical_vamp; }
	float GetGrowArmor() const { return grow_armor; }
	float GetGrowHealAndShieldPower() const { return grow_heal_and_shield_power; }
	float GetGrowHealth() const { return grow_health; }
	float GetGrowHealthRegeneration() const { return grow_health_regeneration; }
	float GetGrowMagicResistance() const { return grow_magic_resistance; }
	float GetGrowTenacity() const { return grow_tenacity; }
	float GetGrowSlowResist() const { return grow_slow_resist; }
	float GetGrowAbilityHaste() const { return grow_ability_haste; }
	float GetGrowMana() const { return grow_mana; }
	float GetGrowManaRegeneration() const { return grow_mana_regeneration; }
	float GetGrowMovementSpeed() const { return grow_movement_speed; }
	float GetGrowRange() const { return grow_range; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	int32 character_class_id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_armor_penetration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_attack_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_attack_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_critical_strike_chance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_cirtical_strike_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_life_steal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_ability_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_mage_penetration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_omnivamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_physical_vamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_armor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_heal_and_shield_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_health_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_magic_resistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_tenacity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_slow_resist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_ability_haste;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_mana_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
	float grow_movement_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StatusGrowth", meta = (AllowPrivateAccess = "true"))
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
	void SetStatusGrowData(const FStatusGrowthData InGrowStatus) { mGrowStatus = InGrowStatus; }

public:
	FStatusGrowthData GetStatusGrowData() const { return mGrowStatus; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
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
	
public:
	void SetArmorPenetration(const float inarmor_penetration) { armor_penteration = inarmor_penetration; }
	void SetAttackDamage(const float inattack_damage) { attack_damage = inattack_damage; }
	void SetAttackSpeed(const float inattack_speed) { attack_speed = inattack_speed; }
	void SetCriticalStrikeChance(const float incritical_strike_chance) { critical_strike_chance = incritical_strike_chance; }
	void SetCriticalStrikeDamage(const float incirtical_strike_damage) { cirtical_strike_damage = incirtical_strike_damage; }
	void SetLifeSteal(const float inlife_steal) { life_steal = inlife_steal; }
	void SetAbilityPower(const float inability_power) { ability_power = inability_power; }
	void SetMagePenetration(const float inmage_penetration) { mage_penetration = inmage_penetration; }
	void SetOmniVamp(const float inomnivamp) { omnivamp = inomnivamp; }
	void SetPhysicalVamp(const float inphysical_vamp) { physical_vamp = inphysical_vamp; }
	void SetArmor(const float inarmor) { armor = inarmor; }
	void SetHealAndShieldPower(const float inheal_and_shield_power) { heal_and_shield_power = inheal_and_shield_power; }
	void SetHealth(const float inhealth) { health = inhealth; }
	void SetHealthRegeneration(const float inhealth_regeneration) { health_regeneration = inhealth_regeneration; }
	void SetMagicResistance(const float inmagic_resistance) { magic_resistance = inmagic_resistance; }
	void SetTenacity(const float intenacity) { tenacity = intenacity; }
	void SetSlowResist(const float inslow_resist) { slow_resist = inslow_resist; }
	void SetAbilityHaste(const float inability_haste) { ability_haste = inability_haste; }
	void SetMana(const float inmana) { mana = inmana; }
	void SetManaRegeneration(const float inmana_regeneration) { mana_regeneration = inmana_regeneration; }
	void SetMovementSpeed(const float inmovement_speed) { movement_speed = inmovement_speed; }
	void SetRange(const float inrange) { range = inrange; }

public:
	float GetArmorPenetration() const { return armor_penteration; }
	float GetAttackDamage() const { return attack_damage; }
	float GetAttackSpeed() const { return attack_speed; }
	float GetCriticalStrikeChance() const { return critical_strike_chance; }
	float GetCriticalStrikeDamage() const { return cirtical_strike_damage; }
	float GetLifeSteal() const { return life_steal; }
	float GetAbilityPower() const { return ability_power; }
	float GetMagePenetration() const { return mage_penetration; }
	float GetOmniVamp() const { return omnivamp; }
	float GetPhysicalVamp() const { return physical_vamp; }
	float GetArmor() const { return armor; }
	float GetHealAndShieldPower() const { return heal_and_shield_power; }
	float GetHealth() const { return health; }
	float GetHealthRegeneration() const { return health_regeneration; }
	float GetMagicResistance() const { return magic_resistance; }
	float GetTenacity() const { return tenacity; }
	float GetSlowResist() const { return slow_resist; }
	float GetAbilityHaste() const { return ability_haste; }
	float GetMana() const { return mana; }
	float GetManaRegeneration() const { return mana_regeneration; }
	float GetMovementSpeed() const { return movement_speed; }
	float GetRange() const { return range; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float item_id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float armor_penteration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float attack_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float attack_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float critical_strike_chance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float cirtical_strike_damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float life_steal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float ability_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float mage_penetration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float omnivamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float physical_vamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float armor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float heal_and_shield_power;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float health_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float magic_resistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float tenacity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float slow_resist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float ability_haste;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float mana;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float mana_regeneration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
		float movement_speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status", meta = (AllowPrivateAccess = "true"))
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
	void SetStatusData(const FEquipmentItemData InEquipmentStatus) { mEquipmentStatus = InEquipmentStatus; }

public:
	FEquipmentItemData GetStatusData() const { return mEquipmentStatus; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FEquipmentItemData mEquipmentStatus;
};

UCLASS()
class PROJECT_LD_API ACharacterStatusData : public AActor
{
	GENERATED_BODY()
};
