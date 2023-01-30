// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Identity/IdentityGameMode.h"
#include <Framework/Identity/IdentityPlayerController.h>
#include <Protobuf/Handler/IdentityClientPacketHandler.h>

AIdentityGameMode::AIdentityGameMode()
{
	
}

AIdentityGameMode::~AIdentityGameMode()
{
}

NetworkControllerPtr AIdentityGameMode::CreateDefaultPlayerController()
{
	return NetworkControllerPtr();
}
