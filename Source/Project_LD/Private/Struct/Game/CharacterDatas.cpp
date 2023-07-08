// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/Game/CharacterDatas.h"
#include <Protobuf/Handler/PacketUtils.h>
#include <Network/NetworkUtils.h>

FCharacterEquipment::FCharacterEquipment() : mHair(0), mHelmet(0), mShoulders(0), mChest(0),mBracers(0), mHands(0), mPants(0), mBoots(0), mWeapon_L(0), mWeapon_R(0)
{

}

void FCharacterEquipment::UpdateEquipments(const FCharacterEquipment& inCharacterEquipments)
{
	mHair			= inCharacterEquipments.mHair;
	mHelmet			= inCharacterEquipments.mHelmet;
	mShoulders		= inCharacterEquipments.mShoulders;
	mChest			= inCharacterEquipments.mChest;
	mBracers		= inCharacterEquipments.mBracers;
	mHands			= inCharacterEquipments.mHands;
	mPants			= inCharacterEquipments.mPants;
	mBoots			= inCharacterEquipments.mBoots;
	mWeapon_L		= inCharacterEquipments.mWeapon_L;
	mWeapon_R		= inCharacterEquipments.mWeapon_R;
}

void FCharacterEquipment::UpdateEquipments(const Protocol::SCharacterEqipment& inCharacterEquipments)
{
	mHair			= inCharacterEquipments.hair();
	mHelmet			= inCharacterEquipments.helmet();
	mShoulders		= inCharacterEquipments.shoulders();
	mChest			= inCharacterEquipments.chest();
	mBracers		= inCharacterEquipments.bracers();
	mHands			= inCharacterEquipments.hands();
	mPants			= inCharacterEquipments.pants();
	mBoots			= inCharacterEquipments.boots();
	mWeapon_L		= inCharacterEquipments.weapon_l();
	mWeapon_R		= inCharacterEquipments.weapon_r();
}

void FCharacterEquipment::CompareEquipments(const FCharacterEquipment& inOtherEquipments)
{
	mHair			= (inOtherEquipments.mHair == 0) ?		mHair		: inOtherEquipments.mHair;
	mHelmet			= (inOtherEquipments.mHelmet == 0) ?	mHelmet		: inOtherEquipments.mHelmet;
	mShoulders		= (inOtherEquipments.mShoulders == 0) ? mShoulders	: inOtherEquipments.mShoulders;
	mChest			= (inOtherEquipments.mChest == 0) ?		mChest		: inOtherEquipments.mChest;
	mBracers		= (inOtherEquipments.mBracers == 0) ?	mBracers	: inOtherEquipments.mBracers;
	mHands			= (inOtherEquipments.mHands == 0) ?		mHands		: inOtherEquipments.mHands;
	mPants			= (inOtherEquipments.mPants == 0) ?		mPants		: inOtherEquipments.mPants;
	mBoots			= (inOtherEquipments.mBoots == 0) ?		mBoots		: inOtherEquipments.mBoots;
	mWeapon_L		= (inOtherEquipments.mWeapon_L == 0) ?	mWeapon_L	: inOtherEquipments.mWeapon_L;
	mWeapon_R		= (inOtherEquipments.mWeapon_R == 0) ?	mWeapon_R	: inOtherEquipments.mWeapon_R;
}

TArray<float> FCharacterEquipment::GetAllItemIndex()
{
	TArray<float> ItemArr;

	ItemArr.SetNum(9);
	ItemArr[0] = mHelmet;
	ItemArr[1] = mShoulders;
	ItemArr[2] = mChest;
	ItemArr[3] = mBracers;
	ItemArr[4] = mHands;
	ItemArr[5] = mPants;
	ItemArr[6] = mBoots;
	ItemArr[7] = mWeapon_L;
	ItemArr[8] = mWeapon_R;

	return ItemArr;
}

FCharacterAppearance::FCharacterAppearance() : mRace(ECharacterRace::None), mSeat(0), mSkin_Color(0), mHair_Color(0), mEye_Color(0), mEyebrow_Color(0)
{
}

void FCharacterAppearance::UpdateAppearance(const FCharacterAppearance& inCharacterAppearance)
{
	mRace					= inCharacterAppearance.mRace;
	mSeat					= inCharacterAppearance.mSeat;
	mSkin_Color		= inCharacterAppearance.mSkin_Color;
	mHair_Color		= inCharacterAppearance.mHair_Color;
	mEye_Color			= inCharacterAppearance.mEye_Color;
	mEyebrow_Color	= inCharacterAppearance.mEyebrow_Color;
}

void FCharacterAppearance::UpdateAppearance(const Protocol::SCharacterAppearance& inCharacterAppearance)
{
	mRace			= UPacketUtils::ConvertToURace(inCharacterAppearance.race());
	mSeat			= inCharacterAppearance.seat();
	mSkin_Color		= inCharacterAppearance.skin_color();
	mHair_Color		= inCharacterAppearance.hair_color();
	mEye_Color		= inCharacterAppearance.eye_color();
	mEyebrow_Color	= inCharacterAppearance.eyebrow_color();
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

	returnData[0]		= mMaxStats.GetArmorPenetration();
	returnData[1]		= mMaxStats.GetAttackDamage();
	returnData[2]		= mMaxStats.GetAttackSpeed();
	returnData[3]		= mMaxStats.GetCriticalStrikeChance();
	returnData[4]		= mMaxStats.GetCriticalStrikeDamage();
	returnData[5]		= mMaxStats.GetLifeSteal();
	returnData[6]		= mMaxStats.GetAbilityPower();
	returnData[7]		= mMaxStats.GetMagePenetration();
	returnData[8]		= mMaxStats.GetOmniVamp();
	returnData[9]		= mMaxStats.GetPhysicalVamp();
	returnData[10]	= mMaxStats.GetArmor();
	returnData[11]	= mMaxStats.GetHealAndShieldPower();
	returnData[12]	= mMaxStats.GetHealth();
	returnData[13]	= mMaxStats.GetHealthRegeneration();
	returnData[14]	= mMaxStats.GetMagicResistance();
	returnData[15]	= mMaxStats.GetTenacity();
	returnData[16]	= mMaxStats.GetSlowResist();
	returnData[17]	= mMaxStats.GetAbilityHaste();
	returnData[18]	= mMaxStats.GetMana();
	returnData[19]	= mMaxStats.GetManaRegeneration();
	returnData[20]	= mMaxStats.GetMovementSpeed();
	returnData[21]	= mMaxStats.GetRange();

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


FCharacterData::FCharacterData() : mName(TEXT("")), mLevel(0), mClass(ECharacterClass::None), mAppearance(), mEquipment()
{
}

void FCharacterData::UpdateCharacterData(const FCharacterData& inCharacterData)
{
	mName					= inCharacterData.mName;
	mLevel					= inCharacterData.mLevel;
	mClass						= inCharacterData.mClass;

	mAppearance			= inCharacterData.mAppearance;
	mEquipment			= inCharacterData.mEquipment;
}

void FCharacterData::UpdateCharacterData(const Protocol::SCharacterData& inCharacterData)
{
	mName			= UNetworkUtils::ConvertFString(inCharacterData.name());
	mLevel			= inCharacterData.level();
	mClass				= StaticCast<ECharacterClass>(inCharacterData.character_class());

	const Protocol::SCharacterAppearance& appearance = inCharacterData.appearance();
	mAppearance.UpdateAppearance(appearance);

	const Protocol::SCharacterEqipment& eqipment = inCharacterData.eqipment();
	mEquipment.UpdateEquipments(eqipment);
}
