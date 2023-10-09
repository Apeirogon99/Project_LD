#include "FGamePacketHandler.h"
#include <FCommonPacketHandler.h>

#include <Network/NetworkUtils.h>
#include <WidgetUtils.h>
#include <PacketUtils.h>

#include <Framework/AnimInstance/AI_PlayerCharacter.h>
#include <Framework/Controller/MovementController.h>
#include <GameContent/Projectile/LineProjectile.h>

#include <Game/GM_Game.h>
#include <Game/C_Game.h>
#include <Game/NC_Game.h>
#include <Game/PC_Game.h>
#include <Game/NPC_Game.h>
#include <Game/PS_Game.h>
#include <Game/GS_Game.h>

#include <Dungeon/GM_Dungeon.h>

#include <GameContent/Enemy/Skill/EnemySkillManager.h>
#include <GameContent/Enemy/Skill/EnemySkillInterface.h>

#include <GameContent/Portal/Portal.h>
#include <GameContent/Enemy/EnemyController.h>
#include <GameContent/Enemy/EnemyState.h>
#include <GameContent/Enemy/EnemyBase.h>
#include <GameContent/Enemy/E_Lich.h>
#include <GameContent/Enemy/LichAnimInstance.h>
#include <GameContent/Enemy/E_DarkKnight.h>
#include <GameContent/Enemy/DarkKnightAnimInstance.h>
#include <GameContent/Projectile/ArcherSkeletonArrow.h>

#include <GameContent/Item/ItemParent.h>
#include <Widget/Handler/ClientHUD.h>
#include <Widget/Game/Main/W_MainGame.h>
#include <Widget/Game/Party/W_PartyMain.h>

#include "CommonErrorTypes.h"
#include <GameErrorTypes.h>

#include <GameContent/Obstruction/ObstructionBase.h>

#include <Framework/Debug/Debug_Box.h>
#include <Framework/Debug/Debug_Circle.h>

bool Handle_S2C_EnterGameServer(ANetworkController* controller, Protocol::S2C_EnterGameServer& pkt)
{

    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
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

    FActorSpawnParameters spawnParams;
    spawnParams.Owner = gameMode;
    spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    AC_Game* newCharacter = world->SpawnActor<AC_Game>(gameMode->DefaultPawnClass, location, rotator, spawnParams);
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
    preivewCharacter->UpdateCharacterPose(ECharacterPose::Idle, true);

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
    playerState->mInventoryComponent->LoadItem(pkt.item(), pkt.money());
    playerState->mEquipmentComponent->LoadEquipment(pkt.eqipment());

    playerState->InitializeLocalPlayerData();

    gameMode->GetClientHUD()->FadeOut();
    return true;
}

