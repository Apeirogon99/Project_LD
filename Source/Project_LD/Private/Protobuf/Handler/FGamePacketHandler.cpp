#include "FGamePacketHandler.h"
#include <FCommonPacketHandler.h>

#include <Network/NetworkUtils.h>

#include <Framework/Controller/MovementController.h>

#include <Game/GM_Game.h>
#include <Game/C_Game.h>
#include <Game/NC_Game.h>
#include <Game/PC_Game.h>
#include <Game/NPC_Game.h>
#include <Game/PS_Game.h>
#include <Game/GS_Game.h>
#include <Framework/AnimInstance/AI_PlayerCharacter.h>

#include <GameContent/Enemy/EnemyController.h>
#include <GameContent/Enemy/EnemyState.h>
#include <GameContent/Enemy/EnemyBase.h>

#include <GameErrorTypes.h>

#include <Widget/Handler/ClientHUD.h>
#include <GameContent/Item/ItemParent.h>
#include <Widget/Game/Main/W_MainGame.h>

bool Handle_S2C_EnterGameServer(ANetworkController* controller, Protocol::S2C_EnterGameServer& pkt)
{

    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGM_Game* gameMode = Cast<AGM_Game>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }
    
    const Protocol::STransform& tempTransform = pkt.transform();
    const Protocol::SVector& tempLocation = tempTransform.location();
    const Protocol::SRotator& tempRotator = tempTransform.rotation();
    FVector location = FVector(tempLocation.x(), tempLocation.y(), tempLocation.z());
    FRotator rotator = FRotator(tempRotator.pitch(), tempRotator.yaw(), tempRotator.roll());

    const int64     newRemoteID = pkt.remote_id();
    FCharacterData  newCharacterData = pkt.character_data();

    AC_Game* newCharacter = Cast<AC_Game>(gameMode->SpawnCharacter(location, rotator));
    if (nullptr == newCharacter)
    {
        return false;
    }
    newCharacter->UpdateCharacterVisual(newCharacterData.GetAppearance(), newCharacterData.GetEquipment());
    newCharacter->InitCharacterAnimation();

    AAppearanceCharacter* preivewCharacter = Cast<AAppearanceCharacter>(gameState->GetPreviewCharacter());
    if (nullptr == preivewCharacter)
    {
        return false;
    }
    preivewCharacter->UpdateCharacterVisual(newCharacterData.GetAppearance(), newCharacterData.GetEquipment());
    preivewCharacter->UpdateCharacterPose(ECharacterPose::Idle);

    APawn* oldCharacter = controller->GetPawn();
    if (oldCharacter)
    {
        controller->UnPossess();
        oldCharacter->Destroy();
    }

    controller->Possess(newCharacter);

    APS_Game* playerState = Cast<APS_Game>(controller->PlayerState);
    if (nullptr == playerState)
    {
        return false;
    }
    playerState->InitializeLocalPlayerState();
    playerState->SetRemotePlayerID(newRemoteID);
    playerState->SetCharacterData(newCharacterData);

    //Load
    playerState->mInventoryComponent->LoadItem(pkt.item());
    playerState->mEquipmentComponent->LoadEquipment(pkt.eqipment());

    return true;
}

bool Handle_S2C_LeaveGameServer(ANetworkController* controller, Protocol::S2C_LeaveGameServer& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGM_Game* gameMode = Cast<AGM_Game>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    gameMode->RequestDisconnectServer();

    return true;
}

bool Handle_S2C_Tick(ANetworkController* controller, Protocol::S2C_Tick& pkt)
{
    return true;
}

