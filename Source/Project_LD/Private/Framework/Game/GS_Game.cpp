// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/GS_Game.h"
#include <Game/C_Game.h>
#include <Game/NC_Game.h>
#include <Game/PC_Game.h>
#include <Game/NPC_Game.h>
#include <Game/PS_Game.h>
#include <Game/NPS_Game.h>
#include <Game/GM_Game.h>

#include <GameContent/Enemy/EnemyController.h>
#include <GameContent/Enemy/EnemyState.h>
#include <GameContent/Enemy/EnemyBase.h>

#include <GameContent/Enemy/Skill/Lich/Skill_LifeVessel.h>
#include <GameContent/Enemy/Skill/Lich/Skill_BlinkAttack.h>
#include <GameContent/Enemy/Skill/Lich/Skill_BlinkStun.h>
#include <GameContent/Enemy/Skill/Lich/Skill_Explosion.h>
#include <GameContent/Enemy/Skill/Lich/Skill_MultiCasting.h>
#include <GameContent/Enemy/Skill/Lich/Skill_OnslaughtOfShadows.h>
#include <GameContent/Enemy/Skill/Lich/Skill_RealmOfDeath.h>
#include <GameContent/Enemy/Skill/Lich/Skill_Rise.h>
#include <GameContent/Enemy/Skill/Lich/Skill_RiseSkeleton.h>
#include <GameContent/Enemy/Skill/Lich/Skill_RiseDarkKnight.h>
#include <GameContent/Enemy/Skill/Lich/Skill_SoulShackles.h>
#include <GameContent/Enemy/Skill/Lich/Skill_SoulSpark.h>
#include <GameContent/Enemy/Skill/Lich/Skill_SoulSpear.h>

#include <GameContent/Enemy/Skill/DarkKnight/DarkKnight_Berserk.h>
#include <GameContent/Enemy/Skill/DarkKnight/DarkKnight_ChargedComboAttack.h>
#include <GameContent/Enemy/Skill/DarkKnight/DarkKnight_HandSwordSwipeAttack.h>
#include <GameContent/Enemy/Skill/DarkKnight/DarkKnight_RunningAttack.h>
#include <GameContent/Enemy/Skill/DarkKnight/DarkKnight_SwingAndSlamAttack.h>
#include <GameContent/Enemy/Skill/DarkKnight/DarkKnight_SwingAttack.h>
#include <GameContent/Enemy/Skill/DarkKnight/DarkKnight_UppercutAttack.h>

#include <Framework/Gameinstance/LDGameInstance.h>
#include <Kismet/GameplayStatics.h>
#include <NetworkUtils.h>

AGS_Game::AGS_Game()
{

}

AGS_Game::~AGS_Game()
{
}

AActor* AGS_Game::CreateNPCCharacter(FVector inLocation, FRotator inRotator, FCharacterData& inCharacterData, const int64 inRemoteID)
{
    UWorld* world = GetWorld();
    if (nullptr == world)
    {
        return nullptr;
    }

    FActorSpawnParameters spawnParams;
    spawnParams.Owner = this;
    spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    TSubclassOf<ANC_Game> npcClass = LoadClass<ANC_Game>(nullptr, TEXT("Blueprint'/Game/Blueprint/Framework/Game/BNC_Game.BNC_Game_C'"));
    if (nullptr == npcClass)
    {
        return nullptr;
    }

    ANC_Game* newNPC = world->SpawnActor<ANC_Game>(npcClass, inLocation, inRotator, spawnParams);
    if (nullptr == newNPC)
    {
        return nullptr;
    }
    newNPC->UpdateCharacterVisual(inCharacterData.GetAppearance(), inCharacterData.GetEquipment());
    newNPC->InitCharacterAnimation();

    ANPC_Game* npcController = Cast<ANPC_Game>(newNPC->GetController());
    if (nullptr == npcController)
    {
        return false;
    }

    ANPS_Game* npcState = world->SpawnActor<ANPS_Game>();
    if (nullptr == npcState)
    {
        return nullptr;
    }
    npcState->SetRemotePlayerID(inRemoteID);
    npcState->SetCharacterData(inCharacterData);
    npcState->calculationStats();
    //npcState->InitCurrentStats();

    newNPC->SetPlayerState(npcState);
    npcController->PlayerState = npcState;

    AddPlayerState(npcState);

    UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("CreateNPCCharacter [REMOTE_ID::%lld] [PLAYER_STATE::%d]"), inRemoteID, PlayerArray.Num()), ELogLevel::Warning);

    return newNPC;
}

