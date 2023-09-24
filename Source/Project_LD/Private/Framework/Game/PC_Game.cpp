// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PC_Game.h"
#include "Framework/AnimInstance/AI_PlayerCharacter.h"
#include <Network/NetworkGameMode.h>
#include <Network/NetworkSession.h>
#include <Network/NetworkController.h>
#include <Widget/Handler/ClientHUD.h>
#include <Widget/Game/Main/W_MainGame.h>
#include <Widget/WidgetUtils.h>
#include <Interface/InteractiveInterface.h>

#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FCommonPacketHandler.h>
#include <Network/NetworkUtils.h>

#include <Network/NetworkTimeStamp.h>

#include <Game/PS_Game.h>
#include <Game/GS_Game.h>
#include <Game/C_Game.h>

APC_Game::APC_Game()
{
	mRightMouseActions.Add(FName("Ground"), &APC_Game::MoveToMouseCursor);
	mRightMouseActions.Add(FName("PickUp"), &APC_Game::PickUp);
	mRightMouseActions.Add(FName("Interative"), &APC_Game::Interative);
	mRightMouseActions.Add(FName("NPC"), &APC_Game::NPC);

	mLeftMouseActions.Add(FName("Enemy"), &APC_Game::Enemy);
}

APC_Game::~APC_Game()
{
}

void APC_Game::BeginPlay()
{
	Super::BeginPlay();

	SwitchMovementMode();
	SwitchUIMode();
}

void APC_Game::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (mIsLeftMouse || mIsRightMouse)
	{
		mMouseTick += DeltaTime;
		if (mMouseTick >= 0.25f)
		{
			if (mIsLeftMouse)
			{
				CheackMouseTrace(mLeftMouseActions);
			}
			else if(mIsRightMouse)
			{
				CheackMouseTrace(mRightMouseActions);
			}

			mMouseTick = 0.0f;
		}
	}
}

bool APC_Game::OnRecvPacket(BYTE* buffer, const uint32 len)
{
	ANetworkController* controller = Cast<ANetworkController>(this);
	bool result = false;
	result = FClientPacketHandler::HandlePacket(controller, buffer, len);
	if (false == result)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("Failed to handle packet [%d]"), header->id), ELogLevel::Error);

		AClientHUD* clientHUD = Cast<AClientHUD>(controller->GetHUD());
		if (nullptr == clientHUD)
		{
			UNetworkUtils::NetworkConsoleLog("Invalid client hud", ELogLevel::Error);
			return false;
		}

		FNotificationDelegate notificationDelegate;
		notificationDelegate.BindLambda([=]()
			{
				clientHUD->CleanWidgetFromName(TEXT("Notification"));
				FGenericPlatformMisc::RequestExit(false);
			});

		bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("Error"), FString::Printf(TEXT("Failed to handle packet [%d]"), header->id), TEXT("Confirm"), notificationDelegate);
		if (ret == false)
		{
			return false;
		}

		return false;
	}

	return true;
}

bool APC_Game::OnSend(int32 len)
{
	UNetworkUtils::NetworkConsoleLog("OnSend", ELogLevel::Error);
	return true;
}

bool APC_Game::OnConnect()
{
	UNetworkUtils::NetworkConsoleLog("OnConnect", ELogLevel::Error);
	return true;
}

bool APC_Game::OnDisconnect()
{
	UNetworkUtils::NetworkConsoleLog("OnDisconnect", ELogLevel::Error);
	return true;
}

bool APC_Game::OnTick()
{

	Super::OnTick();

	UNetworkTimeStamp* networkTimeStmap = this->GetTimeStamp();
	if (nullptr == networkTimeStmap)
	{
		return false;
	}

	const int64 nowUtcTimeStamp = networkTimeStmap->GetUtcTimeStmap();
	const int64 nowRTT			= networkTimeStmap->GetRTT();

	Protocol::C2S_ReplicatedServerTimeStamp timeStampPacket;
	timeStampPacket.set_utc_time(nowUtcTimeStamp);
	timeStampPacket.set_rtt(nowRTT);
	SendBufferPtr pakcetBuffer = FCommonPacketHandler::MakeSendBuffer(this, timeStampPacket);
	this->Send(pakcetBuffer);

	return true;
}

