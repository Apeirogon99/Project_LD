#include "FGamePacketHandler.h"

#include <Framework/Controller/MovementController.h>

#include <Game/GM_Game.h>
#include <Game/C_Game.h>
#include <Game/PC_Game.h>
#include <Game/PS_Game.h>
#include <Game/GS_Game.h>

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

    return true;
}

bool Handle_S2C_LeaveGameServer(ANetworkController* controller, Protocol::S2C_LeaveGameServer& pkt)
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

    const int64 remoteID = pkt.remoteid();
    AController* remoteController = gameState->FindPlayerController(remoteID);

    AMovementController* movementController = StaticCast<AMovementController*>(remoteController);
    Protocol::STransform* transform = pkt.mutable_transform();
    Protocol::SVector* position = transform->mutable_position();

    FVector newDestination;
    newDestination.Set(position->x(), position->y(), position->z());

    movementController->MoveDestination(newDestination);
    return true;
}

bool Handle_S2C_InsertInventory(ANetworkController* controller, Protocol::S2C_InsertInventory& pkt)
{
    return true;
}

bool Handle_S2C_UpdateInventory(ANetworkController* controller, Protocol::S2C_UpdateInventory& pkt)
{
    return true;
}

bool Handle_S2C_DeleteInventory(ANetworkController* controller, Protocol::S2C_DeleteInventory& pkt)
{
    return true;
}