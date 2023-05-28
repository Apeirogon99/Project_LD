// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PS_Game.h"

APS_Game::APS_Game()
{
	/**Character Status Setting**/

	//Attack Range
	mAttackRange = 200.0f;	mAttackRadius = 50.0f;
	//Attack Info
	mIsAttacking = false;
	//Health
	mMaxHealth = 100.0f;	mCurrentHealth = 100.0f;
	//Mana
	mMaxMana = 100.0f;		mCurrentMana = 100.0f;
	//Character Level
	mCharacterLevel = 1;

	mIsAttacking = false;
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
