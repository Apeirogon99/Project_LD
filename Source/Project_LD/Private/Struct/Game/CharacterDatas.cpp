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

	returnData[0]		= mMaxStatus.armor_penetration;
	returnData[1]		= mMaxStatus.attack_damage;
	returnData[2]		= mMaxStatus.attack_speed;
	returnData[3]		= mMaxStatus.critical_strike_chance;
	returnData[4]		= mMaxStatus.cirtical_strike_damage;
	returnData[5]		= mMaxStatus.life_steal;
	returnData[6]		= mMaxStatus.ability_power;
	returnData[7]		= mMaxStatus.mage_penetration;
	returnData[8]		= mMaxStatus.omnivamp;
	returnData[9]		= mMaxStatus.physical_vamp;
	returnData[10]	= mMaxStatus.armor;
	returnData[11]	= mMaxStatus.heal_and_shield_power;
	returnData[12]	= mMaxStatus.health;
	returnData[13]	= mMaxStatus.health_regeneration;
	returnData[14]	= mMaxStatus.magic_resistance;
	returnData[15]	= mMaxStatus.tenacity;
	returnData[16]	= mMaxStatus.slow_resist;
	returnData[17]	= mMaxStatus.ability_haste;
	returnData[18]	= mMaxStatus.mana;
	returnData[19]	= mMaxStatus.mana_regeneration;
	returnData[20]	= mMaxStatus.movement_speed;
	returnData[21]	= mMaxStatus.range;

	return returnData;
}

void FCharacterStats::FloatToFData(TArray<float> Data)
{
	mMaxStatus.armor_penetration				= Data[0];
	mMaxStatus.attack_damage					= Data[1];
	mMaxStatus.attack_speed						= Data[2];
	mMaxStatus.critical_strike_chance		= Data[3];
	mMaxStatus.cirtical_strike_damage		= Data[4];
	mMaxStatus.life_steal								= Data[5];
	mMaxStatus.ability_power						= Data[6];
	mMaxStatus.mage_penetration				= Data[7];
	mMaxStatus.omnivamp							= Data[8];
	mMaxStatus.physical_vamp					= Data[9];
	mMaxStatus.armor									= Data[10];
	mMaxStatus.heal_and_shield_power		= Data[11];
	mMaxStatus.health									= Data[12];
	mMaxStatus.health_regeneration			= Data[13];
	mMaxStatus.magic_resistance				= Data[14];
	mMaxStatus.tenacity								= Data[15];
	mMaxStatus.slow_resist							= Data[16];
	mMaxStatus.ability_haste						= Data[17];
	mMaxStatus.mana									= Data[18];
	mMaxStatus.mana_regeneration				= Data[19];
	mMaxStatus.movement_speed				= Data[20];
	mMaxStatus.range									= Data[21];
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
