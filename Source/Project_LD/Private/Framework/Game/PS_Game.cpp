// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PS_Game.h"

APS_Game::APS_Game()
{
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
