// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/Game/CharacterStatusData.h"

FCharacterBaseStatus::FCharacterBaseStatus() :mBaseStatus(FStatusBaseData())
{
}

void FCharacterBaseStatus::UpdateCharacterBaseStatus(const FCharacterBaseStatus& inCharacterStatus)
{
	mBaseStatus = inCharacterStatus.mBaseStatus;
}

TArray<float> FCharacterBaseStatus::FDataToFloat()
{
	TArray<float> returnData;
	returnData.SetNum(22);

	returnData[0] = mBaseStatus.base_armor_penetration;
	returnData[1] = mBaseStatus.base_attack_damage;
	returnData[2] = mBaseStatus.base_attack_speed;
	returnData[3] = mBaseStatus.base_critical_strike_chance;
	returnData[4] = mBaseStatus.base_cirtical_strike_damage;
	returnData[5] = mBaseStatus.base_life_steal;
	returnData[6] = mBaseStatus.base_ability_power;
	returnData[7] = mBaseStatus.base_mage_penetration;
	returnData[8] = mBaseStatus.base_omnivamp;
	returnData[9] = mBaseStatus.base_physical_vamp;
	returnData[10] = mBaseStatus.base_armor;
	returnData[11] = mBaseStatus.base_heal_and_shield_power;
	returnData[12] = mBaseStatus.base_health;
	returnData[13] = mBaseStatus.base_health_regeneration;
	returnData[14] = mBaseStatus.base_magic_resistance;
	returnData[15] = mBaseStatus.base_tenacity;
	returnData[16] = mBaseStatus.base_slow_resist;
	returnData[17] = mBaseStatus.base_ability_haste;
	returnData[18] = mBaseStatus.base_mana;
	returnData[19] = mBaseStatus.base_mana_regeneration;
	returnData[20] = mBaseStatus.base_movement_speed;
	returnData[21] = mBaseStatus.base_range;

	return returnData;
}

FCharacterGrowStatus::FCharacterGrowStatus() : mGrowStatus(FStatusGrowthData())
{
}

void FCharacterGrowStatus::UpdateCharacterGrowStatus(const FCharacterGrowStatus& inCharacterStatus)
{
	mGrowStatus = inCharacterStatus.mGrowStatus;
}

TArray<float> FCharacterGrowStatus::FDataToFloat()
{
	TArray<float> returnData;
	returnData.SetNum(22);

	returnData[0] = mGrowStatus.grow_armor_penetration;
	returnData[1] = mGrowStatus.grow_attack_damage;
	returnData[2] = mGrowStatus.grow_attack_speed;
	returnData[3] = mGrowStatus.grow_critical_strike_chance;
	returnData[4] = mGrowStatus.grow_cirtical_strike_damage;
	returnData[5] = mGrowStatus.grow_life_steal;
	returnData[6] = mGrowStatus.grow_ability_power;
	returnData[7] = mGrowStatus.grow_mage_penetration;
	returnData[8] = mGrowStatus.grow_omnivamp;
	returnData[9] = mGrowStatus.grow_physical_vamp;
	returnData[10] = mGrowStatus.grow_armor;
	returnData[11] = mGrowStatus.grow_heal_and_shield_power;
	returnData[12] = mGrowStatus.grow_health;
	returnData[13] = mGrowStatus.grow_health_regeneration;
	returnData[14] = mGrowStatus.grow_magic_resistance;
	returnData[15] = mGrowStatus.grow_tenacity;
	returnData[16] = mGrowStatus.grow_slow_resist;
	returnData[17] = mGrowStatus.grow_ability_haste;
	returnData[18] = mGrowStatus.grow_mana;
	returnData[19] = mGrowStatus.grow_mana_regeneration;
	returnData[20] = mGrowStatus.grow_movement_speed;
	returnData[21] = mGrowStatus.grow_range;

	return returnData;
}

FCharacterEquipmentStatus::FCharacterEquipmentStatus() : mEquipmentStatus(FEquipmentItemData())
{
}

void FCharacterEquipmentStatus::UpdateEquipmentStatus(const FCharacterEquipmentStatus& inCharacterStatus)
{
	mEquipmentStatus = inCharacterStatus.mEquipmentStatus;
}

TArray<float> FCharacterEquipmentStatus::FDataToFloat()
{
	TArray<float> returnData;
	returnData.SetNum(22);

	returnData[0] = mEquipmentStatus.armor_penteration;
	returnData[1] = mEquipmentStatus.attack_damage;
	returnData[2] = mEquipmentStatus.attack_speed;
	returnData[3] = mEquipmentStatus.critical_strike_chance;
	returnData[4] = mEquipmentStatus.cirtical_strike_damage;
	returnData[5] = mEquipmentStatus.life_steal;
	returnData[6] = mEquipmentStatus.ability_power;
	returnData[7] = mEquipmentStatus.mage_penetration;
	returnData[8] = mEquipmentStatus.omnivamp;
	returnData[9] = mEquipmentStatus.physical_vamp;
	returnData[10] = mEquipmentStatus.armor;
	returnData[11] = mEquipmentStatus.heal_and_shield_power;
	returnData[12] = mEquipmentStatus.health;
	returnData[13] = mEquipmentStatus.health_regeneration;
	returnData[14] = mEquipmentStatus.magic_resistance;
	returnData[15] = mEquipmentStatus.tenacity;
	returnData[16] = mEquipmentStatus.slow_resist;
	returnData[17] = mEquipmentStatus.ability_haste;
	returnData[18] = mEquipmentStatus.mana;
	returnData[19] = mEquipmentStatus.mana_regeneration;
	returnData[20] = mEquipmentStatus.movement_speed;
	returnData[21] = mEquipmentStatus.range;

	return returnData;
}
