// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PS_Game.h"

APS_Game::APS_Game()
{
	/**Character Status Setting**/

	//Attack Range
	AttackRange = 200.0f;	AttackRadius = 50.0f;
	//Attack Info
	IsAttacking = false;
	//Health
	MaxHealth = 100.0f;	CurrentHealth = 100.0f;
	//Mana
	MaxMana = 100.0f;		CurrentMana = 100.0f;
	//Character Level
	CharacterLevel = 1;

	IsAttacking = false;
}

APS_Game::~APS_Game()
{
}

void APS_Game::Init(const int64 inRemoteID)
{
	mRemoteID = inRemoteID;
}

int64 APS_Game::GetRemoteID()
{
	return mRemoteID;
}