bool Handle_S2C_AppearCharacter(ANetworkController* controller, Protocol::S2C_AppearCharacter& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }
    
    AGM_Game* gameMode = Cast<AGM_Game>(world->GetAuthGameMode());
    if(nullptr == gameMode)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    const int64                     newRemoteID             = pkt.remote_id();
    const int64                     lastMovementTimeStamp   = pkt.timestamp();
    FVector                         oldMovementLocation     = FVector(pkt.cur_location().x(), pkt.cur_location().y(), pkt.cur_location().z());
    FVector                         newMovementLocation     = FVector(pkt.move_location().x(), pkt.move_location().y(), pkt.move_location().z());
    FCharacterData                  characterData           = pkt.character_data();

    ANC_Game* character = Cast<ANC_Game>(gameState->CreateNPCCharacter(FVector::ZeroVector, FRotator::ZeroRotator, characterData, newRemoteID));
    if (nullptr == character)
    {
        return false;
    }
 
    ANPC_Game* npcController = Cast<ANPC_Game>(character->GetController());
    if (nullptr == npcController)
    {
        return false;
    }
    const int64 nowServerTimeStamp = controller->GetServerTimeStamp();
    const int64 durationTimeStamp = nowServerTimeStamp - lastMovementTimeStamp;
    npcController->NPCMoveDestination(oldMovementLocation, newMovementLocation, durationTimeStamp);

    return true;
}

bool Handle_S2C_DisAppearCharacter(ANetworkController* controller, Protocol::S2C_DisAppearCharacter& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }
    const int64 remoteID = pkt.remote_id();

    AController* remoteController = gameState->FindPlayerController(remoteID);
    if (nullptr == remoteController)
    {
        return true;
    }

    APawn* character = remoteController->GetPawn();
    if (character)
    {
        character->Destroy();
    }

    return true;
}

bool Handle_S2C_MovementCharacter(ANetworkController* controller, Protocol::S2C_MovementCharacter& pkt)
{
    FDateTime currentUtcTimeStamp = FDateTime::UtcNow();
    const int64 nowClientUtcTimeStamp = (currentUtcTimeStamp.ToUnixTimestamp() * 1000) + currentUtcTimeStamp.GetMillisecond();

    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGM_Game* gameMode = Cast<AGM_Game>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    const int64 remoteID = pkt.remote_id();
    AController* remoteController = gameState->FindPlayerController(remoteID);
    if (nullptr == remoteController)
    {
        return true;
    }

    const int64 lastMovementTimeStamp = pkt.timestamp();
    const int64 nowServerTimeStamp = controller->GetServerTimeStamp();
    const int64 durationTimeStamp = nowServerTimeStamp - lastMovementTimeStamp;

    FVector     oldMovementLocation = FVector(pkt.cur_location().x(), pkt.cur_location().y(), pkt.cur_location().z());
    FVector     newMovementLocation = FVector(pkt.move_location().x(), pkt.move_location().y(), pkt.move_location().z());

    if (gameMode->CompareNetworkController(remoteController))
    {
        AMovementController* movementController = Cast<AMovementController>(remoteController);
        if (nullptr == movementController)
        {
            return false;
        }
        movementController->MoveDestination(oldMovementLocation, newMovementLocation, durationTimeStamp);
    }
    else
    {
        ANPC_Game* npcController = Cast<ANPC_Game>(remoteController);
        if (nullptr == npcController)
        {
            return false;
        }
        npcController->NPCMoveDestination(oldMovementLocation, newMovementLocation, durationTimeStamp);
    }

    FDateTime oldUtcTimeStamp = FDateTime::UtcNow();
    const int64 oldClientUtcTimeStamp = (currentUtcTimeStamp.ToUnixTimestamp() * 1000) + currentUtcTimeStamp.GetMillisecond();

    //UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("MOVEMENT [SERVER::%lld] [CLIENT::%lld] [DURATION::%lld] [EXEC::%lld]"), lastMovementTimeStamp, nowServerTimeStamp, durationTimeStamp, nowClientUtcTimeStamp - oldClientUtcTimeStamp), ELogLevel::Warning);

    return true;
}

bool Handle_S2C_PlayAnimation(ANetworkController* controller, Protocol::S2C_PlayAnimation& pkt)
{
    return true;
}

