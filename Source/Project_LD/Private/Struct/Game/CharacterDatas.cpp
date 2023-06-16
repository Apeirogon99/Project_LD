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

FCharacterAppearance::FCharacterAppearance() : mRace(ECharacterRace::None), mSeat(0), mSkin_Color(0), mHair_Color(0), mEye_Color(0), mEyebrow_Color(0)
{
}

void FCharacterAppearance::UpdateAppearance(const FCharacterAppearance& inCharacterAppearance)
{
	mRace			= inCharacterAppearance.mRace;
	mSeat			= inCharacterAppearance.mSeat;
	mSkin_Color		= inCharacterAppearance.mSkin_Color;
	mHair_Color		= inCharacterAppearance.mHair_Color;
	mEye_Color		= inCharacterAppearance.mEye_Color;
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

FCharacterStatus::FCharacterStatus()
{
}

void FCharacterStatus::UpdateCharacterStatus(const FCharacterStatus& inCharacterStatus)
{
}


FCharacterData::FCharacterData() : mName(TEXT("")), mLevel(0), mClass(ECharacterClass::None), mAppearance(), mEquipment()
{
}

void FCharacterData::UpdateCharacterData(const FCharacterData& inCharacterData)
{
	mName				= inCharacterData.mName;
	mLevel				= inCharacterData.mLevel;
	mClass				= inCharacterData.mClass;

	mAppearance			= inCharacterData.mAppearance;
	mEquipment			= inCharacterData.mEquipment;
}

void FCharacterData::UpdateCharacterData(const Protocol::SCharacterData& inCharacterData)
{
	mName			= UNetworkUtils::ConvertFString(inCharacterData.name());
	mLevel			= inCharacterData.level();
	mClass			= StaticCast<ECharacterClass>(inCharacterData.character_class());

	const Protocol::SCharacterAppearance& appearance = inCharacterData.appearance();
	mAppearance.UpdateAppearance(appearance);

	const Protocol::SCharacterEqipment& eqipment = inCharacterData.eqipment();
	mEquipment.UpdateEquipments(eqipment);
}
