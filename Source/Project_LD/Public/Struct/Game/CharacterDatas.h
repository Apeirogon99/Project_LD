// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <PacketStruct.pb.h>
#include <PacketEnum.pb.h>
#include "StatsManager.h"
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
	void SetHair(const int32 inHair)						{ mHair = inHair; }
	void SetHelmet(const int32 inHelmet)				{ mHelmet = inHelmet; }
	void SetShoulders(const int32 inShoulders)		{ mShoulders = inShoulders; }
	void SetChest(const int32 inChest)					{ mChest = inChest; }
	void SetBracers(const int32 inBracers)				{ mBracers = inBracers; }
	void SetHands(const int32 inHands)					{ mHands = inHands; }
	void SetPants(const int32 inPants)					{ mPants = inPants; }
	void SetBoots(const int32 inBoots)					{ mBoots = inBoots; }
	void SetWeaponL(const int32 inWeaponL)		{ mWeapon_L = inWeaponL; }
	void SetWeaponR(const int32 inWeaponR)		{ mWeapon_R = inWeaponR; }

public:
	int32 GetHair() const				{ return mHair; }
	int32 GetHelmet() const			{ return mHelmet; }
	int32 GetShoulders() const		{ return mShoulders; }
	int32 GetChest() const			{ return mChest; }
	int32 GetBracers() const		{ return mBracers; }
	int32 GetHands() const			{ return mHands; }
	int32 GetPants() const			{ return mPants; }
	int32 GetBoots() const			{ return mBoots; }
	int32 GetWeaponL() const		{ return mWeapon_L; }
	int32 GetWeaponR() const		{ return mWeapon_R; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	int32 mHair;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	int32 mHelmet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	int32 mShoulders;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	int32 mChest;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	int32 mBracers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	int32 mHands;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	int32 mPants;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	int32 mBoots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	int32 mWeapon_L;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
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
	void SetRace(const ECharacterRace inRace)					{ mRace = inRace; }
	void SetSeat(const int32 inSeat)									{ mSeat = inSeat; }
	void SetSkinColor(const int32 inSkinColor)					{ mSkin_Color = inSkinColor; }
	void SetHairColor(const int32 inHairColor)					{ mHair_Color = inHairColor; }
	void SetEyeColor(const int32 inEyeColor)					{ mEye_Color = inEyeColor; }
	void SetEyebrowColor(const int32 inEyebrowColor)	{ mEyebrow_Color = inEyebrowColor; }

public:
	ECharacterRace GetRace() const						{ return mRace; }
	int32 GetSeat() const											{ return mSeat; }
	int32 GetSkinColor() const								{ return mSkin_Color; }
	int32 GetHairColor() const									{ return mHair_Color; }
	int32 GetEyeColor() const									{ return mEye_Color; }
	int32 GetEyebrowColor() const							{ return mEyebrow_Color; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	ECharacterRace mRace;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	int32 mSeat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	int32 mSkin_Color;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	int32 mHair_Color;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	int32 mEye_Color;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	int32 mEyebrow_Color;
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
	void SetID(const int32& inID) { mID = inID; }
	void SetName(const FString inName)													{ mName = inName; }
	void SetLevel (const int32 inLevel)														{ mLevel = inLevel; }
	void SetExp (const int32 inExp)															{ mExp = inExp; }
	void SetClass(const ECharacterClass inClass)										{ mClass = inClass; }
	void SetAppearance(const FCharacterAppearance inAppearance)		{ mAppearance = inAppearance; }
	void SetEquipment(const FCharacterEquipment inEquipment)			{ mEquipment = inEquipment; }

public:
	int32					GetID() const					{ return mID; }
	FString					GetName() const					{ return mName; }
	int32					GetLevel() const				{ return mLevel; }
	int32					GetExp() const					{ return mExp; }
	ECharacterClass			GetClass() const				{ return mClass; }
	FCharacterAppearance&	GetAppearance() 				{ return mAppearance; }
	FCharacterEquipment&	GetEquipment() 					{ return mEquipment; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32					mID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FString					mName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32					mLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32					mExp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	ECharacterClass			mClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FCharacterAppearance	mAppearance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FCharacterEquipment		mEquipment;
};


USTRUCT(Atomic, BlueprintType)
struct FPartyPlayerInfo
{
	GENERATED_BODY()

public:
	FPartyPlayerInfo();
	~FPartyPlayerInfo();

public:
	void SetValid(const bool inValid)				{ mValid = inValid; }
	void SetLevel(const int32 inLevel)				{ mLevel = inLevel; }
	void SetClass(const ECharacterClass inClass)	{ mCharacterClass = inClass; }
	void SetName(const FString inName)				{ mName = inName; }

public:
	bool			IsValidArea()		const { return mValid; }
	int32			GetLevel()			const { return mLevel; }
	ECharacterClass	GetCharacterClass() const { return mCharacterClass; }
	FString			GetName()			const { return mName; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
		bool mValid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
		int32 mLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
		ECharacterClass	mCharacterClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
		FString mName;

};