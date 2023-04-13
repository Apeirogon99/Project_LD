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
enum class ECharacterRace : uint8
{
	None			UMETA(DisplayName = "None"),
	Male			UMETA(DisplayName = "Male"),
	Female			UMETA(DisplayName = "Female"),
	Orc				UMETA(DisplayName = "Orc"),
};

UENUM(BlueprintType)
enum class ECharacterPose : uint8
{
	None			UMETA(DisplayName = "None"),
	Seat			UMETA(DisplayName = "Seat")
};

UENUM()
enum class EEquipment : uint8
{
	None			UMETA(DisplayName = "None"),
	Body			UMETA(DisplayName = "Body"),
	Hair			UMETA(DisplayName = "Hair"),
	Helmet			UMETA(DisplayName = "Helmet"),
	Shoulders		UMETA(DisplayName = "Shoulders"),
	Chest			UMETA(DisplayName = "Chest"),
	Bracers			UMETA(DisplayName = "Bracers"),
	Hands			UMETA(DisplayName = "Hands"),
	Pants			UMETA(DisplayName = "Pants"),
	Boots			UMETA(DisplayName = "Boots"),

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
	FCharacterEquipment(const FCharacterEquipment& inCharacterEquipments) { UpdateEquipments(inCharacterEquipments); }
	FCharacterEquipment(const Protocol::SCharacterAppearance& inCharacterEquipments) { UpdateEquipments(inCharacterEquipments);}

	FCharacterEquipment& operator=(const FCharacterEquipment& inCharacterEquipments) { UpdateEquipments(inCharacterEquipments); return *this; }
	FCharacterEquipment& operator=(const Protocol::SCharacterAppearance& inCharacterEquipments) { UpdateEquipments(inCharacterEquipments); return *this; }

	void UpdateEquipments(const FCharacterEquipment& inCharacterEquipments);
	void UpdateEquipments(const Protocol::SCharacterEqipment& inCharacterEquipments);

public:
	UPROPERTY()
	int32 mHair;

	UPROPERTY()
	int32 mHelmet;

	UPROPERTY()
	int32 mShoulders;

	UPROPERTY()
	int32 mChest;

	UPROPERTY()
	int32 mBracers;

	UPROPERTY()
	int32 mHands;

	UPROPERTY()
	int32 mPants;

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
	FCharacterAppearance(const FCharacterAppearance& inCharacterAppearance) { UpdateAppearance(inCharacterAppearance); }
	FCharacterAppearance(const Protocol::SCharacterAppearance& inCharacterAppearance) { UpdateAppearance(inCharacterAppearance); }

	FCharacterAppearance& operator=(const FCharacterAppearance& inCharacterAppearance) { UpdateAppearance(inCharacterAppearance); return *this; }
	FCharacterAppearance& operator=(const Protocol::SCharacterAppearance& inCharacterAppearance) { UpdateAppearance(inCharacterAppearance); return *this; }

	void UpdateAppearance(const FCharacterAppearance& inCharacterAppearance);
	void UpdateAppearance(const Protocol::SCharacterAppearance& inCharacterAppearance);

public:
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

public:
	FCharacterStatus();
	FCharacterStatus(const FCharacterStatus& inCharacterStatus) { UpdateCharacterStatus(inCharacterStatus); }
	FCharacterStatus& operator=(const FCharacterStatus& inCharacterStatus) { UpdateCharacterStatus(inCharacterStatus); return *this; }

	void UpdateCharacterStatus(const FCharacterStatus& inCharacterStatus);
};


USTRUCT(Atomic)
struct FCharacterData
{
	GENERATED_BODY()

public:
	FCharacterData();
	FCharacterData(const FCharacterData& inCharacterData) { UpdateCharacterData(inCharacterData); }
	FCharacterData& operator=(const FCharacterData& inCharacterData) { UpdateCharacterData(inCharacterData); return *this; }

	void UpdateCharacterData(const FCharacterData& inCharacterData);

public:
	int32					mCharacterID;
	FString					mName;
	int32					mLevel;
	ECharacterClass			mClass;
	ECharacterRace			mRace;
	FCharacterAppearance	mAppearance;
	FCharacterEquipment		mEquipment;
	FCharacterStatus		mStatus;

};