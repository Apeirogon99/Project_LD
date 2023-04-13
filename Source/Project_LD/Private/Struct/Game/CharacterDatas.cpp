// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/Game/CharacterDatas.h"

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
	mChest			= inCharacterEquipments.chest_add();
	mBracers		= inCharacterEquipments.bracers_add();
	mHands			= inCharacterEquipments.hands_add();
	mPants			= inCharacterEquipments.pants_add();
	mBoots			= inCharacterEquipments.boots();
	mWeapon_L		= inCharacterEquipments.weapon_l();
	mWeapon_R		= inCharacterEquipments.weapon_r();
}

FCharacterAppearance::FCharacterAppearance() : mSeat(0), mSkin_Color(0), mHair_Color(0), mEye_Color(0), mEyebrow_Color(0)
{
}

void FCharacterAppearance::UpdateAppearance(const FCharacterAppearance& inCharacterAppearance)
{
	mSeat			= inCharacterAppearance.mSeat;
	mSkin_Color		= inCharacterAppearance.mSkin_Color;
	mHair_Color		= inCharacterAppearance.mHair_Color;
	mEye_Color		= inCharacterAppearance.mEye_Color;
	mEyebrow_Color	= inCharacterAppearance.mEyebrow_Color;
}

void FCharacterAppearance::UpdateAppearance(const Protocol::SCharacterAppearance& inCharacterAppearance)
{
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


FCharacterData::FCharacterData() : mCharacterID(0), mClass(ECharacterClass::None), mRace(ECharacterRace::None), mAppearance(), mEquipment(), mStatus()
{
}

void FCharacterData::UpdateCharacterData(const FCharacterData& inCharacterData)
{
	mName				= inCharacterData.mName;
	mLevel				= inCharacterData.mLevel;
	mCharacterID		= inCharacterData.mCharacterID;
	mClass				= inCharacterData.mClass;
	mRace				= inCharacterData.mRace;
	mAppearance			= inCharacterData.mAppearance;
	mEquipment			= inCharacterData.mEquipment;
	mStatus				= inCharacterData.mStatus;
}