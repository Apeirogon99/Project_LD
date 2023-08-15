// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StatsManager.generated.h"

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
	void SetArmorPenetration(const float inarmor_penetration) { armor_penetration = inarmor_penetration; }
	void SetAttackDamage(const float inattack_damage) { attack_damage = inattack_damage; }
	void SetAttackSpeed(const float inattack_speed) { attack_speed = inattack_speed; }
	void SetCriticalStrikeChance(const float incritical_strike_chance) { critical_strike_chance = incritical_strike_chance; }
	void SetCriticalStrikeDamage(const float incirtical_strike_damage) { cirtical_strike_damage = incirtical_strike_damage; }
	void SetLifeSteal(const float inlife_steal) { life_steal = inlife_steal; }
	void SetAbilityPower(const float inability_power) { ability_power = inability_power; }
	void SetMagePenetration(const float inmage_penetration) { mage_penetration = inmage_penetration; }
	void SetOmniVamp(const float inomnivamp) { omnivamp = inomnivamp; }
	void SetPhysicalVamp(const float inphysical_vamp) { physical_vamp = inphysical_vamp; }
	void SetArmor(const float inarmor) { armor = inarmor; }
	void SetHealAndShieldPower(const float inheal_and_shield_power) { heal_and_shield_power = inheal_and_shield_power; }
	void SetHealth(const float inhealth) { health = inhealth; }
	void SetHealthRegeneration(const float inhealth_regeneration) { health_regeneration = inhealth_regeneration; }
	void SetMagicResistance(const float inmagic_resistance) { magic_resistance = inmagic_resistance; }
	void SetTenacity(const float intenacity) { tenacity = intenacity; }
	void SetSlowResist(const float inslow_resist) { slow_resist = inslow_resist; }
	void SetAbilityHaste(const float inability_haste) { ability_haste = inability_haste; }
	void SetMana(const float inmana) { mana = inmana; }
	void SetManaRegeneration(const float inmana_regeneration) { mana_regeneration = inmana_regeneration; }
	void SetMovementSpeed(const float inmovement_speed) { movement_speed = inmovement_speed; }
	void SetRange(const float inrange) { range = inrange; }

public:
	float GetArmorPenetration() const { return armor_penetration; }
	float GetAttackDamage() const { return attack_damage; }
	float GetAttackSpeed() const { return attack_speed; }
	float GetCriticalStrikeChance() const { return critical_strike_chance; }
	float GetCriticalStrikeDamage() const { return cirtical_strike_damage; }
	float GetLifeSteal() const { return life_steal; }
	float GetAbilityPower() const { return ability_power; }
	float GetMagePenetration() const { return mage_penetration; }
	float GetOmniVamp() const { return omnivamp; }
	float GetPhysicalVamp() const { return physical_vamp; }
	float GetArmor() const { return armor; }
	float GetHealAndShieldPower() const { return heal_and_shield_power; }
	float GetHealth() const { return health; }
	float GetHealthRegeneration() const { return health_regeneration; }
	float GetMagicResistance() const { return magic_resistance; }
	float GetTenacity() const { return tenacity; }
	float GetSlowResist() const { return slow_resist; }
	float GetAbilityHaste() const { return ability_haste; }
	float GetMana() const { return mana; }
	float GetManaRegeneration() const { return mana_regeneration; }
	float GetMovementSpeed() const { return movement_speed; }
	float GetRange() const { return range; }

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
	TArray<float> MaxFDataToFloat();
	TArray<float> CurrentFDataToFloat();
	void	MaxFloatToFData(TArray<float> Data);
	void	CurrentFloatToFData(TArray<float> Data);

	void UpdateMaxStats(ECharacterStatus InStats, float Invalue);
	void UpdateCurrentStats(ECharacterStatus InStats, float Invalue);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
		FStatsData 		mMaxStats;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
		FStatsData		mCurrentStats;
};

UCLASS()
class PROJECT_LD_API AStatsManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AStatsManager();
};