bool Handle_S2C_LeaveGameServer(ANetworkController* controller, Protocol::S2C_LeaveGameServer& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
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
    
    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
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

    FVector	direction = newMovementLocation - oldMovementLocation;

    ANC_Game* character = Cast<ANC_Game>(gameState->CreateNPCCharacter(oldMovementLocation, direction.Rotation(), characterData, newRemoteID));
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

    ANPS_Game* playerState = npcController->GetPlayerState<ANPS_Game>();
    if (nullptr == playerState)
    {
        return false;
    }

    const int32 indexSize = pkt.stats_size();
    for (int32 index = 0; index < indexSize; ++index)
    {
        const Protocol::SStat& stat = pkt.stats().Get(index);
        playerState->GetCharacterStats().UpdateCurrentStats(StaticCast<ECharacterStatus>(stat.stat_type()), stat.stat_value());
    }
    playerState->InitCurrentEquipmentStats();

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

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
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

bool Handle_S2C_DetectChangePlayer(ANetworkController* controller, Protocol::S2C_DetectChangePlayer& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
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

    ANPS_Game* playerState = remoteController->GetPlayerState<ANPS_Game>();
    if (nullptr == playerState)
    {
        return true;
    }

    const int32 indexSize = pkt.stats_size();
    for (int32 index = 0; index < indexSize; ++index)
    {
        const Protocol::SStat& stat = pkt.stats().Get(index);
        playerState->GetCharacterStats().UpdateCurrentStats(StaticCast<ECharacterStatus>(stat.stat_type()), stat.stat_value());
    }
    playerState->UpdateCurrentStatsBar();

    return true;
}

bool Handle_S2C_PlayerAutoAttack(ANetworkController* controller, Protocol::S2C_PlayerAutoAttack& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
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

    ANC_Game* player = Cast<ANC_Game>(remoteController->GetPawn());
    if (nullptr == player)
    {
        return true;
    }
    Protocol::SRotator rotation = pkt.rotation();
    player->SetActorRotation(FRotator(rotation.pitch(), rotation.yaw(), rotation.roll()), ETeleportType::ResetPhysics);

    FVector location = FVector(pkt.location().x(), pkt.location().y(), pkt.location().z());

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

    if (gameMode->CompareNetworkController(remoteController))
    {
        AMovementController* movementController = Cast<AMovementController>(remoteController);
        if (nullptr == movementController)
        {
            return false;
        }
        movementController->StopMovementController(location);
    }
    else
    {
        ANPC_Game* npcController = Cast<ANPC_Game>(remoteController);
        if (nullptr == npcController)
        {
            return false;
        }
        npcController->StopMovementController(location);
    }

    return true;
}

bool Handle_S2C_PlayerEndAutoAttack(ANetworkController* controller, Protocol::S2C_PlayerEndAutoAttack& pkt)
{
    UE_LOG(LogTemp, Warning, TEXT("Handle_S2C_PlayerEndAutoAttack"));

    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
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

    ANC_Game* player = Cast<ANC_Game>(remoteController->GetPawn());
    if (nullptr == player)
    {
        return true;
    }

    player->ActiveMovement();
    player->SetCanMove(true);
    player->SetUsingSkill(false);

    return true;
}

bool Handle_S2C_UpdateExperience(ANetworkController* controller, Protocol::S2C_UpdateExperience& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
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

    if (false  == gameMode->CompareNetworkController(remoteController))
    {
        return true;
    }

    //TODO: 경험치 증가
    APS_Game* playerState = remoteController->GetPlayerState<APS_Game>();
    if (nullptr == playerState)
    {
        return false;
    }

    playerState->UpdateExpValue(pkt.experience());

    return true;
}

bool Handle_S2C_LevelUp(ANetworkController* controller, Protocol::S2C_LevelUp& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
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

    APS_Game* playerState = remoteController->GetPlayerState<APS_Game>();
    if (nullptr == playerState)
    {
        return false;
    }

    ANC_Game* character = Cast<ANC_Game>(remoteController->GetCharacter());
    if (nullptr == character)
    {
        return false;
    }

    character->ShowLevelUpParticle();

    //TODO: 레벨업
    playerState->GetCharacterData().SetLevel(pkt.level());

    if (false == gameMode->CompareNetworkController(remoteController))
    {
        return true;
    }

    //TODO: 경험치 증가
    playerState->UpdateExpValue(pkt.experience());

    return true;
}

bool Handle_S2C_Chat(ANetworkController* controller, Protocol::S2C_Chat& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(controller->GetHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    FString playerName  = UNetworkUtils::ConvertFString(pkt.name());
    FString message     = UNetworkUtils::ConvertFString(pkt.message());
    int32   chatType      = static_cast<int32>(pkt.chat_type());

    //채팅창
    bool ret = UWidgetUtils::SetChatWidget(clientHUD, playerName, message, chatType);
    if (ret == false)
    {
        return false;
    }
    
    //캐릭터 UI
    const int64 remoteID = pkt.remote_id();
    AController* remoteController = gameState->FindPlayerController(remoteID);
    if (nullptr == remoteController)
    {
        return true;
    }

    ANC_Game* character = Cast<ANC_Game>(remoteController->GetPawn());
    if (nullptr == character)
    {
        return false;
    }

    const int64 timeStamp = pkt.timestamp();
    const int64 durationTime = controller->GetServerTimeStamp() - timeStamp;
    character->ShowWorldChat(playerName, message, durationTime / 1000.0f);

    return true;
}

bool Handle_S2C_LoadFriendList(ANetworkController* controller, Protocol::S2C_LoadFriendList& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
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

    mainGameWidget->FriendOpenResponse(pkt.friends(), pkt.list_type());
    return true;
}

bool Handle_S2C_RequestFriend(ANetworkController* controller, Protocol::S2C_RequestFriend& pkt)
{
    AClientHUD* clientHUD = Cast<AClientHUD>(controller->GetHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));

    FString title;
    FString description;
    FString buttonText = TEXT("확인");

    int32 error = pkt.error();
    if (error != GetDatabaseErrorToInt(EDCommonErrorType::SUCCESS))
    {
        title = TEXT("친구 요청 실패");
        description = UNetworkUtils::GetNetworkErrorToString(error);
    }
    else
    {
        if (pkt.action() == 1)
        {
            title = TEXT("요청 성공");
            description = TEXT("요청에 성공하였습니다.");
        }
        else
        {
            title = TEXT("요청 응답 성공");
            description = TEXT("요청 응답에 성공하였습니다.");
        }
    }

    FNotificationDelegate notificationDelegate;
    notificationDelegate.BindLambda([=]()
        {
            clientHUD->CleanWidgetFromName(TEXT("Notification"));
        });

    bool ret = UWidgetUtils::SetNotification(clientHUD, title, description, buttonText, notificationDelegate);
    if (ret == false)
    {
        return false;
    }

    return true;
}

bool Handle_S2C_BlockFriend(ANetworkController* controller, Protocol::S2C_BlockFriend& pkt)
{
    AClientHUD* clientHUD = Cast<AClientHUD>(controller->GetHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));

    FString title;
    FString description;
    FString buttonText = TEXT("확인");

    int32 error = pkt.error();
    if (error != GetDatabaseErrorToInt(EDCommonErrorType::SUCCESS))
    {
        title = TEXT("친구 차단 실패");
        description = UNetworkUtils::GetNetworkErrorToString(error);
    }
    else
    {
        if (pkt.action() == 1)
        {
            title = TEXT("차단 성공");
            description = TEXT("차단에 성공하였습니다.");
        }
        else
        {
            title = TEXT("차단 해제 성공");
            description = TEXT("차단 해제에 성공하였습니다.");
        }
    }

    FNotificationDelegate notificationDelegate;
    notificationDelegate.BindLambda([=]()
        {
            clientHUD->CleanWidgetFromName(TEXT("Notification"));
        });

    bool ret = UWidgetUtils::SetNotification(clientHUD, title, description, buttonText, notificationDelegate);
    if (ret == false)
    {
        return false;
    }

    return true;
}

bool Handle_S2C_ConnectFriend(ANetworkController* controller, Protocol::S2C_ConnectFriend& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
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
   
    const FString playerName = UNetworkUtils::ConvertFString(pkt.nick_name());
    mainGameWidget->FriendNotifyGame(playerName, true);
    return true;
}

bool Handle_S2C_DisConnectFriend(ANetworkController* controller, Protocol::S2C_DisConnectFriend& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
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

    const FString playerName = UNetworkUtils::ConvertFString(pkt.nick_name());
    mainGameWidget->FriendNotifyGame(playerName, false);
    return true;
}

