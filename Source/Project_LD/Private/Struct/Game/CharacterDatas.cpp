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

void FCharacterStats::UpdateCharacterStatus(const FCharacterStats& inCharacterStatus)
{
	mMaxStatus = inCharacterStatus.mMaxStatus;
	mCurrentStatus = inCharacterStatus.mCurrentStatus;
}

TArray<float> FCharacterStats::FDataToFloat()
{
	TArray<float> returnData;
	returnData.SetNum(22);

	returnData[0]		= mMaxStatus.GetArmorPenetration();
	returnData[1]		= mMaxStatus.GetAttackDamage();
	returnData[2]		= mMaxStatus.GetAttackSpeed();
	returnData[3]		= mMaxStatus.GetCriticalStrikeChance();
	returnData[4]		= mMaxStatus.GetCriticalStrikeDamage();
	returnData[5]		= mMaxStatus.GetLifeSteal();
	returnData[6]		= mMaxStatus.GetAbilityPower();
	returnData[7]		= mMaxStatus.GetMagePenetration();
	returnData[8]		= mMaxStatus.GetOmniVamp();
	returnData[9]		= mMaxStatus.GetPhysicalVamp();
	returnData[10]	= mMaxStatus.GetArmor();
	returnData[11]	= mMaxStatus.GetHealAndShieldPower();
	returnData[12]	= mMaxStatus.GetHealth();
	returnData[13]	= mMaxStatus.GetHealthRegeneration();
	returnData[14]	= mMaxStatus.GetMagicResistance();
	returnData[15]	= mMaxStatus.GetTenacity();
	returnData[16]	= mMaxStatus.GetSlowResist();
	returnData[17]	= mMaxStatus.GetAbilityHaste();
	returnData[18]	= mMaxStatus.GetMana();
	returnData[19]	= mMaxStatus.GetManaRegeneration();
	returnData[20]	= mMaxStatus.GetMovementSpeed();
	returnData[21]	= mMaxStatus.GetRange();

	return returnData;
}

void FCharacterStats::FloatToFData(TArray<float> Data)
{
	mMaxStatus.SetArmorPenetration(Data[0]);
	mMaxStatus.SetAttackDamage(Data[1]);
	mMaxStatus.SetAttackSpeed(Data[2]);
	mMaxStatus.SetCriticalStrikeChance(Data[3]);
	mMaxStatus.SetCriticalStrikeDamage(Data[4]);
	mMaxStatus.SetLifeSteal(Data[5]);
	mMaxStatus.SetAbilityPower(Data[6]);
	mMaxStatus.SetMagePenetration(Data[7]);
	mMaxStatus.SetOmniVamp(Data[8]);
	mMaxStatus.SetPhysicalVamp(Data[9]);
	mMaxStatus.SetArmor(Data[10]);
	mMaxStatus.SetHealAndShieldPower(Data[11]);
	mMaxStatus.SetHealth(Data[12]);
	mMaxStatus.SetHealthRegeneration(Data[13]);
	mMaxStatus.SetMagicResistance(Data[14]);
	mMaxStatus.SetTenacity(Data[15]);
	mMaxStatus.SetSlowResist(Data[16]);
	mMaxStatus.SetAbilityHaste(Data[17]);
	mMaxStatus.SetMana(Data[18]);
	mMaxStatus.SetManaRegeneration(Data[19]);
	mMaxStatus.SetMovementSpeed(Data[20]);
	mMaxStatus.SetRange(Data[21]);
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
