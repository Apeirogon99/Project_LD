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

UENUM()
enum class ECharacterStatus : uint8
{
	None								UMETA(DisplayName = "None"),
	ArmorPenetration			UMETA(DisplayName = "ArmorPenetration"),
	AttackDamage					UMETA(DisplayName = "AttackDamage"),
	AttackSpeed					UMETA(DisplayName = "AttackSpeed"),
	CriticalStrikeChance		UMETA(DisplayName = "CriticalStrikeChance"),
	CriticalStrikeDamage		UMETA(DisplayName = "CriticalStrikeDamage"),
	LifeSteal							UMETA(DisplayName = "LifeSteal"),
	AbilityPower					UMETA(DisplayName = "AbilityPower"),
	MagePenetration				UMETA(DisplayName = "MagePenetration"),
	Omnivamp						UMETA(DisplayName = "Omnivamp"),
	PhysicalVamp					UMETA(DisplayName = "PhysicalVamp"),
	Armor								UMETA(DisplayName = "Armor"),
	HealAndShieldPower		UMETA(DisplayName = "HealAndShieldPower"),
	Health								UMETA(DisplayName = "Health"),
	HealthRegeneration		UMETA(DisplayName = "HealthRegeneration"),
	MagicResistance				UMETA(DisplayName = "MagicResistance"),
	Tenacity							UMETA(DisplayName = "Tenacity"),
	SlowResist						UMETA(DisplayName = "SlowResist"),
	AbilityHaste					UMETA(DisplayName = "AbilityHaste"),
	Mana								UMETA(DisplayName = "Mana"),
	ManaRegeneration			UMETA(DisplayName = "ManaRegeneration"),
	MovementSpeed				UMETA(DisplayName = "MovementSpeed"),
	Range								UMETA(DisplayName = "Range"),
};

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
	
	TArray<float> GetAllItemIndex();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	int32 mHair;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	int32 mHelmet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	int32 mShoulders;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	int32 mChest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	int32 mBracers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	int32 mHands;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	int32 mPants;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	int32 mBoots;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	int32 mWeapon_L;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	int32 mWeapon_R;
};

USTRUCT(Atomic, BlueprintType)
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance")
	ECharacterRace mRace;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance")
	int32 mSeat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance")
	int32 mSkin_Color;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance")
	int32 mHair_Color;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance")
	int32 mEye_Color;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance")
	int32 mEyebrow_Color;
};

USTRUCT(Atomic, BlueprintType)
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
		float character_class_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float armor_penetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float attack_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float attack_speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float critical_strike_chance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float cirtical_strike_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float life_steal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float ability_power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float mage_penetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float omnivamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float physical_vamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float heal_and_shield_power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float health_regeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float magic_resistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float tenacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float slow_resist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float ability_haste;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float mana_regeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float movement_speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus")
		float range;
};

USTRUCT(Atomic, BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

public:
	FCharacterStats();
	FCharacterStats(const FCharacterStats& inCharacterStatus) { UpdateCharacterStatus(inCharacterStatus); }
	FCharacterStats& operator=(const FCharacterStats& inCharacterStatus) { UpdateCharacterStatus(inCharacterStatus); return *this; }

	void UpdateCharacterStatus(const FCharacterStats& inCharacterStatus);

	TArray<float> FDataToFloat();
	void	FloatToFData(TArray<float> Data);

	//int operator[](ECharacterStatus Index) const { return static_cast<int>(Index) - 1; };

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FStatusData 	mMaxStatus;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FStatusData		mCurrentStatus;
};


USTRUCT(Atomic, BlueprintType)
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FString					mName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	int32					mLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	ECharacterClass			mClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FCharacterAppearance	mAppearance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	FCharacterEquipment		mEquipment;
};