bool Handle_S2C_CreateParty(ANetworkController* controller, Protocol::S2C_CreateParty& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    APS_Game* playerState = Cast<APS_Game>(controller->PlayerState);
    if (nullptr == playerState)
    {
        return false;
    }
    FCharacterData& characterData = playerState->GetCharacterData();

    clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));

    int32 error = pkt.error();
    if (error != GetDatabaseErrorToInt(EDCommonErrorType::SUCCESS))
    {

        FNotificationDelegate notificationDelegate;
        notificationDelegate.BindLambda([=]()
            {
                clientHUD->CleanWidgetFromName(TEXT("Notification"));
            });

        bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("파티 생성 실패"), UNetworkUtils::GetNetworkErrorToString(error), TEXT("확인"), notificationDelegate);
        if (ret == false)
        {
            return false;
        }

        return true;
    }

    {
        playerState->GetPartyComponent()->CreateParty();
    }

    {
        
        UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("PartyMain")));
        if (nullptr == widget)
        {
            return false;
        }

        UW_PartyMain* partyMainWidget = Cast<UW_PartyMain>(widget);
        if (nullptr == partyMainWidget)
        {
            return false;
        }

        partyMainWidget->PushPlayerList(playerState->GetRemoteID(), playerState->GetRemoteID(), characterData.GetLevel(), StaticCast<int32>(characterData.GetClass()), characterData.GetName(), true);
    }

    {
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

        mainGameWidget->PushPartyPlayerInfo(playerState->GetRemoteID(), playerState->GetRemoteID(), characterData.GetLevel(), StaticCast<int32>(characterData.GetClass()), characterData.GetName(), true);
    }

    return true;
}

bool Handle_S2C_RequestEnterParty(ANetworkController* controller, Protocol::S2C_RequestEnterParty& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    APS_Game* playerState = Cast<APS_Game>(controller->PlayerState);
    if (nullptr == playerState)
    {
        return false;
    }
    FCharacterData& characterData = playerState->GetCharacterData();

    clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));

    int32 error = pkt.error();
    if (error != GetDatabaseErrorToInt(EDCommonErrorType::SUCCESS))
    {
        FNotificationDelegate notificationDelegate;
        notificationDelegate.BindLambda([=]()
            {
                clientHUD->CleanWidgetFromName(TEXT("Notification"));
            });

        bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("파티 요청 실패"), UNetworkUtils::GetNetworkErrorToString(error), TEXT("확인"), notificationDelegate);
        if (ret == false)
        {
            return false;
        }

    }
    else
    {
        FNotificationDelegate notificationDelegate;
        notificationDelegate.BindLambda([=]()
            {
                clientHUD->CleanWidgetFromName(TEXT("Notification"));
            });

        bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("파티 요청 성공"), TEXT("파티를 요청하였습니다."), TEXT("확인"), notificationDelegate);
        if (ret == false)
        {
            return false;
        }

    }

    return true;
}

bool Handle_S2C_RequestParty(ANetworkController* controller, Protocol::S2C_RequestParty& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    int64   remoteID = pkt.remote_id();
    int32   level = pkt.level();
    int32   characterClass = static_cast<int32>(pkt.character_class());
    FString name = UNetworkUtils::ConvertFString(pkt.nick_name());

    {
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
        mainGameWidget->PartyNotifyGame(name, 1);
    }


    {
        UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("PartyMain")));
        if (nullptr == widget)
        {
            return false;
        }

        UW_PartyMain* partyMainWidget = Cast<UW_PartyMain>(widget);
        if (nullptr == partyMainWidget)
        {
            return false;
        }
        partyMainWidget->PushRequestList(remoteID, level, characterClass, name);

        ANC_Game* player =  Cast<ANC_Game>(controller->GetCharacter());
        if (nullptr == player)
        {
            return false;
        }

        player->ReplaceIconParty();

        return true;
    }
}

bool Handle_S2C_RequestLeaveParty(ANetworkController* controller, Protocol::S2C_RequestLeaveParty& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    APS_Game* playerState = Cast<APS_Game>(controller->PlayerState);
    if (nullptr == playerState)
    {
        return false;
    }
    FCharacterData& characterData = playerState->GetCharacterData();

    clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));

    int32 error = pkt.error();
    if (error != GetDatabaseErrorToInt(EDCommonErrorType::SUCCESS))
    {
        FNotificationDelegate notificationDelegate;
        notificationDelegate.BindLambda([=]()
            {
                clientHUD->CleanWidgetFromName(TEXT("Notification"));
            });

        bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("파티 탈퇴 실패"), UNetworkUtils::GetNetworkErrorToString(error), TEXT("확인"), notificationDelegate);
        if (ret == false)
        {
            return false;
        }

        return true;
    }
    else
    {
        FString causeString;
        switch (pkt.cause())
        {
        case 0:
            causeString = TEXT("강제 퇴장 하였습니다.");
            break;
        case 1:
            causeString = TEXT("강제 퇴장 당하셨습니다.");
            break;
        case 2:
            causeString = TEXT("권한을 위임하고 탈퇴 하였습니다.");
            break;
        case 3:
            causeString = TEXT("파티를 탈퇴 하였습니다.");
            break;
        default:
            causeString = TEXT("알 수 없는 에러.");
            break;
        }

        FNotificationDelegate notificationDelegate;
        notificationDelegate.BindLambda([=]()
            {
                clientHUD->CleanWidgetFromName(TEXT("Notification"));
            });

        bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("파티 탈퇴 성공"), causeString, TEXT("확인"), notificationDelegate);
        if (ret == false)
        {
            return false;
        }

        if (pkt.cause() != 0)
        {
            {
                UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("PartyMain")));
                if (nullptr == widget)
                {
                    return false;
                }

                UW_PartyMain* partyMainWidget = Cast<UW_PartyMain>(widget);
                if (nullptr == partyMainWidget)
                {
                    return false;
                }

                partyMainWidget->ClearPlayerList();
            }

            {
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

                mainGameWidget->ClearPartyPlayerInfo();
            }

            {
                playerState->GetPartyComponent()->ClearParty();
            }

            {
                ANC_Game* player = Cast<ANC_Game>(controller->GetCharacter());
                if (nullptr == player)
                {
                    return false;
                }

                player->ReplaceIconOtherPlayer();
            }
        }
    }

    return true;
}

