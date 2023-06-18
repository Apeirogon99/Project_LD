// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/GS_Game.h"
#include <Game/C_Game.h>
#include <Game/PC_Game.h>
#include <Game/PS_Game.h>
#include <Game/GM_Game.h>

#include <Kismet/GameplayStatics.h>

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

bool AGS_Game::RemoveGameObject(const int64 inGameObjectID)
{
    AActor* findActor = FindGameObject(inGameObjectID);
    if (nullptr == findActor)
    {
        return false;
    }
    findActor->Destroy();
    
    int32 result = mGameObjects.Remove(inGameObjectID);
    if (result != 0)
    {
        return true;
    }

    return false;
}

AController* AGS_Game::FindPlayerController(const int64 inRemoteID)
{

    for (APlayerState* curPlayerState : PlayerArray)
    {
        APS_Game* playerState = Cast<APS_Game>(curPlayerState);
        if (playerState)
        {
            if (playerState->GetRemoteID() == inRemoteID)
            {
                return playerState->GetPawn()->GetController();
            }
        }
    }

    return nullptr;
}

AAppearanceCharacter* AGS_Game::GetPreviewCharacter()
{
    UWorld* world = GetWorld();
    if (nullptr == world)
    {
        return nullptr;
    }

    static TSubclassOf<AAppearanceCharacter> dummyClass = LoadClass<AAppearanceCharacter>(NULL, TEXT("Blueprint'/Game/Blueprint/Widget/Game/Inventory/PreView/BP_PreViewCharacter.BP_PreViewCharacter_C'"));

    AAppearanceCharacter* oldDummy = Cast<AAppearanceCharacter>(UGameplayStatics::GetActorOfClass(world, dummyClass));
    if (oldDummy)
    {
        return oldDummy;
    }

    FActorSpawnParameters spawnParams;
    spawnParams.Owner = this;
    spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    AAppearanceCharacter* newDummyCharacter = world->SpawnActor<AAppearanceCharacter>(dummyClass, FVector(0.0f, 0.0f, -1000.0f), FRotator::ZeroRotator, spawnParams);

    return newDummyCharacter;
}