bool AGS_Game::RemoveNPCCharacter(const int64 inRemoteID)
{
    UWorld* world = GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AController* remoteController = FindPlayerController(inRemoteID);
    if (nullptr == remoteController)
    {
        return false;
    }

    ANPC_Game* npcController = Cast<ANPC_Game>(remoteController);
    if (nullptr == npcController)
    {
        return false;
    }
    npcController->UnPossess();

    ANPS_Game* npcState = world->SpawnActor<ANPS_Game>();
    if (nullptr == npcState)
    {
        return false;
    }
    RemovePlayerState(npcState);

    ANC_Game* character = Cast<ANC_Game>(remoteController->GetPawn());
    if (nullptr == character)
    {
        return false;
    }
    character->Destroy();
    world->DestroyActor(npcState);
    world->DestroyActor(npcController);

    UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("RemoveNPCCharacter [REMOTE_ID::%lld] [PLAYER_STATE::%d]"), inRemoteID, PlayerArray.Num()), ELogLevel::Warning);

    return true;
}

AActor* AGS_Game::CreateEnemyCharacter(const int32 inEnemyID, FVector inLocation, FRotator inRotator, const int64 inGameObjectID)
{
    UWorld* world = GetWorld();
    if (nullptr == world)
    {
        return nullptr;
    }

    ULDGameInstance* gameinstance = Cast<ULDGameInstance>(GetGameInstance());
    if (nullptr == gameinstance)
    {
        return nullptr;
    }

    FEnemyData*     enemyDatas = gameinstance->GetEnemyData(inEnemyID);
    FEnemyStatData* enemyStats = gameinstance->GetEnemyStatData(inEnemyID);

    FActorSpawnParameters spawnParams;
    spawnParams.Owner = this;
    spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    TSubclassOf<AEnemyBase> enemyClass = LoadClass<AEnemyBase>(nullptr, *enemyDatas->GetEnemyClassPath());
    if (nullptr == enemyClass)
    {
        return nullptr;
    }

    AEnemyBase* newEnemy = world->SpawnActor<AEnemyBase>(enemyClass, inLocation, inRotator, spawnParams);
    if (nullptr == newEnemy)
    {
        return nullptr;
    }

    AEnemyController* newEnemyController = Cast<AEnemyController>(newEnemy->GetController());
    if (nullptr == newEnemyController)
    {
        return nullptr;
    }

    AEnemyState* newEnemyState = world->SpawnActor<AEnemyState>();
    if (nullptr == newEnemyState)
    {
        return nullptr;
    }
    newEnemyState->SetObjectID(inGameObjectID);
    newEnemyState->SetEnemyDatas(*enemyDatas);
    newEnemyState->SetEnemyStats(*enemyStats);

    newEnemy->SetPlayerState(newEnemyState);
    newEnemyController->PlayerState = newEnemyState;

    mGameObjects.Add(inGameObjectID, newEnemy);
    AddPlayerState(newEnemyState);
    return newEnemy;
}

AActor* AGS_Game::CreateGameObject(UClass* inUClass, FVector inLocation, FRotator inRotator, const int64 inGameObjectID)
{
    if (nullptr == inUClass)
    {
        return nullptr;
    }

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
    if (result == 0)
    {
        return false;
    }

    return true;
}

AController* AGS_Game::FindPlayerController(const int64 inRemoteID)
{
    bool result = false;
    for (APlayerState* curPlayerState : PlayerArray)
    {
        if (nullptr == curPlayerState)
        {
            continue;
        }

        ANPS_Game* playerState = Cast<ANPS_Game>(curPlayerState);
        if (nullptr == playerState)
        {
            continue;
        }

        const int64& remoteID = playerState->GetRemoteID();
        if (remoteID != inRemoteID)
        {            
            continue;
        }

        APawn* pawn = playerState->GetPawn();
        if (nullptr == pawn)
        {
            continue;
        }

        AController* findController = pawn->GetController();
        if (nullptr == findController)
        {
            continue;
        }

        return findController;
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
