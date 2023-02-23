// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterDatas.generated.h"

UENUM(BlueprintType)
enum class EClass : uint8
{
	None			UMETA(DisplayName = "None"),
	Warrior 		UMETA(DisplayName = "Warrior"),
	Wizard			UMETA(DisplayName = "Wizard"),
};

UENUM(BlueprintType)
enum class ETribe : uint8
{
	None			UMETA(DisplayName = "None"),
	Man				UMETA(DisplayName = "Man"),
	Woman			UMETA(DisplayName = "Woman"),
	Orc				UMETA(DisplayName = "Orc"),
};

UENUM()
enum class EPart : uint8
{
	None			UMETA(DisplayName = "None"),
	Boots			UMETA(DisplayName = "Boots"),
	Bracers			UMETA(DisplayName = "Bracers"),
	Chest			UMETA(DisplayName = "Chest"),
	Feet			UMETA(DisplayName = "Feet"),
	Hands			UMETA(DisplayName = "Hands"),
	Head			UMETA(DisplayName = "Head"),
	Hair			UMETA(DisplayName = "Hair"),
	Eye				UMETA(DisplayName = "Eye"),
	Eyebrow			UMETA(DisplayName = "Eyebrow"),
	Ears			UMETA(DisplayName = "Ears"),
	Pants			UMETA(DisplayName = "Pants"),
};

USTRUCT(Atomic)
struct FCharacterDatas
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString mName;

	UPROPERTY()
	int32 mLevel;

	UPROPERTY()
	int32 mPosition;

	UPROPERTY()
	int32 mClass;

	UPROPERTY()
	int32 mTribe;

	UPROPERTY()
	uint32 mSkin;

	UPROPERTY()
	uint32 mHair;

	UPROPERTY()
	uint32 mEye;

	UPROPERTY()
	uint32 mEyebrow;
};

USTRUCT(Atomic)
struct FCharacterAppearance
{
	GENERATED_BODY()

//Color
public:
	uint32 mBodyColor;
	uint32 mHairColor;
	uint32 mEyeColor;
	TArray<int32> mMeshs;

//Skin
//public:
//	int32 mEars;
//	int32 mFeet;
//	int32 mHair;
//	int32 mFacials_01;
//	int32 mFacials_02;
//	int32 mHelmet;
//	int32 mShoulders;
//	int32 mSkirt;
//	int32 mLegs;
//	int32 mLegsAdd;
//	int32 mHands;
//	int32 mHandsAdd;
//	int32 mChest;
//	int32 mChestAdd;
//	int32 mCape;
//	int32 mBracers;
//	int32 mBracersAdd;
//	int32 mBoots;
//	int32 mBelt;
//	int32 mTabard;
//	 
//Weapon
//public:
//	int32 mBack_2HL;
//	int32 mBack_Shield;
//	int32 mBack_WeaponL;
//	int32 mBack_WeaponR;
//	int32 mBack_Bow;
//	int32 mQuiver;
//	int32 mWeapon_R_Arrow;
//	int32 mWeapon_Shield;
//	int32 mWeapon_L;
//	int32 mWeapon_R;
//	int32 mHip_L;
//	int32 mHip_R;
};