bool Handle_S2C_PlayerAutoAttack(ANetworkController* controller, Protocol::S2C_PlayerAutoAttack& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGM_Game* gameMode = Cast<AGM_Game>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    const int64 remoteID = pkt.remote_id();
    AController* remoteController = gameState->FindPlayerController(remoteID);
    if (nullptr == remoteController)
    {
        return true;
    }

    AC_Game* player = Cast<AC_Game>(remoteController->GetPawn());
    if (nullptr == player)
    {
        return true;
    }
    Protocol::SRotator rotation = pkt.rotation();
    player->SetActorRotation(FRotator(rotation.pitch(), rotation.yaw(), rotation.roll()), ETeleportType::ResetPhysics);

    const int64 timeStamp           = pkt.timestamp();
    const int64 nowServerTimeStamp  = controller->GetServerTimeStamp();
    const int64 durationTimeStamp   = nowServerTimeStamp - timeStamp;
    const float millisecondDuration = durationTimeStamp / 1000.0f;

    const int32 combo = pkt.combo();

    UAI_PlayerCharacter* animInstance = Cast<UAI_PlayerCharacter>(player->GetMesh()->GetAnimInstance());
    if (nullptr == animInstance)
    {
        return true;
    }
    animInstance->JumpAttackMontageSection(combo, millisecondDuration);

    return true;
}

bool Handle_S2C_AppearItem(ANetworkController* controller, Protocol::S2C_AppearItem& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    const Protocol::SItem& curItem = pkt.item();
    int64 objectID          = curItem.object_id();
    int32 itemCode          = curItem.item_code();

    if (nullptr != gameState->FindGameObject(objectID))
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_AppearItem] ALREADY GameObject : %d"), objectID), ELogLevel::Error);
        return false;
    }

    const Protocol::SVector& itemPosition = curItem.world_position();
    FVector itemLocation = FVector(itemPosition.x(), itemPosition.y(), itemPosition.z());
    FRotator itemRotator = FRotator::ZeroRotator;

    AActor* newActor = gameState->CreateGameObject(AItemParent::StaticClass(), itemLocation, itemRotator, objectID);
    AItemParent* newItem = Cast<AItemParent>(newActor);
    if (nullptr == newItem)
    {
        return false;
    }
    newItem->Init(itemCode, objectID);
    
    return true;
}

bool Handle_S2C_AppearEnemy(ANetworkController* controller, Protocol::S2C_AppearEnemy& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    //PACKET
    const int64     objectID        = pkt.object_id();
    const int32     enemyID         = pkt.enemy_id();
    EEnemyStateType stateType       = StaticCast<EEnemyStateType>(pkt.state());
    auto            stats           = pkt.stats();
    FVector         curLocation     = FVector(pkt.cur_location().x(), pkt.cur_location().y(), pkt.cur_location().z());
    FVector         moveLocation    = FVector(pkt.move_location().x(), pkt.move_location().y(), pkt.move_location().z());
    const int64     timestamp       = pkt.timestamp();
    const int64     durationTime    = controller->GetServerTimeStamp() - timestamp;



    if (nullptr != gameState->FindGameObject(objectID))
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_AppearEnemy] ALREADY GameObject : %d"), objectID), ELogLevel::Error);
        return false;
    }


    AActor* newActor = gameState->CreateEnemyCharacter(enemyID, curLocation, FRotator::ZeroRotator, objectID);
    if (nullptr == newActor)
    {
        return false;
    }

    AEnemyBase* newEnemy = Cast<AEnemyBase>(newActor);
    if (nullptr == newEnemy)
    {
        return false;
    }

    AEnemyState* enemyState = newEnemy->GetPlayerState<AEnemyState>();
    if (nullptr == enemyState)
    {
        return false;
    }
    enemyState->SetEnemyState(stateType, durationTime / 1000.0f);
    enemyState->UpdateCurrentStats(stats);

    AEnemyController* enemyController = Cast<AEnemyController>(newEnemy->GetController());
    if (nullptr == enemyController)
    {
        return false;
    }
    enemyController->MoveDestination(curLocation, moveLocation, durationTime);

    newEnemy->Init();

    return true;
}

