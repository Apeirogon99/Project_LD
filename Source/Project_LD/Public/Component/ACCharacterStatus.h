// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Struct/Game/CharacterStatusData.h>
#include "ACCharacterStatus.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_LD_API UACCharacterStatus : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACCharacterStatus();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	//FStatusData* StatusData;
	//FStatusGrowthData* StatusGrowthData;

public:
	//int32 mLevel;

//	FStatusData* CharacterStaus;
	/*
	int32 character_class_id;

	//atttack
	int32 base_attack_damage;
	int32 base_ability_power;
	int32 base_attack_speed;
	int32 base_critical_strike_chance;
	int32 base_cirtical_strike_damage;
	int32 base_armor_penetration;
	int32 base_mage_penetration;
	int32 base_ability_haste;
	int32 base_movement_speed;
	int32 base_range;

	//defense
	int32 base_armor;
	int32 base_tenacity;
	int32 base_magic_resistance;
	int32 base_slow_resist;

	//life
	int32 base_health;
	int32 base_health_regeneration;
	int32 base_life_steal;
	int32 base_physical_vamp;
	int32 base_omnivamp;
	int32 base_heal_and_shield_power;

	//mana
	int32 base_mana;
	int32 base_mana_regeneration;
	*/
public:
	void UpdateStatusData(int32 Level);
	void UpdateWidgetStatusData();
};
