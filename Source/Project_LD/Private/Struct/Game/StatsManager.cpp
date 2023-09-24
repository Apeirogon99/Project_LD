// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/Game/StatsManager.h"
#include <CharacterStatusData.h>

// Sets default values
AStatsManager::AStatsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

FCharacterStats::FCharacterStats()
{
}

void FCharacterStats::UpdateCharacterStats(const FCharacterStats& inCharacterStats)
{
	mMaxStats = inCharacterStats.mMaxStats;
	mCurrentStats = inCharacterStats.mCurrentStats;
}

TArray<float> FCharacterStats::MaxFDataToFloat()
{
	TArray<float> returnData;
	returnData.SetNum(22);

	returnData[0] = mMaxStats.GetArmorPenetration();
	returnData[1] = mMaxStats.GetAttackDamage();
	returnData[2] = mMaxStats.GetAttackSpeed();
	returnData[3] = mMaxStats.GetCriticalStrikeChance();
	returnData[4] = mMaxStats.GetCriticalStrikeDamage();
	returnData[5] = mMaxStats.GetLifeSteal();
	returnData[6] = mMaxStats.GetAbilityPower();
	returnData[7] = mMaxStats.GetMagePenetration();
	returnData[8] = mMaxStats.GetOmniVamp();
	returnData[9] = mMaxStats.GetPhysicalVamp();
	returnData[10] = mMaxStats.GetArmor();
	returnData[11] = mMaxStats.GetHealAndShieldPower();
	returnData[12] = mMaxStats.GetHealth();
	returnData[13] = mMaxStats.GetHealthRegeneration();
	returnData[14] = mMaxStats.GetMagicResistance();
	returnData[15] = mMaxStats.GetTenacity();
	returnData[16] = mMaxStats.GetSlowResist();
	returnData[17] = mMaxStats.GetAbilityHaste();
	returnData[18] = mMaxStats.GetMana();
	returnData[19] = mMaxStats.GetManaRegeneration();
	returnData[20] = mMaxStats.GetMovementSpeed();
	returnData[21] = mMaxStats.GetRange();

	return returnData;
}

TArray<float> FCharacterStats::CurrentFDataToFloat()
{
	TArray<float> returnData;
	returnData.SetNum(22);

	returnData[0] = mCurrentStats.GetArmorPenetration();
	returnData[1] = mCurrentStats.GetAttackDamage();
	returnData[2] = mCurrentStats.GetAttackSpeed();
	returnData[3] = mCurrentStats.GetCriticalStrikeChance();
	returnData[4] = mCurrentStats.GetCriticalStrikeDamage();
	returnData[5] = mCurrentStats.GetLifeSteal();
	returnData[6] = mCurrentStats.GetAbilityPower();
	returnData[7] = mCurrentStats.GetMagePenetration();
	returnData[8] = mCurrentStats.GetOmniVamp();
	returnData[9] = mCurrentStats.GetPhysicalVamp();
	returnData[10] = mCurrentStats.GetArmor();
	returnData[11] = mCurrentStats.GetHealAndShieldPower();
	returnData[12] = mCurrentStats.GetHealth();
	returnData[13] = mCurrentStats.GetHealthRegeneration();
	returnData[14] = mCurrentStats.GetMagicResistance();
	returnData[15] = mCurrentStats.GetTenacity();
	returnData[16] = mCurrentStats.GetSlowResist();
	returnData[17] = mCurrentStats.GetAbilityHaste();
	returnData[18] = mCurrentStats.GetMana();
	returnData[19] = mCurrentStats.GetManaRegeneration();
	returnData[20] = mCurrentStats.GetMovementSpeed();
	returnData[21] = mCurrentStats.GetRange();

	return returnData;
}