bool Handle_S2C_DetectChangeEnemy(ANetworkController* controller, Protocol::S2C_DetectChangeEnemy& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    const int64     objectID        = pkt.object_id();
    auto            stats           = pkt.stats();
    EEnemyStateType state           = StaticCast<EEnemyStateType>(pkt.state());
    const int64     timestamp       = pkt.timestamp();
    const int64     durationTime    = controller->GetServerTimeStamp() - timestamp;

    AActor* actor = gameState->FindGameObject(objectID);
    if (nullptr == actor)
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_AppearEnemy] INVALID GameObject : %d"), objectID), ELogLevel::Error);
        return false;
    }

    AEnemyBase* enemy = Cast<AEnemyBase>(actor);
    if (nullptr == enemy)
    {
        return false;
    }

    AEnemyState* enemyState = enemy->GetPlayerState<AEnemyState>();
    if (nullptr == enemyState)
    {
        return false;
    }
    enemyState->SetEnemyState(state, durationTime / 1000.0f);
    enemyState->UpdateCurrentStats(stats);

    return true;
}

bool Handle_S2C_MovementEnemy(ANetworkController* controller, Protocol::S2C_MovementEnemy& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    //Packet
    const int64     objectID        = pkt.object_id();
    FVector         curLocation     = FVector(pkt.cur_location().x(), pkt.cur_location().y(), pkt.cur_location().z());
    FVector         moveLocation    = FVector(pkt.move_location().x(), pkt.move_location().y(), pkt.move_location().z());
    const int64     timestamp       = pkt.timestamp();
    const int64     durationTime    = controller->GetServerTimeStamp() - timestamp;


    AActor* actor = gameState->FindGameObject(objectID);
    if (nullptr == actor)
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_AppearEnemy] INVALID GameObject : %d"), objectID), ELogLevel::Error);
        return false;
    }

    AEnemyBase* enemy = Cast<AEnemyBase>(actor);
    if (nullptr == enemy)
    {
        return false;
    }

    AEnemyController* enemyController = Cast<AEnemyController>(enemy->GetController());
    if (nullptr == enemyController)
    {
        return false;
    }
    enemyController->MoveDestination(curLocation, moveLocation, durationTime);

    return true;
}

bool Handle_S2C_EnemyAutoAttack(ANetworkController* controller, Protocol::S2C_EnemyAutoAttack& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    //Packet
    const int64     objectID        = pkt.object_id();
    const int64     timestamp       = pkt.timestamp();
    const int64     durationTime    = controller->GetServerTimeStamp() - timestamp;
    const FRotator  rotation        = FRotator(pkt.rotation().pitch(), pkt.rotation().yaw(), pkt.rotation().roll());

    AActor* actor = gameState->FindGameObject(objectID);
    if (nullptr == actor)
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_AppearEnemy] INVALID GameObject : %d"), objectID), ELogLevel::Error);
        return false;
    }

    AEnemyBase* enemy = Cast<AEnemyBase>(actor);
    if (nullptr == enemy)
    {
        return false;
    }
    enemy->SetActorRotation(rotation);

    //AEnemyState* enemyState = enemy->GetPlayerState<AEnemyState>();
    //if (nullptr == enemyState)
    //{
    //    return false;
    //}
    //enemyState->SetEnemyState(EEnemyStateType::State_Attack, durationTime / 1000.0f);

    return true;
}

