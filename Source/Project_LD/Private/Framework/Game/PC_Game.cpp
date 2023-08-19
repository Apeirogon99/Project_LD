// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PC_Game.h"
#include "Framework/AnimInstance/AI_PlayerCharacter.h"
#include <Network/NetworkGameMode.h>
#include <Network/NetworkSession.h>
#include <Network/NetworkController.h>
#include <Widget/Handler/ClientHUD.h>
#include <Widget/Game/Main/W_MainGame.h>
#include <Widget/WidgetUtils.h>

#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FCommonPacketHandler.h>
#include <Network/NetworkUtils.h>

#include <Network/NetworkTimeStamp.h>

#include <Game/PS_Game.h>
#include <Game/GS_Game.h>
#include <Game/C_Game.h>

APC_Game::APC_Game()
{
	
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

bool APC_Game::OnRecvPacket(BYTE* buffer, const uint32 len)
{
	ANetworkController* controller = Cast<ANetworkController>(this);
	bool result = false;
	result = FClientPacketHandler::HandlePacket(controller, buffer, len);
	if (false == result)
	{
		UNetworkUtils::NetworkConsoleLog("Failed to handle packet", ELogLevel::Error);

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

		bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("Error"), TEXT("Failed to handle packet"), TEXT("Confirm"), notificationDelegate);
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

	InputComponent->BindAction("SkillQ", IE_Released, this, &APC_Game::UseSkill_Q_Released);
	InputComponent->BindAction("SkillW", IE_Released, this, &APC_Game::UseSkill_W_Released);
	InputComponent->BindAction("SkillE", IE_Released, this, &APC_Game::UseSkill_E_Released);
	InputComponent->BindAction("SkillR", IE_Released, this, &APC_Game::UseSkill_R_Released);
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

	playerAnim->PlayClientSkillMontage(1);

	Protocol::C2S_PressedUseKeyAction keyActionPacket;
	keyActionPacket.set_key_id(81);
	keyActionPacket.set_timestamp(this->GetServerTimeStamp());
	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
	this->Send(pakcetBuffer);
}

void APC_Game::UseSkill_Q_Released()
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

	playerAnim->PlayClientSkillMontage(2);

	Protocol::C2S_PressedUseKeyAction keyActionPacket;
	keyActionPacket.set_key_id(87);
	keyActionPacket.set_timestamp(this->GetServerTimeStamp());
	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
	this->Send(pakcetBuffer);
}

void APC_Game::UseSkill_W_Released()
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

	playerAnim->PlayClientSkillMontage(0);

	Protocol::C2S_PressedUseKeyAction keyActionPacket;
	keyActionPacket.set_key_id(69);
	keyActionPacket.set_timestamp(this->GetServerTimeStamp());
	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
	this->Send(pakcetBuffer);
}

void APC_Game::UseSkill_E_Released()
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

	//playerAnim->PlayClientSkillMontage(3);
	playerAnim->PlaySkillMontage(3, 0.f);

	Protocol::C2S_PressedUseKeyAction keyActionPacket;
	keyActionPacket.set_key_id(82);
	keyActionPacket.set_timestamp(this->GetServerTimeStamp());
	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
	this->Send(pakcetBuffer);
}

void APC_Game::UseSkill_R_Released()
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

	playerAnim->PlayClientSkillMontage(4);

	Protocol::C2S_ReleaseUseKeyAction keyActionPacket;
	keyActionPacket.set_key_id(82);
	keyActionPacket.set_timestamp(this->GetServerTimeStamp());
	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(this, keyActionPacket);
	this->Send(pakcetBuffer);
}
