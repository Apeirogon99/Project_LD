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
	Male				UMETA(DisplayName = "Male"),
	Female			UMETA(DisplayName = "Female"),
	Orc				UMETA(DisplayName = "Orc"),
};

UENUM(BlueprintType)
enum class ECharacterPose : uint8
{
	Default			UMETA(DisplayName = "Default"),
	Idle					UMETA(DisplayName = "Idle"),
	Seat					UMETA(DisplayName = "Seat"),
	StandUp			UMETA(DisplayName = "StandUp"),
	StandDown		UMETA(DisplayName = "StandDown"),
};

UENUM()
enum class ECharacterPart : uint8
{
	None				UMETA(DisplayName = "None"),
	Helmet			UMETA(DisplayName = "Helmet"),
	Shoulders		UMETA(DisplayName = "Shoulders"),
	Chest				UMETA(DisplayName = "Chest"),
	Bracers			UMETA(DisplayName = "Bracers"),
	Hands				UMETA(DisplayName = "Hands"),
	Pants				UMETA(DisplayName = "Pants"),
	Boots				UMETA(DisplayName = "Boots"),
	Weapon_L		UMETA(DisplayName = "Weapon_L"),
	Weapon_R		UMETA(DisplayName = "Weapon_R"),
};

UENUM()
enum class EAppearance : uint8
{
	None				UMETA(DisplayName = "None"),
	Body				UMETA(DisplayName = "Body"),
	Eye					UMETA(DisplayName = "Eye"),
	Eyebrow			UMETA(DisplayName = "Eyebrow"),
	Hair					UMETA(DisplayName = "Hair"),
};

/*
UENUM()
enum class ECharacterStatus : uint8
{

};*/

USTRUCT(Atomic, BlueprintType)
struct FCharacterEquipment
{
	GENERATED_BODY()

public:
	FCharacterEquipment();
	FCharacterEquipment(const FCharacterEquipment& inCharacterEquipments) { UpdateEquipments(inCharacterEquipments); }
	FCharacterEquipment(const Protocol::SCharacterEqipment& inCharacterEquipments) { UpdateEquipments(inCharacterEquipments);}

	FCharacterEquipment& operator=(const FCharacterEquipment& inCharacterEquipments) { UpdateEquipments(inCharacterEquipments); return *this; }
	FCharacterEquipment& operator=(const Protocol::SCharacterEqipment& inCharacterEquipments) { UpdateEquipments(inCharacterEquipments); return *this; }

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

USTRUCT(BlueprintType)
struct FStatusData
{
	GENERATED_USTRUCT_BODY()

public:
	FStatusData() :
		character_class_id(0),
		armor_penetration(0),
		attack_damage(0),
		attack_speed(0),
		critical_strike_chance(0),
		cirtical_strike_damage(0),
		life_steal(0),
		ability_power(0),
		mage_penetration(0),
		omnivamp(0),
		physical_vamp(0),
		armor(0),
		heal_and_shield_power(0),
		health(0),
		health_regeneration(0),
		magic_resistance(0),
		tenacity(0),
		slow_resist(0),
		ability_haste(0),
		mana(0),
		mana_regeneration(0),
		movement_speed(0),
		range(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 character_class_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 armor_penetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 attack_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 attack_speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 critical_strike_chance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 cirtical_strike_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 life_steal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 ability_power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 mage_penetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 omnivamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 physical_vamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 heal_and_shield_power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 health_regeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 magic_resistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 tenacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 slow_resist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 ability_haste;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 mana_regeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 movement_speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		int32 range;
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
	
public:
	FStatusData		mMaxStatus;
	FStatusData		mCurrentStatus;
};


USTRUCT(Atomic)
struct FCharacterData
{
	GENERATED_BODY()

public:
	FCharacterData();
	FCharacterData(const FCharacterData& inCharacterData) { UpdateCharacterData(inCharacterData); }
	FCharacterData(const Protocol::SCharacterData& inCharacterData) { UpdateCharacterData(inCharacterData); }

	FCharacterData& operator=(const FCharacterData& inCharacterData) { UpdateCharacterData(inCharacterData); return *this; }
	FCharacterData& operator=(const Protocol::SCharacterData& inCharacterData) { UpdateCharacterData(inCharacterData); return *this; }

	void UpdateCharacterData(const FCharacterData& inCharacterData);
	void UpdateCharacterData(const Protocol::SCharacterData& inCharacterData);

public:
	FString							mName;
	int32								mLevel;
	ECharacterClass				mClass;
	FCharacterAppearance	mAppearance;
	FCharacterEquipment		mEquipment;
};