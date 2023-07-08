// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/Game/CharacterStatusData.h"

FCharacterBaseStats::FCharacterBaseStats() :mBaseStats(FStatsBaseData())
{
}

void FCharacterBaseStats::UpdateCharacterBaseStats(const FCharacterBaseStats& inCharacterStats)
{
	mBaseStats = inCharacterStats.mBaseStats;
}

TArray<float> FCharacterBaseStats::FDataToFloat()
{
	TArray<float> returnData;
	returnData.SetNum(22);

	returnData[0] = mBaseStats.base_armor_penetration;
	returnData[1] = mBaseStats.base_attack_damage;
	returnData[2] = mBaseStats.base_attack_speed;
	returnData[3] = mBaseStats.base_critical_strike_chance;
	returnData[4] = mBaseStats.base_cirtical_strike_damage;
	returnData[5] = mBaseStats.base_life_steal;
	returnData[6] = mBaseStats.base_ability_power;
	returnData[7] = mBaseStats.base_mage_penetration;
	returnData[8] = mBaseStats.base_omnivamp;
	returnData[9] = mBaseStats.base_physical_vamp;
	returnData[10] = mBaseStats.base_armor;
	returnData[11] = mBaseStats.base_heal_and_shield_power;
	returnData[12] = mBaseStats.base_health;
	returnData[13] = mBaseStats.base_health_regeneration;
	returnData[14] = mBaseStats.base_magic_resistance;
	returnData[15] = mBaseStats.base_tenacity;
	returnData[16] = mBaseStats.base_slow_resist;
	returnData[17] = mBaseStats.base_ability_haste;
	returnData[18] = mBaseStats.base_mana;
	returnData[19] = mBaseStats.base_mana_regeneration;
	returnData[20] = mBaseStats.base_movement_speed;
	returnData[21] = mBaseStats.base_range;

	return returnData;
}

FCharacterGrowStats::FCharacterGrowStats() : mGrowStats(FStatsGrowthData())
{
}

void FCharacterGrowStats::UpdateCharacterGrowStats(const FCharacterGrowStats& inCharacterStats)
{
	mGrowStats = inCharacterStats.mGrowStats;
}

TArray<float> FCharacterGrowStats::FDataToFloat()
{
	TArray<float> returnData;
	returnData.SetNum(22);

	returnData[0] = mGrowStats.grow_armor_penetration;
	returnData[1] = mGrowStats.grow_attack_damage;
	returnData[2] = mGrowStats.grow_attack_speed;
	returnData[3] = mGrowStats.grow_critical_strike_chance;
	returnData[4] = mGrowStats.grow_cirtical_strike_damage;
	returnData[5] = mGrowStats.grow_life_steal;
	returnData[6] = mGrowStats.grow_ability_power;
	returnData[7] = mGrowStats.grow_mage_penetration;
	returnData[8] = mGrowStats.grow_omnivamp;
	returnData[9] = mGrowStats.grow_physical_vamp;
	returnData[10] = mGrowStats.grow_armor;
	returnData[11] = mGrowStats.grow_heal_and_shield_power;
	returnData[12] = mGrowStats.grow_health;
	returnData[13] = mGrowStats.grow_health_regeneration;
	returnData[14] = mGrowStats.grow_magic_resistance;
	returnData[15] = mGrowStats.grow_tenacity;
	returnData[16] = mGrowStats.grow_slow_resist;
	returnData[17] = mGrowStats.grow_ability_haste;
	returnData[18] = mGrowStats.grow_mana;
	returnData[19] = mGrowStats.grow_mana_regeneration;
	returnData[20] = mGrowStats.grow_movement_speed;
	returnData[21] = mGrowStats.grow_range;

	return returnData;
}

FCharacterEquipmentStats::FCharacterEquipmentStats() : mEquipmentStats(FEquipmentItemData())
{
}

void FCharacterEquipmentStats::UpdateEquipmentStats(const FCharacterEquipmentStats& inCharacterStats)
{
	mEquipmentStats = inCharacterStats.mEquipmentStats;
}

TArray<float> FCharacterEquipmentStats::FDataToFloat()
{
	TArray<float> returnData;
	returnData.SetNum(22);

	returnData[0] = mEquipmentStats.armor_penteration;
	returnData[1] = mEquipmentStats.attack_damage;
	returnData[2] = mEquipmentStats.attack_speed;
	returnData[3] = mEquipmentStats.critical_strike_chance;
	returnData[4] = mEquipmentStats.cirtical_strike_damage;
	returnData[5] = mEquipmentStats.life_steal;
	returnData[6] = mEquipmentStats.ability_power;
	returnData[7] = mEquipmentStats.mage_penetration;
	returnData[8] = mEquipmentStats.omnivamp;
	returnData[9] = mEquipmentStats.physical_vamp;
	returnData[10] = mEquipmentStats.armor;
	returnData[11] = mEquipmentStats.heal_and_shield_power;
	returnData[12] = mEquipmentStats.health;
	returnData[13] = mEquipmentStats.health_regeneration;
	returnData[14] = mEquipmentStats.magic_resistance;
	returnData[15] = mEquipmentStats.tenacity;
	returnData[16] = mEquipmentStats.slow_resist;
	returnData[17] = mEquipmentStats.ability_haste;
	returnData[18] = mEquipmentStats.mana;
	returnData[19] = mEquipmentStats.mana_regeneration;
	returnData[20] = mEquipmentStats.movement_speed;
	returnData[21] = mEquipmentStats.range;

	return returnData;
}