bool Handle_S2C_RequestLeaderParty(ANetworkController* controller, Protocol::S2C_RequestLeaderParty& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    APS_Game* playerState = Cast<APS_Game>(controller->PlayerState);
    if (nullptr == playerState)
    {
        return false;
    }

    clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));

    int32 error = pkt.error();
    if (error != GetDatabaseErrorToInt(EDCommonErrorType::SUCCESS))
    {
        FNotificationDelegate notificationDelegate;
        notificationDelegate.BindLambda([=]()
            {
                clientHUD->CleanWidgetFromName(TEXT("Notification"));
            });

        bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("파티 권한 위임 실패"), UNetworkUtils::GetNetworkErrorToString(error), TEXT("확인"), notificationDelegate);
        if (ret == false)
        {
            return false;
        }

    }
    else
    {
        FNotificationDelegate notificationDelegate;
        notificationDelegate.BindLambda([=]()
            {
                clientHUD->CleanWidgetFromName(TEXT("Notification"));
            });

        bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("파티 권한 위임 성공"), TEXT("파티 권환을 양도하였습니다."), TEXT("확인"), notificationDelegate);
        if (ret == false)
        {
            return false;
        }
    }

    return true;
}

bool Handle_S2C_ResponeParty(ANetworkController* controller, Protocol::S2C_ResponeParty& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    APS_Game* playerState = Cast<APS_Game>(controller->PlayerState);
    if (nullptr == playerState)
    {
        return false;
    }

    clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));

    int32 error = pkt.error();
    if (error != GetDatabaseErrorToInt(EDCommonErrorType::SUCCESS))
    {
        FNotificationDelegate notificationDelegate;
        notificationDelegate.BindLambda([=]()
            {
                clientHUD->CleanWidgetFromName(TEXT("Notification"));
            });

        bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("파티 응답 실패"), UNetworkUtils::GetNetworkErrorToString(error), TEXT("확인"), notificationDelegate);
        if (ret == false)
        {
            return false;
        }

    }
    else
    {

        FString description;
        if (pkt.action() == 2)
        {
            description = TEXT("파티 참가를 수락하였습니다");
        }
        else if(pkt.action() == 3)
        {
            description = TEXT("파티 참가를 거절하였습니다");
        }
        else
        {
            description = TEXT("알 수 없는 에러");
        }

        FNotificationDelegate notificationDelegate;
        notificationDelegate.BindLambda([=]()
            {
                clientHUD->CleanWidgetFromName(TEXT("Notification"));
            });

        bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("파티 응답 성공"), description, TEXT("확인"), notificationDelegate);
        if (ret == false)
        {
            return false;
        }

        {
            UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("PartyMain")));
            if (nullptr == widget)
            {
                return false;
            }

            UW_PartyMain* partyMainWidget = Cast<UW_PartyMain>(widget);
            if (nullptr == partyMainWidget)
            {
                return false;
            }
            partyMainWidget->ReleaseRequestList(pkt.remote_id());
        }

    }

    return true;
}

bool Handle_S2C_LoadParty(ANetworkController* controller, Protocol::S2C_LoadParty& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    APS_Game* playerState = Cast<APS_Game>(controller->PlayerState);
    if (nullptr == playerState)
    {
        return false;
    }

    int32 error = pkt.error();
    if (error != GetDatabaseErrorToInt(EDCommonErrorType::SUCCESS))
    {

        FNotificationDelegate notificationDelegate;
        notificationDelegate.BindLambda([=]()
            {
                clientHUD->CleanWidgetFromName(TEXT("Notification"));
            });

        bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("파티 로드 실패"), UNetworkUtils::GetNetworkErrorToString(error), TEXT("확인"), notificationDelegate);
        if (ret == false)
        {
            return false;
        }

        return true;
    }

    UW_PartyMain* partyMainWidget = Cast<UW_PartyMain>(clientHUD->GetWidgetFromName(FString(TEXT("PartyMain"))));
    if (nullptr == partyMainWidget)
    {
        return false;
    }
    partyMainWidget->ClearPlayerList();

    UW_MainGame* mainGameWidget = Cast<UW_MainGame>(clientHUD->GetWidgetFromName(FString(TEXT("MainGame"))));
    if (nullptr == mainGameWidget)
    {
        return false;
    }
    mainGameWidget->ClearPartyPlayerInfo();

    UACPartyComponent* partyComponent = playerState->GetPartyComponent();
    if (nullptr == partyComponent)
    {
        return false;
    }
    partyComponent->ClearParty();

    const int32 maxSize = pkt.remote_id_size();
    for (int32 index = 0; index < maxSize; ++index)
    {

        int64   remoteID        = pkt.mutable_remote_id()->Get(index);
        int32   level           = pkt.mutable_level()->Get(index);
        int32   characterClass  = static_cast<int32>(pkt.mutable_character_class()->Get(index));
        FString name            = UNetworkUtils::ConvertFString(pkt.mutable_nick_name()->Get(index));
        bool    isSelf          = remoteID == playerState->GetRemoteID();
        int64   leaderID        = pkt.leader_id();

        {
            partyMainWidget->PushPlayerList(remoteID, leaderID, level, characterClass, name, isSelf);
        }

        {
            mainGameWidget->PushPartyPlayerInfo(remoteID, leaderID, level, characterClass, name, isSelf);
        }

        {
            partyComponent->EnterParty(remoteID, level, characterClass, name);
        }
    }

    return true;
}