bool Handle_S2C_HitEnemy(ANetworkController* controller, Protocol::S2C_HitEnemy& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    const int64     objectID        = pkt.object_id();
    const int64     timestamp       = pkt.timestamp();
    const int64     durationTime    = controller->GetServerTimeStamp() - timestamp;

    AActor* actor = gameState->FindGameObject(objectID);
    if (nullptr == actor)
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_AppearEnemy] INVALID GameObject : %d"), objectID), ELogLevel::Error);
        return false;
    }

    AEnemyBase* enemy = Cast<AEnemyBase>(actor);
    if (nullptr == enemy)
    {
        return false;
    }

    //AEnemyState* enemyState = enemy->GetPlayerState<AEnemyState>();
    //if (nullptr == enemyState)
    //{
    //    return false;
    //}
    //enemyState->SetEnemyState(EEnemyStateType::State_Hit, durationTime / 1000.0f);

    return true;
}

bool Handle_S2C_DeathEnemy(ANetworkController* controller, Protocol::S2C_DeathEnemy& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    const int64     objectID = pkt.object_id();
    const int64     timestamp = pkt.timestamp();
    const int64     durationTime = controller->GetServerTimeStamp() - timestamp;

    AActor* actor = gameState->FindGameObject(objectID);
    if (nullptr == actor)
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_AppearEnemy] INVALID GameObject : %d"), objectID), ELogLevel::Error);
        return false;
    }

    AEnemyBase* enemy = Cast<AEnemyBase>(actor);
    if (nullptr == enemy)
    {
        return false;
    }
    enemy->Destroy();
    //AEnemyState* enemyState = enemy->GetPlayerState<AEnemyState>();
    //if (nullptr == enemyState)
    //{
    //    return false;
    //}
    //enemyState->SetEnemyState(EEnemyStateType::State_Death, durationTime / 1000.0f);

    return true;
}

bool Handle_S2C_DisAppearGameObject(ANetworkController* controller, Protocol::S2C_DisAppearGameObject& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    const int64 objectID = pkt.object_id();
    AActor* gameObject = gameState->FindGameObject(objectID);
    if (nullptr == gameObject)
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_DisAppearGameObject] INVALID GameObject : %d"), objectID), ELogLevel::Error);
        return true;
    }
 
    bool result = gameState->RemoveGameObject(objectID);
    //UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_DisAppearGameObject] %ws Remove GameObject : %d"), ((result == true) ? TEXT("Success") : TEXT("Faild")), objectID), ELogLevel::Error);

    return true;
}

bool Handle_S2C_LoadInventory(ANetworkController* controller, Protocol::S2C_LoadInventory& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGM_Game* gameMode = Cast<AGM_Game>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    APC_Game* localController = Cast<APC_Game>(gameMode->GetNetworkController());
    if (nullptr == localController)
    {
        return false;
    }

    APS_Game* playerState = localController->GetPlayerState<APS_Game>();
    if (nullptr == playerState)
    {
        return false;
    }
   
    //Load
    playerState->mInventoryComponent->LoadItem(pkt.item());
    playerState->mEquipmentComponent->LoadEquipment(pkt.eqipment());

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("MainGame")));
    if (nullptr == widget)
    {
        return false;
    }

    UW_MainGame* mainGameWidget = Cast<UW_MainGame>(widget);
    if (nullptr == mainGameWidget)
    {
        return false;
    }

    mainGameWidget->InventoryOpenResponse();
    
    return true;
}

bool Handle_S2C_InsertInventory(ANetworkController* controller, Protocol::S2C_InsertInventory& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    int32 error = pkt.error();
    if (error != ErrorToInt(EGameErrorType::SUCCESS))
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_InsertInventory] InsertInventory Error : %d"), error), ELogLevel::Error);
        return true;
    }

    const int64 remoteID = pkt.remote_id();
    APC_Game* findController = Cast<APC_Game>(gameState->FindPlayerController(remoteID));
    if (nullptr == findController)
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_InsertInventory] INVALID RemotePlayer : %d"), remoteID), ELogLevel::Error);
        return true;
    }
    //TODO : 줍는 애니메이션

    //TODO : 아이템 삭제
    const int64 gameObjectID = pkt.object_id();
    if (false == gameState->RemoveGameObject(gameObjectID))
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_InsertInventory] INVALID Item in world : %d"), remoteID), ELogLevel::Error);
        return true;
    }
    
    return true;
}

