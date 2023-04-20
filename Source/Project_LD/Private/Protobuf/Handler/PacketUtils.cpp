// Fill out your copyright notice in the Description page of Project Settings.


#include "Protobuf/Handler/PacketUtils.h"
#include <Network/NetworkUtils.h>

const Protocol::ECharacterClass UPacketUtils::ConvertToPClass(const ECharacterClass& inClass)
{
	return StaticCast<Protocol::ECharacterClass>(inClass);
}

const ECharacterClass UPacketUtils::ConvertToUClass(const Protocol::ECharacterClass& inClass)
{
	return StaticCast<ECharacterClass>(inClass);
}

const Protocol::ERace UPacketUtils::ConvertToPRace(const ECharacterRace& inRace)
{
	return StaticCast<Protocol::ERace>(inRace);
}

const ECharacterRace UPacketUtils::ConvertToURace(const Protocol::ERace& inRace)
{
	return StaticCast<ECharacterRace>(inRace);
}

const Protocol::SCharacterAppearance UPacketUtils::ConvertToPAppearance(const FCharacterAppearance& inAppearance)
{
	Protocol::SCharacterAppearance appearance;
	appearance.set_race(ConvertToPRace(inAppearance.mRace));
	appearance.set_seat(inAppearance.mSeat);
	appearance.set_skin_color(inAppearance.mSkin_Color);
	appearance.set_hair_color(inAppearance.mHair_Color);
	appearance.set_eye_color(inAppearance.mEye_Color);
	appearance.set_eyebrow_color(inAppearance.mEyebrow_Color);
	return appearance;
}

const Protocol::SCharacterEqipment UPacketUtils::ConvertToPEqipment(const FCharacterEquipment& inEquipment)
{
	Protocol::SCharacterEqipment eqipment;
	eqipment.set_hair(inEquipment.mHair);
	eqipment.set_helmet(inEquipment.mHelmet);
	eqipment.set_shoulders(inEquipment.mShoulders);
	eqipment.set_chest(inEquipment.mChest);
	eqipment.set_bracers(inEquipment.mBracers);
	eqipment.set_hands(inEquipment.mHands);
	eqipment.set_pants(inEquipment.mPants);
	eqipment.set_boots(inEquipment.mBoots);
	eqipment.set_weapon_l(inEquipment.mWeapon_L);
	eqipment.set_weapon_r(inEquipment.mWeapon_R);
	return eqipment;
}

const Protocol::SCharacterData UPacketUtils::ConvertToPData(const FCharacterData& inData)
{
	Protocol::SCharacterData data;
	data.set_name(UNetworkUtils::ConvertString(inData.mName));
	data.set_level(inData.mLevel);
	data.set_character_class(ConvertToPClass(inData.mClass));

	Protocol::SCharacterAppearance* appearance = data.mutable_appearance();
	*appearance = ConvertToPAppearance(inData.mAppearance);

	Protocol::SCharacterEqipment* eqipment = data.mutable_eqipment();
	*eqipment = ConvertToPEqipment(inData.mEquipment);

	return data;
}