bool Handle_S2C_NotifyParty(ANetworkController* controller, Protocol::S2C_NotifyParty& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
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

    const FString playerName = UNetworkUtils::ConvertFString(pkt.nick_name());
    mainGameWidget->PartyNotifyGame(playerName, pkt.action());
    return true;
}

bool Handle_S2C_EnterPartyPlayer(ANetworkController* controller, Protocol::S2C_EnterPartyPlayer& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    APS_Game* playerState = Cast<APS_Game>(controller->PlayerState);
    if (nullptr == playerState)
    {
        return false;
    }


    int64   remoteID            = pkt.remote_id();
    int32   level               = pkt.level();
    int32   characterClass      = static_cast<int32>(pkt.character_class());
    FString name                = UNetworkUtils::ConvertFString(pkt.nick_name());
    bool    isSelf              = remoteID == playerState->GetRemoteID();
    int64   leaderID            = pkt.leader_id();

    {
        UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("PartyMain")));
        if (nullptr == widget)
        {
            return false;
        }

        UW_PartyMain* partyMainWidget = Cast<UW_PartyMain>(widget);
        if (nullptr == partyMainWidget)
        {
            return false;
        }

        partyMainWidget->PushPlayerList(remoteID, leaderID, level, characterClass, name, isSelf);
    }

    {
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

        mainGameWidget->PushPartyPlayerInfo(remoteID, leaderID, level, characterClass, name, isSelf);
    }

    {
        UACPartyComponent* partyComponent = playerState->GetPartyComponent();
        if (nullptr == partyComponent)
        {
            return false;
        }

        partyComponent->EnterParty(remoteID, level, characterClass, name);
    }

    return true;
}

bool Handle_S2C_LeavePartyPlayer(ANetworkController* controller, Protocol::S2C_LeavePartyPlayer& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    APS_Game* playerState = Cast<APS_Game>(controller->PlayerState);
    if (nullptr == playerState)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    {
        UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("PartyMain")));
        if (nullptr == widget)
        {
            return false;
        }

        UW_PartyMain* partyMainWidget = Cast<UW_PartyMain>(widget);
        if (nullptr == partyMainWidget)
        {
            return false;
        }

        partyMainWidget->ReleasePlayerList(pkt.remote_id());
    }

    {
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

        mainGameWidget->ReleasePartyPlayerInfo(pkt.remote_id());
    }

    {
        UACPartyComponent* partyComponent = playerState->GetPartyComponent();
        if (nullptr == partyComponent)
        {
            return false;
        }

        partyComponent->LeaveParty(pkt.remote_id());
    }

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
        return true;
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

bool Handle_S2C_AppearArrow(ANetworkController* controller, Protocol::S2C_AppearArrow& pkt)
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

    const int64     objectID    = pkt.object_id();
    const FVector   location    = FVector(pkt.location().x(), pkt.location().y(), pkt.location().z());
    const FRotator  rotation    = FRotator(pkt.rotation().pitch(), pkt.rotation().yaw(), pkt.rotation().roll());
    const int64     timeStamp = pkt.timestamp();
    const int64     durationTime = controller->GetServerTimeStamp() - timeStamp;

    if (nullptr != gameState->FindGameObject(objectID))
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_AppearItem] ALREADY GameObject : %d"), objectID), ELogLevel::Error);
        return true;
    }

    AActor* newActor = gameState->CreateGameObject(AArcherSkeletonArrow::StaticClass(), location, rotation, objectID);
    AArcherSkeletonArrow* newArrow = Cast<AArcherSkeletonArrow>(newActor);
    if (nullptr == newArrow)
    {
        return false;
    }
    newArrow->InitProjectile(1000.0f, 1000.0f);
    newArrow->LineProjectileMovement(location, rotation, durationTime / 1000.0f);

    return true;
}

bool Handle_S2C_AppearProtal(ANetworkController* controller, Protocol::S2C_AppearProtal& pkt)
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
    const FVector   location = FVector(pkt.location().x(), pkt.location().y(), pkt.location().z());
    const FRotator  rotation = FRotator(pkt.rotation().pitch(), pkt.rotation().yaw(), pkt.rotation().roll());

    if (nullptr != gameState->FindGameObject(objectID))
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_AppearProtal] ALREADY GameObject : %d"), objectID), ELogLevel::Error);
        return true;
    }

    AActor* newActor = gameState->CreateGameObject(APortal::StaticClass(), location, rotation, objectID);
    if (nullptr == newActor)
    {
        return false;
    }

    return true;
}

bool Handle_S2C_AppearObstruction(ANetworkController* controller, Protocol::S2C_AppearObstruction& pkt)
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

    const int64     objectID    = pkt.object_id();
    const int32     type        = pkt.type();
    const FVector   location    = FVector(pkt.location().x(), pkt.location().y(), pkt.location().z());
    const FRotator  rotation    = FRotator(pkt.rotation().pitch(), pkt.rotation().yaw(), pkt.rotation().roll());
    const FVector   extent      = FVector(pkt.extent().x(), pkt.extent().y(), pkt.extent().z());

    if (nullptr != gameState->FindGameObject(objectID))
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_AppearObstruction] ALREADY GameObject : %d"), objectID), ELogLevel::Error);
        return true;
    }

    AActor* newActor = gameState->CreateGameObject(AObstructionBase::StaticClass(), location, rotation, objectID);
    if (nullptr == newActor)
    {
        return false;
    }

    AObstructionBase* newObstruction = Cast<AObstructionBase>(newActor);
    if (nullptr == newObstruction)
    {
        return false;
    }
    newObstruction->SetObstructioType(type);
    newObstruction->SetBlockingExtent(extent);

    return true;
}

