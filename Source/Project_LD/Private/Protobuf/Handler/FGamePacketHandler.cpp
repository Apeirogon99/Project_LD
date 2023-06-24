#include "FGamePacketHandler.h"
#include <FCommonPacketHandler.h>

#include <Network/NetworkUtils.h>

#include <Framework/Controller/MovementController.h>

#include <Game/GM_Game.h>
#include <Game/C_Game.h>
#include <Game/PC_Game.h>
#include <Game/PS_Game.h>
#include <Game/GS_Game.h>

#include <GameErrorTypes.h>

#include <Widget/Handler/ClientHUD.h>
#include <Widget/Game/Inventory/UWInventory.h>
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
    newCharacter->UpdateCharacterVisual(newCharacterData.mAppearance, newCharacterData.mEquipment);
    newCharacter->InitCharacterAnimation();
    newCharacter->UpdateDefaultAnimation();

    AAppearanceCharacter* preivewCharacter = Cast<AAppearanceCharacter>(gameState->GetPreviewCharacter());
    if (nullptr == preivewCharacter)
    {
        return false;
    }
    preivewCharacter->UpdateCharacterVisual(newCharacterData.mAppearance, newCharacterData.mEquipment);
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

    APS_Game* localPlayerState = Cast<APS_Game>(controller->PlayerState);
    if (nullptr == localPlayerState)
    {
        return false;
    }

    const int64 LocalRemoteID = localPlayerState->GetRemoteID();
    if (pkt.remote_id() == LocalRemoteID || LocalRemoteID == 0)
    {
        return true;
    }

    const int64                     newRemoteID             = pkt.remote_id();
    const int64                     lastMovementTimeStamp   = pkt.timestamp();
    FVector                         oldMovementLocation     = FVector(pkt.old_location().x(), pkt.old_location().y(), pkt.old_location().z());
    FVector                         newMovementLocation     = FVector(pkt.new_location().x(), pkt.new_location().y(), pkt.new_location().z());
    FCharacterData                  characterData           = pkt.character_data();

    AC_Game* character = Cast<AC_Game>(gameMode->SpawnCharacter(FVector::ZeroVector, FRotator::ZeroRotator));
    if (nullptr == character)
    {
        return false;
    }
    character->UpdateCharacterVisual(characterData.mAppearance, characterData.mEquipment);
    character->InitCharacterAnimation();
    character->UpdateDefaultAnimation();

    AController* newController = gameMode->CreateController();
    if (nullptr == newController)
    {
        return false;
    }
    newController->Possess(character);

    AMovementController* movementController = Cast<AMovementController>(newController);
    if (nullptr == movementController)
    {
        return false;
    }
    const int64 nowServerTimeStamp = controller->GetServerTimeStamp();
    const int64 durationTimeStamp = nowServerTimeStamp - lastMovementTimeStamp;
    movementController->MoveDestination(oldMovementLocation, newMovementLocation, durationTimeStamp);

    newController->InitPlayerState();
    APS_Game* playerState = newController->GetPlayerState<APS_Game>();
    if (nullptr == playerState)
    {
        return false;
    }
    playerState->SetRemotePlayerID(newRemoteID);
    playerState->SetCharacterData(characterData);

    character->SetPlayerState(playerState);

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
    if (nullptr == remoteController)
    {
        return true;
    }

    AMovementController* movementController = Cast<AMovementController>(remoteController);
    if (nullptr == movementController)
    {
        return false;
    }

    const int64 lastMovementTimeStamp = pkt.timestamp();
    const int64 nowServerTimeStamp = controller->GetServerTimeStamp();
    const int64 durationTimeStamp = nowServerTimeStamp - lastMovementTimeStamp;

    FVector     oldMovementLocation = FVector(pkt.old_location().x(), pkt.old_location().y(), pkt.old_location().z());
    FVector     newMovementLocation = FVector(pkt.new_location().x(), pkt.new_location().y(), pkt.new_location().z());

    movementController->MoveDestination(oldMovementLocation, newMovementLocation, durationTimeStamp);
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
    else
    {
        gameState->RemoveGameObject(objectID);
    }

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
    playerState->calculationStatus();

    AClientHUD* clientHUD = controller->GetHUD<AClientHUD>();
    if (nullptr == clientHUD)
    {
        return false;
    }

    UUserWidget* inventory = clientHUD->GetWidgetFromName(TEXT("Inventory"));
    if (inventory == nullptr)
    {
        return false;
    }
    Cast<UUWInventory>(inventory)->UpdateStatus();

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