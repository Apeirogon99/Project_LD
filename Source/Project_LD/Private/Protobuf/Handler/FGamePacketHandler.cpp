#include "FGamePacketHandler.h"
#include <FCommonPacketHandler.h>

#include <Framework/Controller/MovementController.h>

#include <Game/GM_Game.h>
#include <Game/C_Game.h>
#include <Game/PC_Game.h>
#include <Game/PS_Game.h>
#include <Game/GS_Game.h>

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

    FVector location = FVector(0, 0, 200.0f);
    FVector velocity = FVector();
    FRotator rotator = FRotator::ZeroRotator;

    AC_Game* newCharacter = Cast<AC_Game>(gameMode->SpawnCharacter(location, velocity, rotator));
    if (nullptr == newCharacter)
    {
        return false;
    }

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

    const int64 newRemoteID = pkt.remote_id();
    playerState->Init(newRemoteID);

    Protocol::C2S_ReplicatedServerTimeStamp timePacket;
    SendBufferPtr pakcetBuffer = FCommonPacketHandler::MakeSendBuffer(controller, timePacket);
    controller->Send(pakcetBuffer);

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

    FVector location = FVector(0, 0, 200.0f);
    FVector velocity = FVector();
    FRotator rotator = FRotator::ZeroRotator;

    AC_Game* character = Cast<AC_Game>(gameMode->SpawnCharacter(location, velocity, rotator));
    if (nullptr == character)
    {
        return false;
    }
    character->SpawnDefaultController();

    AController* aiController = character->GetController();
    aiController->InitPlayerState();
    APS_Game* playerState = aiController->GetPlayerState<APS_Game>();
    if (nullptr == playerState)
    {
        return false;
    }

    const int64 newRemoteID = pkt.remote_id();
    character->SetPlayerState(playerState);
    playerState->Init(newRemoteID);

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    gameState->AddPlayerState(playerState);
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

    APlayerState* playerState = remoteController->GetPlayerState<APlayerState>();
    if (nullptr == playerState)
    {
        return false;
    }
    gameState->RemovePlayerState(playerState);
    playerState->Destroy();

    APawn* character = remoteController->GetPawn();
    if (character)
    {
        remoteController->UnPossess();
        character->Destroy();
    }

    remoteController->Destroy();

    return true;
}

bool Handle_S2C_MovementCharacter(ANetworkController* controller, Protocol::S2C_MovementCharacter& pkt)
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

    AMovementController* movementController = StaticCast<AMovementController*>(remoteController);
    Protocol::STransform* transform = pkt.mutable_transform();
    Protocol::SVector* position = transform->mutable_position();

    FVector newDestination;
    newDestination.Set(position->x(), position->y(), position->z());

    movementController->MoveDestination(newDestination);
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

    const int32 maxItemSize = pkt.item().size();
    for (int32 index = 0; index < maxItemSize; ++index)
    {
        const Protocol::SItem& curItem = pkt.item(index);
        int64 objectID          = curItem.object_id();
        int32 itemCode          = curItem.item_code();

        const Protocol::SVector& itemPosition = curItem.world_position();
        float worldPositionX    = itemPosition.x();
        float worldPositionY    = itemPosition.y();
        float worldPositionZ    = itemPosition.z();

        FVector itemLocation = FVector(worldPositionX, worldPositionY, worldPositionZ);
        FRotator itemRotator = FRotator::ZeroRotator;

        AItemParent* newItem = Cast<AItemParent>(gameState->CreateGameObject(AItemParent::StaticClass(), itemLocation, itemRotator, objectID));
        if (nullptr == newItem)
        {
            return false;
        }
        newItem->Init(itemCode, objectID);
    }

    return true;
}

bool Handle_S2C_DisAppearGameObject(ANetworkController* controller, Protocol::S2C_DisAppearGameObject& pkt)
{
    return true;
}

bool Handle_S2C_DestroyItem(ANetworkController* controller, Protocol::S2C_DestroyItem& pkt)
{
    return false;
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
   
    playerState->mInventoryComponent->ClearInventory();

    const int32 maxItemSize = pkt.item().size();
    for (int32 index = 0; index < maxItemSize; ++index)
    {
        const Protocol::SItem&      curItem         = pkt.item(index);
        int64	                    objectID        = curItem.object_id();
        int32	                    itemCode        = curItem.item_code();

        const Protocol::SVector2D&  invenPosition   = curItem.inven_position();
        int32                       positionX       = invenPosition.x();
        int32                       positionY       = invenPosition.y();
        int32                       rotation        = curItem.rotation();

        playerState->mInventoryComponent->LoadItem(objectID, itemCode, positionX, positionY, rotation);
    }

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

    const int64 remoteID = pkt.remote_id();
    const int64 objectID = pkt.object_id();

    AActor* gameObject = gameState->FindGameObject(objectID);
    if (nullptr == gameObject)
    {
        return false;
    }

    AItemParent* item = Cast<AItemParent>(gameObject);
    item->ItemDestroy();

    gameState->RemoveGameObject(objectID);

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
    //TODO: if()

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

    const int32 error = pkt.error();
    if (0 != error)
    {

    }

    const int64 remoteID = pkt.remote_id();
    APC_Game* gameController = Cast<APC_Game>(gameState->FindPlayerController(remoteID));
    if (nullptr == gameController)
    {
        return false;
    }

    const Protocol::SItem& itemInfo = pkt.item();
    const Protocol::SVector& worldPosition = itemInfo.world_position();

    const int32 itemCode        = itemInfo.item_code();
    const int64 gameObjectID    = itemInfo.object_id();
    FVector itemLocation        = FVector(worldPosition.x(), worldPosition.y(), worldPosition.z());
    FRotator itemRotator        = FRotator::ZeroRotator;

    AItemParent* newItem = Cast<AItemParent>(gameState->CreateGameObject(AItemParent::StaticClass(), itemLocation, itemRotator, gameObjectID));
    if (nullptr == newItem)
    {
        return false;
    }
    newItem->Init(itemCode, gameObjectID);

    return true;
}

bool Handle_S2C_RollbackInventory(ANetworkController* controller, Protocol::S2C_RollbackInventory& pkt)
{
    return true;
}