bool Handle_S2C_MovementProjectile(ANetworkController* controller, Protocol::S2C_MovementProjectile& pkt)
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
    const FVector   location = FVector(pkt.location().x(), pkt.location().y(), pkt.location().z());
    const FRotator  rotation = FRotator(pkt.rotation().pitch(), pkt.rotation().yaw(), pkt.rotation().roll());
    const int64     timeStamp = pkt.timestamp();
    const int64     durationTime = controller->GetServerTimeStamp() - timeStamp;

    AActor* actor = gameState->FindGameObject(objectID);
    if (nullptr == actor)
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_AppearEnemy] INVALID GameObject : %d"), objectID), ELogLevel::Error);
        return true;
    }

    ALineProjectile* lineProjectile = Cast<ALineProjectile>(actor);
    if (nullptr == lineProjectile)
    {
        return false;
    }
    lineProjectile->LineProjectileMovement(location, rotation, durationTime / 1000.0f);

    return true;
}

bool Handle_S2C_Teleport(ANetworkController* controller, Protocol::S2C_Teleport& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
    if (nullptr == gameState)
    {
        return false;
    }

    const int64     objectID = pkt.object_id();
    const FVector   location = FVector(pkt.location().x(), pkt.location().y(), pkt.location().z());

    AController* remoteController = gameState->FindPlayerController(objectID);
    if (nullptr == remoteController)
    {
        return true;
    }

    ANPS_Game* playerState = remoteController->GetPlayerState<ANPS_Game>();
    if (nullptr == playerState)
    {
        return true;
    }

    APawn* pawn = playerState->GetPawn();
    if (nullptr == pawn)
    {
        return true;
    }
    
    if (gameMode->CompareNetworkController(remoteController))
    {
        AMovementController* movementController = Cast<AMovementController>(remoteController);
        if (nullptr == movementController)
        {
            return false;
        }
        movementController->OnTeleport(location);
    }
    else
    {
        ANPC_Game* npcController = Cast<ANPC_Game>(remoteController);
        if (nullptr == npcController)
        {
            return false;
        }
        npcController->OnTeleport(location);
    }

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
        return true;
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
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_DetectChangeEnemy] INVALID GameObject : %d"), objectID), ELogLevel::Error);
        return true;
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
        return true;
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

bool Handle_S2C_AnimationMovementEnemy(ANetworkController* controller, Protocol::S2C_AnimationMovementEnemy& pkt)
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
    const int64     objectID = pkt.object_id();
    FVector         startLocation = FVector(pkt.start_location().x(), pkt.start_location().y(), pkt.start_location().z());
    FVector         endLocation = FVector(pkt.end_location().x(), pkt.end_location().y(), pkt.end_location().z());
    const int64     moveDuration = pkt.duration();
    const int64     timestamp = pkt.timestamp();
    const int64     durationTime = controller->GetServerTimeStamp() - timestamp;


    AActor* actor = gameState->FindGameObject(objectID);
    if (nullptr == actor)
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_AnimationMovementEnemy] INVALID GameObject : %d"), objectID), ELogLevel::Error);
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
    enemyController->AnimationMoveDestination(startLocation, endLocation, moveDuration, durationTime);

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

   bool ret = gameState->RemoveGameObject(objectID);
   if (false == ret)
   {
       UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_AppearEnemy] Can't Remove GameObject : %d"), objectID), ELogLevel::Error);
   }

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
    if (false == result)
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_DisAppearGameObject] Can't Remove GameObject : %d"), objectID), ELogLevel::Error);
        return true;
    }
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

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
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
    playerState->mInventoryComponent->LoadItem(pkt.item(), pkt.money());
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
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_InsertInventory] INVALID Item in world : %d"), gameObjectID), ELogLevel::Error);
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
    FCharacterEquipment oldDatas = playerState->GetCharacterData().GetEquipment();
    playerState->SetCharacterEqipment(updateEquipment);
    playerState->calculationStats();
    playerState->DetectChangeCurrentStats(oldDatas, updateEquipment);

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
    preivewCharacter->UpdateCharacterPose(ECharacterPose::Idle, true);

    return true;
}

bool Handle_S2C_LoadSkillTree(ANetworkController* controller, Protocol::S2C_LoadSkillTree& pkt)
{
    return true;
}

bool Handle_S2C_UpdateSkillTree(ANetworkController* controller, Protocol::S2C_UpdateSkillTree& pkt)
{
    return true;
}

bool Handle_S2C_SetUseKeyAction(ANetworkController* controller, Protocol::S2C_SetUseKeyAction& pkt)
{
    return false;
}

bool Handle_S2C_ResponseUseKeyAction(ANetworkController* controller, Protocol::S2C_ResponseUseKeyAction& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    bool ret = UWidgetUtils::SetResponseUseKeyAction(clientHUD, pkt.key_id(), UNetworkUtils::GetNetworkErrorToString(pkt.error()));
    if (ret == false)
    {
        return false;
    }

    return true;
}

bool Handle_S2C_AppearSkill(ANetworkController* controller, Protocol::S2C_AppearSkill& pkt)
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

    const int64& remoteID = pkt.remote_id();
    const int64& objectID = pkt.object_id();
    const int32& skillID = pkt.skill_id();
    const FVector& location = FVector(pkt.location().x(), pkt.location().y(), pkt.location().z());
    const FRotator& rotation = FRotator(pkt.rotation().pitch(), pkt.rotation().yaw(), pkt.rotation().roll());
    const float& duration = pkt.duration() / 1000.0f;

    if (nullptr != gameState->FindGameObject(objectID) && remoteID != objectID)
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_AppearBuff] ALREADY GameObject : %d"), objectID), ELogLevel::Error);
        return true;
    }

    if (skillID <= 5)
    {
        AController* Control = gameState->FindPlayerController(remoteID);
        if (nullptr == Control)
        {
            return false;
        }

        ACharacter* character = Control->GetCharacter();
        if (nullptr == character)
        {
            return false;
        }

        ANC_Game* nonCharacter = Cast<ANC_Game>(character);
        if (nullptr == nonCharacter)
        {
            return false;
        }
        nonCharacter->DoAppearSkill(location, rotation, remoteID, objectID, skillID, duration);
    }
    else
    {
        UEnemySkillManager* manager = NewObject<UEnemySkillManager>();
        manager->Init();
        AActor* enemy = gameState->FindGameObject(remoteID);
        manager->InputActiveSkillData(world, enemy, skillID, location, rotation, objectID, remoteID);
    }
    return true;
}

