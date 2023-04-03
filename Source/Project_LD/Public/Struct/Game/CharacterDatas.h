// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <IdentityPacket.pb.h>
#include "CharacterDatas.generated.h"

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	None			UMETA(DisplayName = "None"),
	Warrior 		UMETA(DisplayName = "Warrior"),
	Wizard			UMETA(DisplayName = "Wizard"),
};

UENUM(BlueprintType)
enum class ERace : uint8
{
	None			UMETA(DisplayName = "None"),
	Male			UMETA(DisplayName = "Male"),
	Female			UMETA(DisplayName = "Female"),
	Orc				UMETA(DisplayName = "Orc"),
};

UENUM()
enum class EEquipment : uint8
{
	None			UMETA(DisplayName = "None"),
	//머리부분
	Head			UMETA(DisplayName = "Head"),
	Hair			UMETA(DisplayName = "Hair"),
	Facials			UMETA(DisplayName = "Facials"),
	Ears			UMETA(DisplayName = "Ears"),
	Helmet			UMETA(DisplayName = "Helmet"),

	//상체
	Shoulders		UMETA(DisplayName = "Shoulders"),
	Chest			UMETA(DisplayName = "Chest"),
	ChestAdd		UMETA(DisplayName = "ChestAdd"),
	Bracers			UMETA(DisplayName = "Bracers"),
	BracersAdd		UMETA(DisplayName = "BracersAdd"),
	Hands			UMETA(DisplayName = "Hands"),
	HandsAdd		UMETA(DisplayName = "HandsAdd"),

	//하체
	Pants			UMETA(DisplayName = "Pants"),
	PantsAdd		UMETA(DisplayName = "PantsAdd"),
	Legs			UMETA(DisplayName = "Legs"),
	Boots			UMETA(DisplayName = "Boots"),
	Feet			UMETA(DisplayName = "Feet"),

	//무기
	Back_2HL		UMETA(DisplayName = "Back_2HL"),
	Back_Shield		UMETA(DisplayName = "Back_Shield"),
	Back_WeaponL	UMETA(DisplayName = "Back_WeaponL"),
	Back_WeaponR	UMETA(DisplayName = "Back_WeaponR"),
	Back_Bow		UMETA(DisplayName = "Back_Bow"),
	Quiver			UMETA(DisplayName = "Quiver"),
	Weapon_R_Arrow	UMETA(DisplayName = "Weapon_R_Arrow"),
	Weapon_Shield	UMETA(DisplayName = "Weapon_Shield"),
	Weapon_L		UMETA(DisplayName = "Weapon_L"),
	Weapon_R		UMETA(DisplayName = "Weapon_R"),
	Hip_L			UMETA(DisplayName = "Hip_L"),
	Hip_R			UMETA(DisplayName = "Hip_R")
};

UENUM()
enum class EAppearance : uint8
{
	None			UMETA(DisplayName = "None"),
	Body			UMETA(DisplayName = "Body"),
	Eye				UMETA(DisplayName = "Eye"),
	Eyebrow			UMETA(DisplayName = "Eyebrow"),
	Hair			UMETA(DisplayName = "Hair"),
};

USTRUCT(Atomic, BlueprintType)
struct FCharacterEquipment
{
	GENERATED_BODY()

public:
	FCharacterEquipment();
	void UpdateEquipments(const Protocol::SCharacterEqipment& inCharacterEquipments);

public:
	UPROPERTY()
	int32 mHair;

	UPROPERTY()
	int32 mHelmet;

	UPROPERTY()
	int32 mShoulders;

	UPROPERTY()
	int32 mChestAdd;

	UPROPERTY()
	int32 mBracersAdd;

	UPROPERTY()
	int32 mHandsAdd;

	UPROPERTY()
	int32 mPantsAdd;

	UPROPERTY()
	int32 mBoots;

public:
	UPROPERTY()
	int32 mWeapon_L;

	UPROPERTY()
	int32 mWeapon_R;
};

USTRUCT(Atomic)
struct FCharacterAppearance
{
	GENERATED_BODY()

public:
	FCharacterAppearance();
	void UpdateAppearance(const Protocol::SCharacterAppearance& inCharacterAppearance);

public:
	UPROPERTY()
	int32 mCharacterID;

	UPROPERTY()
	int32 mRace;

	UPROPERTY()
	int32 mCharacterClass;

	UPROPERTY()
	int32 mSeat;

	UPROPERTY()
	int32 mSkin_Color;

	UPROPERTY()
	int32 mHair_Color;

	UPROPERTY()
	int32 mEye_Color;

	UPROPERTY()
	int32 mEyebrow_Color;
};

USTRUCT(Atomic, BlueprintType)
struct FCharacterStatus
{
	GENERATED_BODY()

};