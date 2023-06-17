// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkPlayerState.h"

ANetworkPlayerState::ANetworkPlayerState()
{
}

ANetworkPlayerState::~ANetworkPlayerState()
{
}

void ANetworkPlayerState::InitializeCharacterData(const FCharacterData& InCharacterDatas)
{
	mCharacterData = InCharacterDatas;
}