bool Handle_S2C_ReactionSkill(ANetworkController* controller, Protocol::S2C_ReactionSkill& pkt)
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

    const int64&    remoteID    = pkt.remote_id();
    const int64&    objectID    = pkt.object_id();
    const int32&    skillID     = pkt.skill_id();
    const FVector&  location    = FVector(pkt.location().x(), pkt.location().y(), pkt.location().z());
    const FRotator& rotation    = FRotator(pkt.rotation().pitch(), pkt.rotation().yaw(), pkt.rotation().roll());

    const float& Duration = pkt.duration() / 1000.0f;
   // const float& clientDuration = controller->GetServerTimeStamp() / 1000.0f;

    AActor* actor = gameState->FindGameObject(objectID);
    if (nullptr == actor)
    {
        UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Handle_S2C_ReactionSkill] INVALID GameObject : %d"), objectID), ELogLevel::Error);
        return true;
    }

    if (skillID <= 5)
    {
        AController* Control = gameState->FindPlayerController(remoteID);
        if (nullptr == Control)
        {
            return false;
        }

        ACharacter* character = Control->GetCharacter();
        if (nullptr == character)
        {
            return false;
        }

        ANC_Game* nonCharacter = Cast<ANC_Game>(character);
        if (nullptr == nonCharacter)
        {
            return false;
        }
        nonCharacter->DoActionSkill(location, rotation, remoteID, objectID, skillID, Duration);
    }
    else
    {
        UEnemySkillManager* manager = NewObject<UEnemySkillManager>();
        manager->Init();
        AActor* enemy = gameState->FindGameObject(remoteID);
        manager->InputReactionSkillData(world, enemy, skillID, location, rotation, objectID, remoteID);
    }
    return true;
}

bool Handle_S2C_EndReactionSkill(ANetworkController* controller, Protocol::S2C_EndReactionSkill& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
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

    ANC_Game* player = Cast<ANC_Game>(remoteController->GetPawn());
    if (nullptr == player)
    {
        return true;
    }

    player->ActiveMovement();
    player->SetCanMove(true);
    player->SetUsingSkill(false);

    return true;
}

bool Handle_S2C_SkillCoolTime(ANetworkController* controller, Protocol::S2C_SkillCoolTime& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    if (pkt.skill_id_size() != pkt.skill_time_size())
    {
        return false;
    }
    const int32 indexSize = pkt.skill_id_size();

    TArray<int32> skillIDs;
    TArray<int64> skillDurations;
    for (int32 index = 0; index < indexSize; ++index)
    {
        skillIDs.Add(pkt.mutable_skill_id()->at(index));
        skillDurations.Add(pkt.mutable_skill_time()->at(index));
        if (pkt.mutable_skill_time()->at(index) <= 0)
        {
            APC_Game* control = Cast<APC_Game>(controller);
            if(nullptr != control)
            {
                control->SkillCoolTime(pkt.mutable_skill_id()->at(index));
            }
        }
    }

    bool ret = UWidgetUtils::SetSkillCoolTime(clientHUD, skillIDs, skillDurations);
    if (ret == false)
    {
        return false;
    }

    return true;
}

bool Handle_S2C_PushBuff(ANetworkController* controller, Protocol::S2C_PushBuff& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    bool ret = UWidgetUtils::SetPushBuff(clientHUD, pkt.remote_id(), pkt.buff_id(), pkt.duration());
    if (ret == false)
    {
        return false;
    }

    return true;
}

bool Handle_S2C_ReleaseBuff(ANetworkController* controller, Protocol::S2C_ReleaseBuff& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    bool ret = UWidgetUtils::SetReleaseBuff(clientHUD, pkt.remote_id(), pkt.buff_id());
    if (ret == false)
    {
        return false;
    }

    return true;
}

bool Handle_S2C_DebugBox(ANetworkController* controller, Protocol::S2C_DebugBox& pkt)
{

    FVector startLocation   = FVector(pkt.start_location().x(), pkt.start_location().y(), pkt.start_location().z());
    FVector endLocation     = FVector(pkt.end_location().x(), pkt.end_location().y(), pkt.end_location().z());
    FVector extent          = FVector(pkt.extent().x(), pkt.extent().y(), pkt.extent().z());
    float duration          = pkt.duration();

    UBlueprint* BlueprintObj = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, TEXT("Blueprint'/Game/Test/DebugActor_Box.DebugActor_Box'")));
    if (BlueprintObj)
    {
        UClass* DebugActorClass = BlueprintObj->GeneratedClass;
        UWorld* world = controller->GetWorld();
        if (world == nullptr)
        {
            return false;
        }
        Cast<ADebug_Box>(world->SpawnActor<AActor>(DebugActorClass, FVector(), FRotator()))->DebugInit(startLocation, endLocation, extent, duration);
    }

    return true;
}

bool Handle_S2C_DebugCircle(ANetworkController* controller, Protocol::S2C_DebugCircle& pkt)
{
    FVector location    = FVector(pkt.location().x(), pkt.location().y(), pkt.location().z());
    float radius        = pkt.radius();
    float duration      = pkt.duration();

    UBlueprint* BlueprintObj = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, TEXT("Blueprint'/Game/Test/DebugActor_Circle.DebugActor_Circle'")));
    if (BlueprintObj)
    {
        UClass* DebugActorClass = BlueprintObj->GeneratedClass;
        if (nullptr == DebugActorClass)
        {
            return true;
        }

        UWorld* world = controller->GetWorld();
        if (world == nullptr)
        {
            return false;
        }

        AActor* newActor = world->SpawnActor<AActor>(DebugActorClass, FVector(), FRotator());
        if (nullptr == newActor)
        {
            return true;
        }

        ADebug_Circle* newDebugCircle = Cast<ADebug_Circle>(newActor);
        if (nullptr == newDebugCircle)
        {
            return true;
        }
        newDebugCircle->DebugInit(radius, location, duration);
    }

    return true;
}