void FCharacterStats::MaxFloatToFData(TArray<float> Data)
{
	mMaxStats.SetArmorPenetration(Data[0]);
	mMaxStats.SetAttackDamage(Data[1]);
	mMaxStats.SetAttackSpeed(Data[2]);
	mMaxStats.SetCriticalStrikeChance(Data[3]);
	mMaxStats.SetCriticalStrikeDamage(Data[4]);
	mMaxStats.SetLifeSteal(Data[5]);
	mMaxStats.SetAbilityPower(Data[6]);
	mMaxStats.SetMagePenetration(Data[7]);
	mMaxStats.SetOmniVamp(Data[8]);
	mMaxStats.SetPhysicalVamp(Data[9]);
	mMaxStats.SetArmor(Data[10]);
	mMaxStats.SetHealAndShieldPower(Data[11]);
	mMaxStats.SetHealth(Data[12]);
	mMaxStats.SetHealthRegeneration(Data[13]);
	mMaxStats.SetMagicResistance(Data[14]);
	mMaxStats.SetTenacity(Data[15]);
	mMaxStats.SetSlowResist(Data[16]);
	mMaxStats.SetAbilityHaste(Data[17]);
	mMaxStats.SetMana(Data[18]);
	mMaxStats.SetManaRegeneration(Data[19]);
	mMaxStats.SetMovementSpeed(Data[20]);
	mMaxStats.SetRange(Data[21]);
}

void FCharacterStats::CurrentFloatToFData(TArray<float> Data)
{
	mCurrentStats.SetArmorPenetration(Data[0]);
	mCurrentStats.SetAttackDamage(Data[1]);
	mCurrentStats.SetAttackSpeed(Data[2]);
	mCurrentStats.SetCriticalStrikeChance(Data[3]);
	mCurrentStats.SetCriticalStrikeDamage(Data[4]);
	mCurrentStats.SetLifeSteal(Data[5]);
	mCurrentStats.SetAbilityPower(Data[6]);
	mCurrentStats.SetMagePenetration(Data[7]);
	mCurrentStats.SetOmniVamp(Data[8]);
	mCurrentStats.SetPhysicalVamp(Data[9]);
	mCurrentStats.SetArmor(Data[10]);
	mCurrentStats.SetHealAndShieldPower(Data[11]);
	mCurrentStats.SetHealth(Data[12]);
	mCurrentStats.SetHealthRegeneration(Data[13]);
	mCurrentStats.SetMagicResistance(Data[14]);
	mCurrentStats.SetTenacity(Data[15]);
	mCurrentStats.SetSlowResist(Data[16]);
	mCurrentStats.SetAbilityHaste(Data[17]);
	mCurrentStats.SetMana(Data[18]);
	mCurrentStats.SetManaRegeneration(Data[19]);
	mCurrentStats.SetMovementSpeed(Data[20]);
	mCurrentStats.SetRange(Data[21]);
}

void FCharacterStats::UpdateMaxStats(ECharacterStatus InStats, float Invalue)
{
	switch (InStats)
	{
	case ECharacterStatus::None:
		break;
	case ECharacterStatus::ArmorPenetration:
		mMaxStats.SetArmorPenetration(Invalue);
		break;
	case ECharacterStatus::AttackDamage:
		mMaxStats.SetAttackDamage(Invalue);
		break;
	case ECharacterStatus::AttackSpeed:
		mMaxStats.SetAttackSpeed(Invalue);
		break;
	case ECharacterStatus::CriticalStrikeChance:
		mMaxStats.SetCriticalStrikeChance(Invalue);
		break;
	case ECharacterStatus::CriticalStrikeDamage:
		mMaxStats.SetCriticalStrikeDamage(Invalue);
		break;
	case ECharacterStatus::LifeSteal:
		mMaxStats.SetLifeSteal(Invalue);
		break;
	case ECharacterStatus::AbilityPower:
		mMaxStats.SetAbilityPower(Invalue);
		break;
	case ECharacterStatus::MagePenetration:
		mMaxStats.SetMagePenetration(Invalue);
		break;
	case ECharacterStatus::Omnivamp:
		mMaxStats.SetOmniVamp(Invalue);
		break;
	case ECharacterStatus::PhysicalVamp:
		mMaxStats.SetPhysicalVamp(Invalue);
		break;
	case ECharacterStatus::Armor:
		mMaxStats.SetArmor(Invalue);
		break;
	case ECharacterStatus::HealAndShieldPower:
		mMaxStats.SetHealAndShieldPower(Invalue);
		break;
	case ECharacterStatus::Health:
		mMaxStats.SetHealth(Invalue);
		break;
	case ECharacterStatus::HealthRegeneration:
		mMaxStats.SetHealthRegeneration(Invalue);
		break;
	case ECharacterStatus::MagicResistance:
		mMaxStats.SetMagicResistance(Invalue);
		break;
	case ECharacterStatus::Tenacity:
		mMaxStats.SetTenacity(Invalue);
		break;
	case ECharacterStatus::SlowResist:
		mMaxStats.SetSlowResist(Invalue);
		break;
	case ECharacterStatus::AbilityHaste:
		mMaxStats.SetAbilityHaste(Invalue);
		break;
	case ECharacterStatus::Mana:
		mMaxStats.SetMana(Invalue);
		break;
	case ECharacterStatus::ManaRegeneration:
		mMaxStats.SetManaRegeneration(Invalue);
		break;
	case ECharacterStatus::MovementSpeed:
		mMaxStats.SetMovementSpeed(Invalue);
		break;
	case ECharacterStatus::Range:
		mMaxStats.SetRange(Invalue);
		break;
	default:
		break;
	}
}

