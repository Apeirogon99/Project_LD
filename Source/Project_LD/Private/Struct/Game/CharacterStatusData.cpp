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

	returnData[0] = mBaseStatus.GetBaseArmorPenetration();
	returnData[1] = mBaseStatus.GetBaseAttackDamage();
	returnData[2] = mBaseStatus.GetBaseAttackSpeed();
	returnData[3] = mBaseStatus.GetBaseCriticalStrikeChance();
	returnData[4] = mBaseStatus.GetBaseCriticalStrikeDamage();
	returnData[5] = mBaseStatus.GetBaseLifeSteal();
	returnData[6] = mBaseStatus.GetBaseAbilityPower();
	returnData[7] = mBaseStatus.GetBaseMagePenetration();
	returnData[8] = mBaseStatus.GetBaseOmniVamp();
	returnData[9] = mBaseStatus.GetBasePhysicalVamp();
	returnData[10] = mBaseStatus.GetBaseArmor();
	returnData[11] = mBaseStatus.GetBaseHealAndShieldPower();
	returnData[12] = mBaseStatus.GetBaseHealth();
	returnData[13] = mBaseStatus.GetBaseHealthRegeneration();
	returnData[14] = mBaseStatus.GetBaseMagicResistance();
	returnData[15] = mBaseStatus.GetBaseTenacity();
	returnData[16] = mBaseStatus.GetBaseSlowResist();
	returnData[17] = mBaseStatus.GetBaseAbilityHaste();
	returnData[18] = mBaseStatus.GetBaseMana();
	returnData[19] = mBaseStatus.GetBaseManaRegeneration();
	returnData[20] = mBaseStatus.GetBaseMovementSpeed();
	returnData[21] = mBaseStatus.GetBaseRange();

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

	returnData[0] = mGrowStatus.GetGrowArmorPenetration();
	returnData[1] = mGrowStatus.GetGrowAttackDamage();
	returnData[2] = mGrowStatus.GetGrowAttackSpeed();
	returnData[3] = mGrowStatus.GetGrowCriticalStrikeChance();
	returnData[4] = mGrowStatus.GetGrowCriticalStrikeDamage();
	returnData[5] = mGrowStatus.GetGrowLifeSteal();
	returnData[6] = mGrowStatus.GetGrowAbilityPower();
	returnData[7] = mGrowStatus.GetGrowMagePenetration();
	returnData[8] = mGrowStatus.GetGrowOmniVamp();
	returnData[9] = mGrowStatus.GetGrowPhysicalVamp();
	returnData[10] = mGrowStatus.GetGrowArmor();
	returnData[11] = mGrowStatus.GetGrowHealAndShieldPower();
	returnData[12] = mGrowStatus.GetGrowHealth();
	returnData[13] = mGrowStatus.GetGrowHealthRegeneration();
	returnData[14] = mGrowStatus.GetGrowMagicResistance();
	returnData[15] = mGrowStatus.GetGrowTenacity();
	returnData[16] = mGrowStatus.GetGrowSlowResist();
	returnData[17] = mGrowStatus.GetGrowAbilityHaste();
	returnData[18] = mGrowStatus.GetGrowMana();
	returnData[19] = mGrowStatus.GetGrowManaRegeneration();
	returnData[20] = mGrowStatus.GetGrowMovementSpeed();
	returnData[21] = mGrowStatus.GetGrowRange();

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

	returnData[0] = mEquipmentStatus.GetArmorPenetration();
	returnData[1] = mEquipmentStatus.GetAttackDamage();
	returnData[2] = mEquipmentStatus.GetAttackSpeed();
	returnData[3] = mEquipmentStatus.GetCriticalStrikeChance();
	returnData[4] = mEquipmentStatus.GetCriticalStrikeDamage();
	returnData[5] = mEquipmentStatus.GetLifeSteal();
	returnData[6] = mEquipmentStatus.GetAbilityPower();
	returnData[7] = mEquipmentStatus.GetMagePenetration();
	returnData[8] = mEquipmentStatus.GetOmniVamp();
	returnData[9] = mEquipmentStatus.GetPhysicalVamp();
	returnData[10] = mEquipmentStatus.GetArmor();
	returnData[11] = mEquipmentStatus.GetHealAndShieldPower();
	returnData[12] = mEquipmentStatus.GetHealth();
	returnData[13] = mEquipmentStatus.GetHealthRegeneration();
	returnData[14] = mEquipmentStatus.GetMagicResistance();
	returnData[15] = mEquipmentStatus.GetTenacity();
	returnData[16] = mEquipmentStatus.GetSlowResist();
	returnData[17] = mEquipmentStatus.GetAbilityHaste();
	returnData[18] = mEquipmentStatus.GetMana();
	returnData[19] = mEquipmentStatus.GetManaRegeneration();
	returnData[20] = mEquipmentStatus.GetMovementSpeed();
	returnData[21] = mEquipmentStatus.GetRange();

	return returnData;
}
