// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/Game/EnemyData.h"

FEnemyBaseStats::FEnemyBaseStats() : mBaseStats(FEnemyStatData())
{
}

void FEnemyBaseStats::UpdateEnemyStats(const FEnemyBaseStats& inCharacterStats)
{
	mBaseStats = inCharacterStats.mBaseStats;
}

TArray<float> FEnemyBaseStats::FDataToFloat()
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
