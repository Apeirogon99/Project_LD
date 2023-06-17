// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkPlayerState.h"
#include <Framework/Game/GM_Game.h>
#include <Framework/Character/AppearanceCharacter.h>

ANetworkPlayerState::ANetworkPlayerState()
{
}

ANetworkPlayerState::~ANetworkPlayerState()
{
}

void ANetworkPlayerState::InitializeCharacterData(const FCharacterData& InCharacterDatas)
{
	mCharacterData = InCharacterDatas;

    AAppearanceCharacter* playerCharacter = Cast<AAppearanceCharacter>(GetPawn());
    playerCharacter->InitializeCharacter(mCharacterData);
    playerCharacter->InitializeAppearance();

    AGM_Game* gameMode = Cast<AGM_Game>(GetWorld()->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return;
    }

    AAppearanceCharacter* preivewCharacter = Cast<AAppearanceCharacter>(gameMode->GetPreviewCharacter());
    if (nullptr == preivewCharacter)
    {
        return;
    }
    preivewCharacter->InitializeCharacter(mCharacterData);
    preivewCharacter->InitializeAppearance();

}
