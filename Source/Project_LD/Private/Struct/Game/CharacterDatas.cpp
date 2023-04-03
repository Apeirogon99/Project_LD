// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/Game/CharacterDatas.h"

FCharacterEquipment::FCharacterEquipment() : mHair(0), mHelmet(0), mShoulders(0), mChestAdd(0),mBracersAdd(0), mHandsAdd(0), mPantsAdd(0), mBoots(0), mWeapon_L(0), mWeapon_R(0)
{

}

void FCharacterEquipment::UpdateEquipments(const Protocol::SCharacterEqipment& inCharacterEquipments)
{
	//mEars			= inCharacterEquipments.ears();
	mHair			= inCharacterEquipments.hair();
	//mFacials_01		= inCharacterEquipments.facials_01();
	mHelmet			= inCharacterEquipments.helmet();
	mShoulders		= inCharacterEquipments.shoulders();
	mChestAdd		= inCharacterEquipments.chest_add();
	mBracersAdd		= inCharacterEquipments.bracers_add();
	mHandsAdd		= inCharacterEquipments.hands_add();
	//mSkirt			= inCharacterEquipments.skirt();
	mPantsAdd		= inCharacterEquipments.pants_add();
	//mLegsAdd		= inCharacterEquipments.legs_add();
	//mCape			= inCharacterEquipments.cape();

	mBoots			= inCharacterEquipments.boots();
	//mBelt			= inCharacterEquipments.belt();
	//mTabard			= inCharacterEquipments.tabard();
	mWeapon_L		= inCharacterEquipments.weapon_l();
	mWeapon_R		= inCharacterEquipments.weapon_r();
}

FCharacterAppearance::FCharacterAppearance() : mCharacterID(0), mRace(0), mCharacterClass(0), mSeat(0), mSkin_Color(0), mHair_Color(0), mEye_Color(0), mEyebrow_Color(0)
{
}

void FCharacterAppearance::UpdateAppearance(const Protocol::SCharacterAppearance& inCharacterAppearance)
{
	mCharacterID	= 0;
	mRace			= inCharacterAppearance.race();
	mCharacterClass = inCharacterAppearance.character_class();
	mSeat			= inCharacterAppearance.seat();
	mSkin_Color		= inCharacterAppearance.skin_color();
	mHair_Color		= inCharacterAppearance.hair_color();
	mEye_Color		= inCharacterAppearance.eye_color();
	mEyebrow_Color	= inCharacterAppearance.eyebrow_color();
}
