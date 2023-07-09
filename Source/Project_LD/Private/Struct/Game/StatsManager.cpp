// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/Game/StatsManager.h"

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

TArray<float> FCharacterStats::FDataToFloat()
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

void FCharacterStats::FloatToFData(TArray<float> Data)
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

void FCharacterStats::UpdateStats(ECharacterStatus InStats, float Invalue)
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