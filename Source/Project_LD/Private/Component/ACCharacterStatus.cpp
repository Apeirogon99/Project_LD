// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ACCharacterStatus.h"
#include <Framework/Game/GM_Game.h>
#include <Widget/Handler/ClientHUD.h>
//#include "Blueprint/UserWidget.h"
#include <Widget/Game/Inventory/UWInventory.h>

// Sets default values for this component's properties
UACCharacterStatus::UACCharacterStatus()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	/*
	character_class_id = -1;

	//atttack
	base_attack_damage = 0;
	base_ability_power = 0;
	base_attack_speed = 0;
	base_critical_strike_chance = 0;
	base_cirtical_strike_damage = 0;
	base_armor_penetration = 0;
	base_mage_penetration = 0;
	base_ability_haste = 0;
	base_movement_speed = 0;
	base_range = 0;

	//defense
	base_armor = 0;
	base_tenacity = 0;
	base_magic_resistance = 0;
	base_slow_resist = 0;

	//life
	base_health = 0;
	base_health_regeneration = 0;
	base_life_steal = 0;
	base_physical_vamp = 0;
	base_omnivamp = 0;
	base_heal_and_shield_power = 0;
	
	//mana
	base_mana = 0;
	base_mana_regeneration = 0;
	*/
}


// Called when the game starts
void UACCharacterStatus::BeginPlay()
{
	Super::BeginPlay();
}

void UACCharacterStatus::UpdateStatusData(int32 Level)
{
	mLevel = Level;
	/*
	character_class_id = StatusData->character_class_id;

	//atttack
	base_attack_damage = StatusData->base_attack_damage + StatusGrowthData->grow_attack_damage * mLevel;
	base_ability_power = StatusData->base_ability_power + StatusGrowthData->grow_ability_power * mLevel;
	base_attack_speed = StatusData->base_attack_speed + StatusGrowthData->grow_attack_speed * mLevel;
	base_critical_strike_chance = StatusData->base_critical_strike_chance + StatusGrowthData->grow_critical_strike_chance * mLevel;
	base_cirtical_strike_damage = StatusData->base_cirtical_strike_damage + StatusGrowthData->grow_cirtical_strike_damage * mLevel;
	base_armor_penetration = StatusData->base_armor_penetration + StatusGrowthData->grow_armor_penetration * mLevel;
	base_mage_penetration = StatusData->base_mage_penetration + StatusGrowthData->grow_mage_penetration * mLevel;
	base_ability_haste = StatusData->base_ability_haste + StatusGrowthData->grow_ability_haste * mLevel;
	base_movement_speed = StatusData->base_movement_speed + StatusGrowthData->grow_movement_speed * mLevel;
	base_range = StatusData->base_range + StatusGrowthData->grow_range * mLevel;

	//defense
	base_armor = StatusData->base_armor + StatusGrowthData->grow_armor * mLevel;
	base_tenacity = StatusData->base_tenacity + StatusGrowthData->grow_tenacity * mLevel;
	base_magic_resistance = StatusData->base_magic_resistance + StatusGrowthData->grow_magic_resistance * mLevel;
	base_slow_resist = StatusData->base_slow_resist + StatusGrowthData->grow_slow_resist * mLevel;

	//life
	base_health = StatusData->base_health + StatusGrowthData->grow_health * mLevel;
	base_health_regeneration = StatusData->base_health_regeneration + StatusGrowthData->grow_health_regeneration * mLevel;
	base_life_steal = StatusData->base_life_steal + StatusGrowthData->grow_life_steal * mLevel;
	base_physical_vamp = StatusData->base_physical_vamp + StatusGrowthData->grow_physical_vamp * mLevel;
	base_omnivamp = StatusData->base_omnivamp + StatusGrowthData->grow_omnivamp * mLevel;
	base_heal_and_shield_power = StatusData->base_heal_and_shield_power + StatusGrowthData->grow_heal_and_shield_power * mLevel;

	//mana
	base_mana = StatusData->base_mana + StatusGrowthData->grow_mana * mLevel;
	base_mana_regeneration = StatusData->base_mana_regeneration + StatusGrowthData->grow_mana_regeneration * mLevel;

	UpdateWidgetStatusData();
	*/
}

void UACCharacterStatus::UpdateWidgetStatusData()
{
	/*
	UWorld* world = GetWorld();
	if (world == nullptr)
	{
		return;
	}
	AGM_Game* gamemode = Cast<AGM_Game>(world->GetAuthGameMode());
	if (gamemode == nullptr)
	{
		return;
	}
	AClientHUD* clientHUD = Cast<AClientHUD>(gamemode->GetClientHUD());
	if (nullptr == clientHUD)
	{
		return;
	}
	UUWInventory* inventoryWidget = Cast<UUWInventory>(clientHUD->GetWidgetFromName("Inventory"));

	inventoryWidget->
	*/
}

