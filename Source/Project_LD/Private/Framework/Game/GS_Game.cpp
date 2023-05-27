// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/GS_Game.h"
#include <Game/C_Game.h>
#include <Game/PC_Game.h>
#include <Game/PS_Game.h>
#include <Game/GM_Game.h>

AGS_Game::AGS_Game()
{
}

AGS_Game::~AGS_Game()
{
}

AController* AGS_Game::FindPlayerController(const int64 inRemoteID)
{

    for (APlayerState* curPlayerState : PlayerArray)
    {
        APS_Game* playerState = Cast<APS_Game>(curPlayerState);
        if (playerState)
        {
            if (playerState->mRemoteID == inRemoteID)
            {
                return playerState->GetPawn()->GetController();
            }
        }
    }

    return nullptr;
}