void APC_Game::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void APC_Game::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ToggleInventory",IE_Pressed,this,&APC_Game::SwitchInventory);
	InputComponent->BindAction("ToggleChat", IE_Pressed, this, &APC_Game::SwitchChat);
	InputComponent->BindAction("ToggleSkillTree", IE_Pressed, this, &APC_Game::SwitchSkillTree);
	InputComponent->BindAction("ToggleFriend", IE_Pressed, this, &APC_Game::SwitchFriend);
	InputComponent->BindAction("ToggleParty", IE_Pressed, this, &APC_Game::SwitchParty);
	
	InputComponent->BindAction("SkillQ", IE_Pressed, this, &APC_Game::UseSkill_Q_Pressed);
	InputComponent->BindAction("SkillW", IE_Pressed, this, &APC_Game::UseSkill_W_Pressed);
	InputComponent->BindAction("SkillE", IE_Pressed, this, &APC_Game::UseSkill_E_Pressed);
	InputComponent->BindAction("SkillR", IE_Pressed, this, &APC_Game::UseSkill_R_Pressed);
	InputComponent->BindAction("Dash", IE_Pressed, this, &APC_Game::UseSkill_Dash_Pressed);

	InputComponent->BindAction("SkillQ", IE_Released, this, &APC_Game::UseSkill_Q_Released);
	InputComponent->BindAction("SkillW", IE_Released, this, &APC_Game::UseSkill_W_Released);
	InputComponent->BindAction("SkillE", IE_Released, this, &APC_Game::UseSkill_E_Released);
	InputComponent->BindAction("SkillR", IE_Released, this, &APC_Game::UseSkill_R_Released);
	InputComponent->BindAction("Dash", IE_Released, this, &APC_Game::UseSkill_Dash_Released);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APC_Game::CameraZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &APC_Game::CameraZoomOut);

	InputComponent->BindAction("LeftMouseAction(Player)", IE_Pressed, this, &APC_Game::PressedLeftMouse);
	InputComponent->BindAction("LeftMouseAction(Player)", IE_Released, this, &APC_Game::ReleasedLeftMouse);

	InputComponent->BindAction("RightMouseAction(Player)", IE_Pressed, this, &APC_Game::PressedRightMouse);
	InputComponent->BindAction("RightMouseAction(Player)", IE_Released, this, &APC_Game::ReleasedRightMouse);
}

void APC_Game::CheackMouseTrace(TMap<FName, TFunction<void(APC_Game&, AActor*, FHitResult)>> inMouseActions)
{
	FHitResult hitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, hitResult);

	if (false == hitResult.bBlockingHit)
	{
		return;
	}

	AActor* hitActor = hitResult.Actor.Get();
	if (nullptr == hitActor)
	{
		return;
	}

	TArray<FName> tags = hitActor->Tags;
	if (0 == tags.Num())
	{
		return;
	}

	int32 findTargetTag = INDEX_NONE;
	for (auto targetTag : inMouseActions)
	{
		int32 tempCompareTag = tags.Find(targetTag.Key);
		if (INDEX_NONE != tempCompareTag)
		{
			TFunction<void(APC_Game&, AActor*, FHitResult)> actionFunction = *inMouseActions.Find(targetTag.Key);
			actionFunction(*this, hitActor, hitResult);
			return;
		}
	}

	if (INDEX_NONE == findTargetTag)
	{
		return;
	}

}

void APC_Game::PickUp(AActor* inHitActor, FHitResult inHitResult)
{
	ANC_Game* character = Cast<ANC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}

	if (inHitActor->GetClass()->ImplementsInterface(UInteractiveInterface::StaticClass()))
	{
		Cast<IInteractiveInterface>(inHitActor)->Interactive(character);
	}
}

void APC_Game::Interative(AActor* inHitActor, FHitResult inHitResult)
{
	ANC_Game* character = Cast<ANC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}

	if (inHitActor->GetClass()->ImplementsInterface(UInteractiveInterface::StaticClass()))
	{
		Cast<IInteractiveInterface>(inHitActor)->Interactive(character);
	}
}

void APC_Game::Enemy(AActor* inHitActor, FHitResult inHitResult)
{
	ANC_Game* character = Cast<ANC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}

	if (inHitActor->GetClass()->ImplementsInterface(UInteractiveInterface::StaticClass()))
	{
		Cast<IInteractiveInterface>(inHitActor)->Interactive(character);
	}
}

void APC_Game::NPC(AActor* inHitActor, FHitResult inHitResult)
{
	ANC_Game* character = Cast<ANC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}

	if (inHitActor->GetClass()->ImplementsInterface(UInteractiveInterface::StaticClass()))
	{
		Cast<IInteractiveInterface>(inHitActor)->Interactive(character);
	}
}

void APC_Game::SwitchUIMode()
{
	FInputModeGameAndUI inputMode;
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputMode.SetHideCursorDuringCapture(false);
	SetInputMode(inputMode);
	bShowMouseCursor = true;
}

void APC_Game::SwitchInventory()
{
	AClientHUD* clientHUD = Cast<AClientHUD>(this->GetHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("MainGame")));
	if (nullptr == widget)
	{
		return;
	}

	UW_MainGame* maingame = Cast<UW_MainGame>(widget);
	if (nullptr == maingame)
	{
		return;
	}

	maingame->InventoryOpenRequest();
}

