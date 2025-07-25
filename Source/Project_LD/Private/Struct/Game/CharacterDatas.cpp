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

FCharacterData::FCharacterData() : mID(0), mName(TEXT("")), mLevel(0),mExp(0), mClass(ECharacterClass::None), mAppearance(), mEquipment()
{
}

void FCharacterData::UpdateCharacterData(const FCharacterData& inCharacterData)
{
	mID					= inCharacterData.mID;
	mName				= inCharacterData.mName;
	mLevel				= inCharacterData.mLevel;
	mExp				= inCharacterData.mExp;
	mClass				= inCharacterData.mClass;

	mAppearance			= inCharacterData.mAppearance;
	mEquipment			= inCharacterData.mEquipment;
}

void FCharacterData::UpdateCharacterData(const Protocol::SCharacterData& inCharacterData)
{
	mID				= inCharacterData.id();
	mName			= UNetworkUtils::ConvertFString(inCharacterData.name());
	mLevel			= inCharacterData.level();
	mExp			= inCharacterData.experience();
	mClass			= StaticCast<ECharacterClass>(inCharacterData.character_class());

	const Protocol::SCharacterAppearance& appearance = inCharacterData.appearance();
	mAppearance.UpdateAppearance(appearance);

	const Protocol::SCharacterEqipment& eqipment = inCharacterData.eqipment();
	mEquipment.UpdateEquipments(eqipment);
}

FPartyPlayerInfo::FPartyPlayerInfo() : mValid(false), mLevel(0), mCharacterClass(ECharacterClass::None), mName(TEXT(""))
{
}

FPartyPlayerInfo::~FPartyPlayerInfo()
{
}