void FCharacterStats::UpdateCurrentStats(ECharacterStatus InStats, float Invalue)
{
	switch (InStats)
	{
	case ECharacterStatus::None:
		break;
	case ECharacterStatus::ArmorPenetration:
		mCurrentStats.SetArmorPenetration(Invalue);
		break;
	case ECharacterStatus::AttackDamage:
		mCurrentStats.SetAttackDamage(Invalue);
		break;
	case ECharacterStatus::AttackSpeed:
		mCurrentStats.SetAttackSpeed(Invalue);
		break;
	case ECharacterStatus::CriticalStrikeChance:
		mCurrentStats.SetCriticalStrikeChance(Invalue);
		break;
	case ECharacterStatus::CriticalStrikeDamage:
		mCurrentStats.SetCriticalStrikeDamage(Invalue);
		break;
	case ECharacterStatus::LifeSteal:
		mCurrentStats.SetLifeSteal(Invalue);
		break;
	case ECharacterStatus::AbilityPower:
		mCurrentStats.SetAbilityPower(Invalue);
		break;
	case ECharacterStatus::MagePenetration:
		mCurrentStats.SetMagePenetration(Invalue);
		break;
	case ECharacterStatus::Omnivamp:
		mCurrentStats.SetOmniVamp(Invalue);
		break;
	case ECharacterStatus::PhysicalVamp:
		mCurrentStats.SetPhysicalVamp(Invalue);
		break;
	case ECharacterStatus::Armor:
		mCurrentStats.SetArmor(Invalue);
		break;
	case ECharacterStatus::HealAndShieldPower:
		mCurrentStats.SetHealAndShieldPower(Invalue);
		break;
	case ECharacterStatus::Health:
		mCurrentStats.SetHealth(Invalue);
		break;
	case ECharacterStatus::HealthRegeneration:
		mCurrentStats.SetHealthRegeneration(Invalue);
		break;
	case ECharacterStatus::MagicResistance:
		mCurrentStats.SetMagicResistance(Invalue);
		break;
	case ECharacterStatus::Tenacity:
		mCurrentStats.SetTenacity(Invalue);
		break;
	case ECharacterStatus::SlowResist:
		mCurrentStats.SetSlowResist(Invalue);
		break;
	case ECharacterStatus::AbilityHaste:
		mCurrentStats.SetAbilityHaste(Invalue);
		break;
	case ECharacterStatus::Mana:
		mCurrentStats.SetMana(Invalue);
		break;
	case ECharacterStatus::ManaRegeneration:
		mCurrentStats.SetManaRegeneration(Invalue);
		break;
	case ECharacterStatus::MovementSpeed:
		mCurrentStats.SetMovementSpeed(Invalue);
		break;
	case ECharacterStatus::Range:
		mCurrentStats.SetRange(Invalue);
		break;
	default:
		break;
	}
}