void APC_Game::SwitchChat()
{
	AClientHUD* clientHUD = Cast<AClientHUD>(this->GetHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("MainGame")));
	if (nullptr == widget)
	{
		return;
	}

	UW_MainGame* mainGame = Cast<UW_MainGame>(widget);
	if (nullptr == mainGame)
	{
		return;
	}

	mainGame->FocusChat();
}

void APC_Game::SwitchSkillTree()
{
	AClientHUD* clientHUD = Cast<AClientHUD>(this->GetHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("MainGame")));
	if (nullptr == widget)
	{
		return;
	}

	UW_MainGame* maingame = Cast<UW_MainGame>(widget);
	if (nullptr == maingame)
	{
		return;
	}

	maingame->SkillTreeOpenRequest();
}

void APC_Game::SwitchFriend()
{
	AClientHUD* clientHUD = Cast<AClientHUD>(this->GetHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("MainGame")));
	if (nullptr == widget)
	{
		return;
	}

	UW_MainGame* mainGame = Cast<UW_MainGame>(widget);
	if (nullptr == mainGame)
	{
		return;
	}

	mainGame->FriendOpenRequest();
}

void APC_Game::SwitchParty()
{
	AClientHUD* clientHUD = Cast<AClientHUD>(this->GetHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("MainGame")));
	if (nullptr == widget)
	{
		return;
	}

	UW_MainGame* mainGame = Cast<UW_MainGame>(widget);
	if (nullptr == mainGame)
	{
		return;
	}

	mainGame->PartyOpenRequest();
}

void APC_Game::PressedLeftMouse()
{
	CheackMouseTrace(mLeftMouseActions);

	mIsLeftMouse = true;
	mMouseTick = 0.0f;
}

void APC_Game::ReleasedLeftMouse()
{
	mIsLeftMouse = false;
}

void APC_Game::PressedRightMouse()
{
	CheackMouseTrace(mRightMouseActions);

	mIsRightMouse = true;
	mMouseTick = 0.0f;
}

void APC_Game::ReleasedRightMouse()
{
	mIsRightMouse = false;
}

void APC_Game::UseSkill_Q_Pressed()
{
	AC_Game* character = Cast<AC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}

	UAI_PlayerCharacter* playerAnim = Cast<UAI_PlayerCharacter>(character->GetMesh()->GetAnimInstance());
	if (playerAnim == nullptr)
	{
		return;
	}

	if ((character->GetCanUseSkillQ()) && (!character->GetUsingSkill()) && (!playerAnim->GetIsAttack()))
	{
		character->SetCanUseSkillQ(false);
		character->SetUsingSkill(true);
		character->SetCanMove(false);
		character->StopMovement();
		playerAnim->PlayClientSkillMontage(1);

		Protocol::C2S_PressedUseKeyAction keyActionPacket;
		keyActionPacket.set_key_id(81);
		keyActionPacket.set_timestamp(this->GetServerTimeStamp());
		SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
		this->Send(pakcetBuffer);
	}
}

void APC_Game::UseSkill_Q_Released()
{
	AC_Game* character = Cast<AC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}

	if (character->GetCanUseSkillQ() == true)
	{
		return;
	}

	character->StartQTimer();

	Protocol::C2S_ReleaseUseKeyAction keyActionPacket;
	keyActionPacket.set_key_id(81);
	keyActionPacket.set_timestamp(this->GetServerTimeStamp());
	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
	this->Send(pakcetBuffer);
}

void APC_Game::UseSkill_W_Pressed()
{
	AC_Game* character = Cast<AC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}

	UAI_PlayerCharacter* playerAnim = Cast<UAI_PlayerCharacter>(character->GetMesh()->GetAnimInstance());
	if (playerAnim == nullptr)
	{
		return;
	}

	if ((character->GetCanUseSkillW()) && (!character->GetUsingSkill()) && (!playerAnim->GetIsAttack()))
	{
		character->SetCanUseSkillW(false);
		character->SetUsingSkill(true);
		character->SetCanMove(false);
		character->StopMovement();
		playerAnim->PlayClientSkillMontage(2);

		Protocol::C2S_PressedUseKeyAction keyActionPacket;
		keyActionPacket.set_key_id(87);
		keyActionPacket.set_timestamp(this->GetServerTimeStamp());
		SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
		this->Send(pakcetBuffer);
	}
}

void APC_Game::UseSkill_W_Released()
{
	AC_Game* character = Cast<AC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}

	if (character->GetCanUseSkillW() == true)
	{
		return;
	}

	character->StartWTimer();

	Protocol::C2S_ReleaseUseKeyAction keyActionPacket;
	keyActionPacket.set_key_id(87);
	keyActionPacket.set_timestamp(this->GetServerTimeStamp());
	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
	this->Send(pakcetBuffer);
}

