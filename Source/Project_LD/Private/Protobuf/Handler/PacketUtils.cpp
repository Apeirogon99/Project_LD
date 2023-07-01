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
	appearance.set_race(ConvertToPRace(inAppearance.GetRace()));
	appearance.set_seat(inAppearance.GetSeat());
	appearance.set_skin_color(inAppearance.GetSkinColor());
	appearance.set_hair_color(inAppearance.GetHairColor());
	appearance.set_eye_color(inAppearance.GetEyeColor());
	appearance.set_eyebrow_color(inAppearance.GetEyebrowColor());
	return appearance;
}

const Protocol::SCharacterEqipment UPacketUtils::ConvertToPEqipment(const FCharacterEquipment& inEquipment)
{
	Protocol::SCharacterEqipment eqipment;
	eqipment.set_hair(inEquipment.GetHair());
	eqipment.set_helmet(inEquipment.GetHelmet());
	eqipment.set_shoulders(inEquipment.GetShoulders());
	eqipment.set_chest(inEquipment.GetChest());
	eqipment.set_bracers(inEquipment.GetBracers());
	eqipment.set_hands(inEquipment.GetHands());
	eqipment.set_pants(inEquipment.GetPants());
	eqipment.set_boots(inEquipment.GetBoots());
	eqipment.set_weapon_l(inEquipment.GetWeaponL());
	eqipment.set_weapon_r(inEquipment.GetWeaponR());
	return eqipment;
}

const Protocol::SCharacterData UPacketUtils::ConvertToPData(const FCharacterData& inData)
{
	Protocol::SCharacterData data;
	data.set_name(UNetworkUtils::ConvertString(inData.GetName()));
	data.set_level(inData.GetLevel());
	data.set_character_class(ConvertToPClass(inData.GetClass()));

	Protocol::SCharacterAppearance* appearance = data.mutable_appearance();
	*appearance = ConvertToPAppearance(inData.GetAppearance());

	Protocol::SCharacterEqipment* eqipment = data.mutable_eqipment();
	*eqipment = ConvertToPEqipment(inData.GetEquipment());

	return data;
}
