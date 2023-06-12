// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <PacketStruct.pb.h>
#include <PacketEnum.pb.h>
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
	Idle			UMETA(DisplayName = "Idle"),
	Seat			UMETA(DisplayName = "Seat"),
	StandUp			UMETA(DisplayName = "StandUp"),
	StandDown		UMETA(DisplayName = "StandDown"),
};

UENUM()
enum class ECharacterPart : uint8
{
	None			UMETA(DisplayName = "None"),
	Helmet			UMETA(DisplayName = "Helmet"),
	Shoulders		UMETA(DisplayName = "Shoulders"),
	Chest			UMETA(DisplayName = "Chest"),
	Bracers			UMETA(DisplayName = "Bracers"),
	Hands			UMETA(DisplayName = "Hands"),
	Pants			UMETA(DisplayName = "Pants"),
	Boots			UMETA(DisplayName = "Boots"),
	Weapon_L		UMETA(DisplayName = "Weapon_L"),
	Weapon_R		UMETA(DisplayName = "Weapon_R"),
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
	void CompareEquipments(const FCharacterEquipment& inOtherEquipments);

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 mHair;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 mHelmet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 mShoulders;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 mChest;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 mBracers;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 mHands;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 mPants;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 mBoots;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 mWeapon_L;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
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
	ECharacterRace mRace;

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
	FCharacterData& operator=(const Protocol::SCharacterData& inCharacterData) { UpdateCharacterData(inCharacterData); return *this; }

	void UpdateCharacterData(const FCharacterData& inCharacterData);
	void UpdateCharacterData(const Protocol::SCharacterData& inCharacterData);

public:
	int32					mCharacterID;
	FString					mName;
	int32					mLevel;
	ECharacterClass			mClass;
	FCharacterAppearance	mAppearance;
	FCharacterEquipment		mEquipment;
	FCharacterStatus		mStatus;

};