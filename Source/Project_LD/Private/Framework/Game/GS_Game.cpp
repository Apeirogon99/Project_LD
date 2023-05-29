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

AActor* AGS_Game::CreateGameObject(UClass* inUClass, FVector inLocation, FRotator inRotator, const int64 inGameObjectID)
{
    if (nullptr == inUClass)
    {
        return nullptr;
    }

    //TODO: GameState에서 이 자원을 가지고 있어야하고 빼는것도 가능해야함
    UWorld* world = GetWorld();
    if (world)
    {
        FActorSpawnParameters spawnParams;
        spawnParams.Owner = this;
        spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        AActor* gameObject = world->SpawnActor<AActor>(inUClass, inLocation, inRotator, spawnParams);

        mGameObjects.Add(inGameObjectID, gameObject);
        return gameObject;
    }

    return nullptr;
}

AActor* AGS_Game::FindGameObject(const int64 inGameObject)
{
    AActor** gameObject = mGameObjects.Find(inGameObject);
    if (nullptr == gameObject)
    {
        return nullptr;
    }

    return *gameObject;
}

int32 AGS_Game::RemoveGameObject(const int64 inGameObjectID)
{
    int32 result = mGameObjects.Remove(inGameObjectID);
    return result;
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
