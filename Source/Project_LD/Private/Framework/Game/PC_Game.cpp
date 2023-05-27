// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PC_Game.h"
#include <Network/NetworkGameMode.h>
#include <Network/NetworkController.h>
#include <Widget/Handler/ClientHUD.h>
#include <Widget/Game/Main/W_MainGame.h>
#include <Framework/Character/GameCharacter.h>
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Network/NetworkUtils.h>

APC_Game::APC_Game()
{
	SwitchMovementMode();

	InvenIsOpen = false;
}

APC_Game::~APC_Game()
{
}

void APC_Game::BeginPlay()
{
	Super::BeginPlay();

	ClientHUD = Cast<AClientHUD>(GetHUD());
	if (IsValid(ClientHUD))
	{
		FTimerHandle InvenInitTimer;
		GetWorldTimerManager().SetTimer(InvenInitTimer, this, &APC_Game::InvenTimer, 0.01f, false);
	}
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

void APC_Game::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ToggleInventory",IE_Pressed,this,&APC_Game::OpenInventory);
}

void APC_Game::OpenInventory()
{
	if (ClientHUD)
	{
		Inven = ClientHUD->GetWidgetFromName(FString(TEXT("Inventory")));
		if (IsValid(Inven))
		{
			UUWInventory* Inventory = Cast<UUWInventory>(Inven);
			if (InvenIsOpen)
			{
				InvenIsOpen = !InvenIsOpen;
				ClientHUD->CleanWidgetFromName(FString(TEXT("Inventory")));
				FInputModeGameOnly InputMode;
				SetInputMode(InputMode);
				bShowMouseCursor = true;
			}
			else
			{
				InvenIsOpen = !InvenIsOpen;
				ClientHUD->ShowWidgetFromName(FString(TEXT("Inventory")));
				FInputModeGameAndUI InputMode;
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				InputMode.SetHideCursorDuringCapture(false);
				SetInputMode(InputMode);
				bShowMouseCursor = true;
			}
		}
	}
}

void APC_Game::InvenTimer()
{
	Inven = ClientHUD->GetWidgetFromName(FString(TEXT("Inventory")));
	if (IsValid(Inven))
	{
		UUWInventory* UWInventory = Cast<UUWInventory>(Inven);
		if (IsValid(GetPawn()))
		{
			AGameCharacter* GameCharacter = Cast<AGameCharacter>(GetPawn());
			if (IsValid(GameCharacter))
			{
				UWInventory->InitInventory(Cast<AGameCharacter>(GetPawn())->InventoryComponent, 50.0f);
			}
		}
	}
}
