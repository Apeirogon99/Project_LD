// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PC_Game.h"
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
