// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PC_Game.h"
#include <Network/NetworkGameMode.h>
#include <Network/NetworkController.h>
#include <Widget/Handler/ClientHUD.h>
#include <Widget/Game/Main/W_MainGame.h>
#include <Framework/Game/C_Game.h>
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FCommonPacketHandler.h>
#include <Network/NetworkUtils.h>

#include <Game/C_Game.h>
#include <Game/GM_Game.h>
#include <Game/PS_Game.h>
#include <Game/GS_Game.h>

APC_Game::APC_Game()
{
	SwitchMovementMode();
}

APC_Game::~APC_Game()
{
}

void APC_Game::BeginPlay()
{
	Super::BeginPlay();
}

bool APC_Game::OnRecvPacket(BYTE* buffer, const uint32 len)
{
	ANetworkController* controller = Cast<ANetworkController>(this);
	bool result = false;
	result = FClientPacketHandler::HandlePacket(controller, buffer, len);
	if (false == result)
	{
		UNetworkUtils::NetworkConsoleLog("Failed to handle packet", ELogLevel::Error);
		return false;
	}

	return true;
}

bool APC_Game::OnSend(int32 len)
{
	return true;
}

bool APC_Game::OnConnect()
{
	return true;
}

bool APC_Game::OnDisconnect()
{
	return true;
}

bool APC_Game::OnTick()
{
	Protocol::C2S_ReplicatedServerTimeStamp timeStampPacket;
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