void FCharacterStats::PutOnEquipment(FEquipmentItemData InData)
{
	mCurrentStats.SetArmorPenetration(mCurrentStats.GetArmorPenetration() + InData.armor_penteration);
	mCurrentStats.SetAttackDamage(mCurrentStats.GetAttackDamage() + InData.attack_damage);
	mCurrentStats.SetAttackSpeed(mCurrentStats.GetAttackSpeed() + InData.attack_speed);
	mCurrentStats.SetCriticalStrikeChance(mCurrentStats.GetCriticalStrikeChance() + InData.critical_strike_chance);
	mCurrentStats.SetCriticalStrikeDamage(mCurrentStats.GetCriticalStrikeDamage() + InData.cirtical_strike_damage);
	mCurrentStats.SetLifeSteal(mCurrentStats.GetLifeSteal() + InData.life_steal);
	mCurrentStats.SetAbilityPower(mCurrentStats.GetAbilityPower() + InData.ability_power);
	mCurrentStats.SetMagePenetration(mCurrentStats.GetMagePenetration() + InData.mage_penetration);
	mCurrentStats.SetOmniVamp(mCurrentStats.GetOmniVamp() + InData.omnivamp);
	mCurrentStats.SetPhysicalVamp(mCurrentStats.GetPhysicalVamp() + InData.physical_vamp);
	mCurrentStats.SetArmor(mCurrentStats.GetArmor() + InData.armor);
	mCurrentStats.SetHealAndShieldPower(mCurrentStats.GetHealAndShieldPower() + InData.heal_and_shield_power);
	mCurrentStats.SetHealth(mCurrentStats.GetHealth() + InData.health);
	mCurrentStats.SetHealthRegeneration(mCurrentStats.GetHealthRegeneration() + InData.health_regeneration);
	mCurrentStats.SetMagicResistance(mCurrentStats.GetMagicResistance() + InData.magic_resistance);
	mCurrentStats.SetTenacity(mCurrentStats.GetTenacity() + InData.tenacity);
	mCurrentStats.SetSlowResist(mCurrentStats.GetSlowResist() + InData.slow_resist);
	mCurrentStats.SetAbilityHaste(mCurrentStats.GetAbilityHaste() + InData.ability_haste);
	mCurrentStats.SetMana(mCurrentStats.GetMana() + InData.mana);
	mCurrentStats.SetManaRegeneration(mCurrentStats.GetManaRegeneration() + InData.mana_regeneration);
	mCurrentStats.SetMovementSpeed(mCurrentStats.GetMovementSpeed() + InData.movement_speed);
	mCurrentStats.SetRange(mCurrentStats.GetRange() + InData.range);
}

void FCharacterStats::TakeOffEquipment(FEquipmentItemData InData)
{
	mCurrentStats.SetArmorPenetration(mCurrentStats.GetArmorPenetration() - InData.armor_penteration);
	mCurrentStats.SetAttackDamage(mCurrentStats.GetAttackDamage() - InData.attack_damage);
	mCurrentStats.SetAttackSpeed(mCurrentStats.GetAttackSpeed() - InData.attack_speed);
	mCurrentStats.SetCriticalStrikeChance(mCurrentStats.GetCriticalStrikeChance() - InData.critical_strike_chance);
	mCurrentStats.SetCriticalStrikeDamage(mCurrentStats.GetCriticalStrikeDamage() - InData.cirtical_strike_damage);
	mCurrentStats.SetLifeSteal(mCurrentStats.GetLifeSteal() - InData.life_steal);
	mCurrentStats.SetAbilityPower(mCurrentStats.GetAbilityPower() - InData.ability_power);
	mCurrentStats.SetMagePenetration(mCurrentStats.GetMagePenetration() - InData.mage_penetration);
	mCurrentStats.SetOmniVamp(mCurrentStats.GetOmniVamp() - InData.omnivamp);
	mCurrentStats.SetPhysicalVamp(mCurrentStats.GetPhysicalVamp() - InData.physical_vamp);
	mCurrentStats.SetArmor(mCurrentStats.GetArmor() - InData.armor);
	mCurrentStats.SetHealAndShieldPower(mCurrentStats.GetHealAndShieldPower() - InData.heal_and_shield_power);
	mCurrentStats.SetHealth(mCurrentStats.GetHealth() - InData.health);
	mCurrentStats.SetHealthRegeneration(mCurrentStats.GetHealthRegeneration() - InData.health_regeneration);
	mCurrentStats.SetMagicResistance(mCurrentStats.GetMagicResistance() - InData.magic_resistance);
	mCurrentStats.SetTenacity(mCurrentStats.GetTenacity() - InData.tenacity);
	mCurrentStats.SetSlowResist(mCurrentStats.GetSlowResist() - InData.slow_resist);
	mCurrentStats.SetAbilityHaste(mCurrentStats.GetAbilityHaste() - InData.ability_haste);
	mCurrentStats.SetMana(mCurrentStats.GetMana() - InData.mana);
	mCurrentStats.SetManaRegeneration(mCurrentStats.GetManaRegeneration() - InData.mana_regeneration);
	mCurrentStats.SetMovementSpeed(mCurrentStats.GetMovementSpeed() - InData.movement_speed);
	mCurrentStats.SetRange(mCurrentStats.GetRange() - InData.range);
}