bool Handle_S2C_RequestEnterDungeon(ANetworkController* controller, Protocol::S2C_RequestEnterDungeon& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    APS_Game* playerState = Cast<APS_Game>(controller->PlayerState);
    if (nullptr == playerState)
    {
        return false;
    }

    clientHUD->CleanWidgetFromName(TEXT("LoadingServer"));

    int32 error = pkt.error();
    if (error != GetDatabaseErrorToInt(EDCommonErrorType::SUCCESS))
    {
        FNotificationDelegate notificationDelegate;
        notificationDelegate.BindLambda([=]()
            {
                clientHUD->CleanWidgetFromName(TEXT("Notification"));
            });

        bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("던전 입장 실패"), UNetworkUtils::GetNetworkErrorToString(error), TEXT("확인"), notificationDelegate);
        if (ret == false)
        {
            return false;
        }
    }
    else
    {
        clientHUD->ShowWidgetFromName(TEXT("LoadingLevel"));
    }

    return true;
}

bool Handle_S2C_ResponseEnterDungeon(ANetworkController* controller, Protocol::S2C_ResponseEnterDungeon& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    APS_Game* playerState = Cast<APS_Game>(controller->PlayerState);
    if (nullptr == playerState)
    {
        return false;
    }

    int32 error = pkt.error();
    if (error != GetDatabaseErrorToInt(EDCommonErrorType::SUCCESS))
    {
        FNotificationDelegate notificationDelegate;
        notificationDelegate.BindLambda([=]()
            {
                clientHUD->CleanWidgetFromName(TEXT("Notification"));
            });

        bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("던전 입장 실패"), UNetworkUtils::GetNetworkErrorToString(error), TEXT("확인"), notificationDelegate);
        if (ret == false)
        {
            return false;
        }
    }

    ULDGameInstance* instance = Cast<ULDGameInstance>(world->GetGameInstance());
    if (nullptr == instance)
    {
        return false;
    }
    instance->SetDungeonID(pkt.dungeon_id());

    FString level = UNetworkUtils::ConvertFString(pkt.level());
    gameMode->RequestTravelLevel(level);

    clientHUD->CleanWidgetFromName(TEXT("LoadingLevel"));

    clientHUD->FadeIn();

    return true;
}

bool Handle_S2C_WaitingLoadDungeon(ANetworkController* controller, Protocol::S2C_WaitingLoadDungeon& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    bool ret = UWidgetUtils::SetLoadingPlayer(clientHUD, pkt.max_number(), pkt.least_number());
    if (ret == false)
    {
        return false;
    }

    clientHUD->FadeOut();

    return true;
}

bool Handle_S2C_CompleteLoadDungeon(ANetworkController* controller, Protocol::S2C_CompleteLoadDungeon& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }
    
    clientHUD->CleanWidgetFromName(TEXT("LoadingPlayer"));
    clientHUD->ShowWidgetFromName(FString(TEXT("MainGame")));
    clientHUD->FadeOut();

    return true;
}

bool Handle_S2C_EnterPortal(ANetworkController* controller, Protocol::S2C_EnterPortal& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    FString title = UNetworkUtils::ConvertFString(pkt.title());
    int64 time = pkt.time();

    bool ret = UWidgetUtils::SetWaiting(clientHUD, title, time);
    if (ret == false)
    {
        return false;
    }

    return true;
}

bool Handle_S2C_LeavePortal(ANetworkController* controller, Protocol::S2C_LeavePortal& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    clientHUD->CleanWidgetFromName(TEXT("Waiting"));

    return true;
}

bool Handle_S2C_PlaySequence(ANetworkController* controller, Protocol::S2C_PlaySequence& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }
    clientHUD->CleanWidgetFromName(TEXT("MainGame"));

    //TODO play sequence
    int32 sequence = pkt.sequence();
    int32 max = pkt.max_number();

    bool ret = UWidgetUtils::SetSkipSequence(clientHUD, max, 0);
    if (ret == false)
    {
        return false;
    }

    APC_Game* PC_Controller = Cast<APC_Game>(controller);
    if (nullptr == PC_Controller)
    {
        return false;
    }

    PC_Controller->RequestCinematicPlay(sequence);

    return true;
}

bool Handle_S2C_SkipSequence(ANetworkController* controller, Protocol::S2C_SkipSequence& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    bool ret = UWidgetUtils::SetSkipSequence(clientHUD, pkt.max_number(), pkt.least_number());
    if (ret == false)
    {
        return false;
    }

    return true;
}

bool Handle_S2C_EndSequence(ANetworkController* controller, Protocol::S2C_EndSequence& pkt)
{
    UWorld* world = controller->GetWorld();
    if (nullptr == world)
    {
        return false;
    }

    ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
    if (nullptr == gameMode)
    {
        return false;
    }

    AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
    if (nullptr == clientHUD)
    {
        return false;
    }

    clientHUD->CleanWidgetFromName(TEXT("SkipSequence"));

    clientHUD->ShowWidgetFromName(TEXT("MainGame"));

    //TODO end sequence

    APC_Game* PC_Controller = Cast<APC_Game>(controller);
    if (nullptr == PC_Controller)
    {
        return false;
    }

    PC_Controller->RequestCinematicStop();

    clientHUD->FadeOut();
    return true;
}