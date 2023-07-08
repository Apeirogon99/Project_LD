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
struct FStatsData
{
	GENERATED_USTRUCT_BODY()

public:
	FStatsData() :
		class_id(0),
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

public:
	void SetArmorPenetration(const float inarmor_penetration)											{ armor_penetration = inarmor_penetration; }
	void SetAttackDamage(const float inattack_damage)														{ attack_damage = inattack_damage; }
	void SetAttackSpeed(const float inattack_speed)																{ attack_speed = inattack_speed; }
	void SetCriticalStrikeChance(const float incritical_strike_chance)								{ critical_strike_chance = incritical_strike_chance; }
	void SetCriticalStrikeDamage(const float incirtical_strike_damage)								{ cirtical_strike_damage = incirtical_strike_damage; }
	void SetLifeSteal(const float inlife_steal)																			{ life_steal = inlife_steal; }
	void SetAbilityPower(const float inability_power)															{ ability_power = inability_power; }
	void SetMagePenetration(const float inmage_penetration)												{ mage_penetration = inmage_penetration; }
	void SetOmniVamp(const float inomnivamp)																		{ omnivamp = inomnivamp; }
	void SetPhysicalVamp(const float inphysical_vamp)														{ physical_vamp = inphysical_vamp; }
	void SetArmor(const float inarmor)																					{ armor = inarmor; }
	void SetHealAndShieldPower(const float inheal_and_shield_power)								{ heal_and_shield_power = inheal_and_shield_power; }
	void SetHealth(const float inhealth)																					{ health = inhealth; }
	void SetHealthRegeneration(const float inhealth_regeneration)										{ health_regeneration = inhealth_regeneration; }
	void SetMagicResistance(const float inmagic_resistance)												{ magic_resistance = inmagic_resistance; }
	void SetTenacity(const float intenacity)																			{ tenacity = intenacity; }
	void SetSlowResist(const float inslow_resist)																	{ slow_resist = inslow_resist; }
	void SetAbilityHaste(const float inability_haste)																{ ability_haste = inability_haste; }
	void SetMana(const float inmana)																						{ mana = inmana; }
	void SetManaRegeneration(const float inmana_regeneration)											{ mana_regeneration  = inmana_regeneration; }
	void SetMovementSpeed(const float inmovement_speed)													{ movement_speed = inmovement_speed; }
	void SetRange(const float inrange)																					{ range = inrange; }

public:
	float GetArmorPenetration() const					{ return armor_penetration; }
	float GetAttackDamage() const							{ return attack_damage; }
	float GetAttackSpeed() const								{ return attack_speed; }
	float GetCriticalStrikeChance() const				{ return critical_strike_chance; }
	float GetCriticalStrikeDamage() const				{ return cirtical_strike_damage; }
	float GetLifeSteal() const									{ return life_steal; }
	float GetAbilityPower() const							{ return ability_power; }
	float GetMagePenetration() const						{ return mage_penetration; }
	float GetOmniVamp() const								{ return omnivamp; }
	float GetPhysicalVamp() const							{ return physical_vamp; }
	float GetArmor() const										{ return armor; }
	float GetHealAndShieldPower() const				{ return heal_and_shield_power; }
	float GetHealth() const										{ return health; }
	float GetHealthRegeneration() const					{ return health_regeneration; }
	float GetMagicResistance() const						{ return magic_resistance; }
	float GetTenacity() const									{ return tenacity; }
	float GetSlowResist() const								{ return slow_resist; }
	float GetAbilityHaste() const								{ return ability_haste; }
	float GetMana() const											{ return mana; }
	float GetManaRegeneration() const					{ return mana_regeneration; }
	float GetMovementSpeed() const						{ return movement_speed; }
	float GetRange() const										{ return range; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float class_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float armor_penetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float attack_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float attack_speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float critical_strike_chance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float cirtical_strike_damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float life_steal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float ability_power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float mage_penetration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float omnivamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float physical_vamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float heal_and_shield_power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float health_regeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float magic_resistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float tenacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float slow_resist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float ability_haste;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float mana_regeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float movement_speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStatus", meta = (AllowPrivateAccess = "true"))
		float range;
};

USTRUCT(Atomic, BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

public:
	FCharacterStats();
	FCharacterStats(const FCharacterStats& inCharacterStats) { UpdateCharacterStats(inCharacterStats); }
	FCharacterStats& operator=(const FCharacterStats& inCharacterStats) { UpdateCharacterStats(inCharacterStats); return *this; }

	void UpdateCharacterStats(const FCharacterStats& inCharacterStats);

public:
	void SetMaxStats(const FStatsData& inMaxStats) { mMaxStats = inMaxStats; }
	void SetCurrentStats(const FStatsData& inCurrentStats) { mCurrentStats = inCurrentStats; }

public:
	FStatsData	GetMaxStats() const { return mMaxStats; }
	FStatsData	GetCurrentStats() const { return mCurrentStats; }

public:
	TArray<float> FDataToFloat();
	void	FloatToFData(TArray<float> Data);

	void UpdateStats(ECharacterStatus InStats, float Invalue);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FStatsData 		mMaxStats;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FStatsData		mCurrentStats;
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
	void SetName(const FString inName)													{ mName = inName; }
	void SetLevel (const int32 inLevel)														{ mLevel = inLevel; }
	void SetClass(const ECharacterClass inClass)										{ mClass = inClass; }
	void SetAppearance(const FCharacterAppearance inAppearance)		{ mAppearance = inAppearance; }
	void SetEquipment(const FCharacterEquipment inEquipment)			{ mEquipment = inEquipment; }

public:
	FString							GetName() const						{ return mName; }
	int32								GetLevel() const						{ return mLevel; }
	ECharacterClass				GetClass() const						{ return mClass; }
	FCharacterAppearance	GetAppearance() const			{ return mAppearance; }
	FCharacterEquipment		GetEquipment() const				{ return mEquipment; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FString					mName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32					mLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	ECharacterClass			mClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FCharacterAppearance	mAppearance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FCharacterEquipment		mEquipment;
};