bool Handle_S2C_UpdateInventory(ANetworkController* controller, Protocol::S2C_UpdateInventory& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    int32 error = pkt.error();
    if (error != ErrorToInt(EGameErrorType::SUCCESS))
    {

        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("UpdateInventory Error : %d"), error), ELogLevel::Error);

        Protocol::C2S_LoadInventory loadInventoryPacket;
        const int64 serverTimeStamp = controller->GetServerTimeStamp();
        loadInventoryPacket.set_timestamp(serverTimeStamp);
        controller->Send(FGamePacketHandler::MakeSendBuffer(controller, loadInventoryPacket));
    }

    return true;
}

bool Handle_S2C_DeleteInventory(ANetworkController* controller, Protocol::S2C_DeleteInventory& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    int32 error = pkt.error();
    if (error != ErrorToInt(EGameErrorType::SUCCESS))
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("DeleteInventory Error : %d"), error), ELogLevel::Error);
        return true;
    }

    const int64 remoteID = pkt.remote_id();
    APC_Game* gameController = Cast<APC_Game>(gameState->FindPlayerController(remoteID));
    if (nullptr == gameController)
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_DeleteInventory] INVALID RemotePlayer : %d"), remoteID), ELogLevel::Error);
        return true;
    }
    //TODO : 버리는 애니메이션

    //const Protocol::SItem& itemInfo = pkt.item();
    //AActor* actor = gameState->FindGameObject(itemInfo.object_id());
    //if (actor)
    //{
    //    return false;
    //}


    //const Protocol::SVector& worldPosition = itemInfo.world_position();

    //const int32 itemCode        = itemInfo.item_code();
    //const int64 gameObjectID    = itemInfo.object_id();
    //FVector itemLocation        = FVector(worldPosition.x(), worldPosition.y(), worldPosition.z());
    //FRotator itemRotator        = FRotator::ZeroRotator;

    //AActor* newActor = gameState->CreateGameObject(AItemParent::StaticClass(), itemLocation, itemRotator, gameObjectID);
    //AItemParent* newItem = Cast<AItemParent>(newActor);
    //if (nullptr == newItem)
    //{
    //    return false;
    //}
    //newItem->Init(itemCode, gameObjectID);

    return true;
}

bool Handle_S2C_RollbackInventory(ANetworkController* controller, Protocol::S2C_RollbackInventory& pkt)
{
    return true;
}

bool Handle_S2C_ReplaceEqipment(ANetworkController* controller, Protocol::S2C_ReplaceEqipment& pkt)
{
    const int32 error = pkt.error();
    if (0 != error)
    {

    }

    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    const int64 remoteID = pkt.remote_id();
    AController* remoteController = gameState->FindPlayerController(remoteID);
    if (nullptr == remoteController)
    {
        return true;
    }

    FCharacterEquipment updateEquipment = pkt.eqipment();

    APS_Game* playerState = Cast<APS_Game>(remoteController->PlayerState);
    if (nullptr == playerState)
    {
        return false;
    }
    playerState->SetCharacterEqipment(updateEquipment);
    playerState->calculationStats();

    AC_Game* character = Cast<AC_Game>(remoteController->GetPawn());
    if (nullptr == character)
    {
        return false;
    }
    character->UpdateCharacterEquipment(updateEquipment);
    character->UpdateDefaultAnimation();

    if (controller != remoteController)
    {
        return true;
    }

    AAppearanceCharacter* preivewCharacter = Cast<AAppearanceCharacter>(gameState->GetPreviewCharacter());
    if (nullptr == preivewCharacter)
    {
        return false;
    }
    preivewCharacter->UpdateCharacterEquipment(updateEquipment);
    preivewCharacter->UpdateCharacterPose(ECharacterPose::Idle);

    return true;
}