void APC_Game::UseSkill_E_Pressed()
{
	AC_Game* character = Cast<AC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}

	UAI_PlayerCharacter* playerAnim = Cast<UAI_PlayerCharacter>(character->GetMesh()->GetAnimInstance());
	if (playerAnim == nullptr)
	{
		return;
	}

	if ((character->GetCanUseSkillE()) && (!character->GetUsingSkill()) && (!playerAnim->GetIsAttack()))
	{
		character->SetCanUseSkillE(false);
		character->SetUsingSkill(true);
		character->SetCanMove(false);
		character->StopMovement();
		playerAnim->PlayClientSkillMontage(0);

		Protocol::C2S_PressedUseKeyAction keyActionPacket;
		keyActionPacket.set_key_id(69);
		keyActionPacket.set_timestamp(this->GetServerTimeStamp());
		SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
		this->Send(pakcetBuffer);
	}
}

void APC_Game::UseSkill_E_Released()
{
	AC_Game* character = Cast<AC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}

	if (character->GetCanUseSkillE() == true)
	{
		return;
	}

	character->StartETimer();

	Protocol::C2S_ReleaseUseKeyAction keyActionPacket;
	keyActionPacket.set_key_id(69);
	keyActionPacket.set_timestamp(this->GetServerTimeStamp());
	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
	this->Send(pakcetBuffer);
}

void APC_Game::UseSkill_R_Pressed()
{
	AC_Game* character = Cast<AC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}

	UAI_PlayerCharacter* playerAnim = Cast<UAI_PlayerCharacter>(character->GetMesh()->GetAnimInstance());
	if (playerAnim == nullptr)
	{
		return;
	}

	if ((character->GetCanUseSkillR()) && (!character->GetUsingSkill()) && (!playerAnim->GetIsAttack()))
	{
		character->SetCanUseSkillR(false);
		character->SetUsingSkill(true);
		character->SetCanMove(false);
		character->StopMovement();
		playerAnim->PlayClientSkillMontage(3);

		Protocol::C2S_PressedUseKeyAction keyActionPacket;
		keyActionPacket.set_key_id(82);
		keyActionPacket.set_timestamp(this->GetServerTimeStamp());
		SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
		this->Send(pakcetBuffer);
	}
}
void APC_Game::UseSkill_R_Released()
{
	AC_Game* character = Cast<AC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}

	if (character->GetCanUseSkillR() == true)
	{
		return;
	}

	UAI_PlayerCharacter* playerAnim = Cast<UAI_PlayerCharacter>(character->GetMesh()->GetAnimInstance());
	if (playerAnim == nullptr)
	{
		return;
	}

	character->StartRTimer();
	playerAnim->PlayClientSkillMontage(4);

	Protocol::C2S_ReleaseUseKeyAction keyActionPacket;
	keyActionPacket.set_key_id(82);
	keyActionPacket.set_timestamp(this->GetServerTimeStamp());
	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
	this->Send(pakcetBuffer);
}

void APC_Game::UseSkill_Dash_Pressed()
{
	AC_Game* character = Cast<AC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}

	UAI_PlayerCharacter* playerAnim = Cast<UAI_PlayerCharacter>(character->GetMesh()->GetAnimInstance());
	if (playerAnim == nullptr)
	{
		return;
	}

	if ((character->GetCanUseDash()) && (!character->GetUsingSkill()) && (!playerAnim->GetIsAttack()))
	{
		character->SetCanUseDash(false);
		character->SetUsingSkill(true);
		character->SetCanMove(false);
		playerAnim->PlayClientSkillMontage(5);

		Protocol::C2S_PressedUseKeyAction keyActionPacket;
		keyActionPacket.set_key_id(0xA2);
		keyActionPacket.set_timestamp(this->GetServerTimeStamp());
		SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
		this->Send(pakcetBuffer);
	}
}

void APC_Game::UseSkill_Dash_Released()
{
	AC_Game* character = Cast<AC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}

	if (character->GetCanUseDash() == true)
	{
		return;
	}

	character->StartDashTimer();

	Protocol::C2S_ReleaseUseKeyAction keyActionPacket;
	keyActionPacket.set_key_id(0xA2);
	keyActionPacket.set_timestamp(this->GetServerTimeStamp());
	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
	this->Send(pakcetBuffer);
}

void APC_Game::CameraZoomIn()
{
	AC_Game* character = Cast<AC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}
	character->OnCameraZoomIn();
}

void APC_Game::CameraZoomOut()
{
	AC_Game* character = Cast<AC_Game>(GetCharacter());
	if (character == nullptr)
	{
		return;
	}
	character->OnCameraZoomOut();
}
