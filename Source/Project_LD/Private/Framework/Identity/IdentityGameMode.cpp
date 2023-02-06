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

void AIdentityGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AIdentityGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AIdentityGameMode::BeginNetwork()
{
	Super::BeginNetwork();


}
