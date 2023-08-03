// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Main/W_MainGame.h"
#include <Widget/Handler/ClientHUD.h>
#include <Widget/Game/Chat/W_Chat.h>
#include <Widget/Game/Main/W_BottomUI.h>
#include "Components/Button.h"
#include "Blueprint/WidgetTree.h"

#include <Game/GM_Game.h>
#include <Game/PC_Game.h>

#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>

void UW_MainGame::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Inventory = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Inventory")));
	if (Btn_Inventory != nullptr)
	{
		Btn_Inventory->OnClicked.AddDynamic(this, &UW_MainGame::InventoryOpenRequest);
	}

	Btn_Chat = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Chat")));
	if (Btn_Inventory != nullptr)
	{
		Btn_Chat->OnClicked.AddUniqueDynamic(this, &UW_MainGame::ChatOpen);
	}

	mBottomUI = this->WidgetTree->FindWidget(FName(TEXT("BW_BottomUI")));
	if (mBottomUI == nullptr)
	{
		return;
	}

	misInventoryOpen = false;
	misChatOpen = false;
}

void UW_MainGame::Init()
{
	Cast<UW_BottomUI>(mBottomUI)->Init();
}

void UW_MainGame::ChatOpen()
{
	AGM_Game* gamemode = Cast<AGM_Game>(GetWorld()->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}

	APC_Game* playerController = Cast<APC_Game>(gamemode->GetNetworkController());
	if (GetOwningPlayer() != playerController)
	{
		return;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(gamemode->GetClientHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	if (misChatOpen)
	{
		clientHUD->CleanWidgetFromName(FString(TEXT("Chat")));
	}
	else
	{
		clientHUD->ShowWidgetFromName(FString(TEXT("Chat")));
	}
	misChatOpen = !misChatOpen;
}

void UW_MainGame::FocusChat()
{
	AGM_Game* gamemode = Cast<AGM_Game>(GetWorld()->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}

	APC_Game* playerController = Cast<APC_Game>(gamemode->GetNetworkController());
	if (GetOwningPlayer() != playerController)
	{
		return;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(gamemode->GetClientHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("Chat")));
	if (nullptr == widget)
	{
		return;
	}

	clientHUD->ShowWidgetFromName(FString(TEXT("Chat")));
	misChatOpen = true;

	UW_Chat* chat = Cast<UW_Chat>(widget);
	if (nullptr == chat)
	{
		return;
	}
	chat->FocusChat();

}

void UW_MainGame::InventoryOpenRequest()
{
	AGM_Game* gamemode = Cast<AGM_Game>(GetWorld()->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}

	APC_Game* playerController = Cast<APC_Game>(gamemode->GetNetworkController());
	if(GetOwningPlayer()!=playerController)
	{
		return;
	}
	
	AClientHUD* clientHUD = Cast<AClientHUD>(gamemode->GetClientHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	if (misInventoryOpen)
	{
		misInventoryOpen = !misInventoryOpen;
		clientHUD->CleanWidgetFromName(FString(TEXT("Inventory")));
		playerController->SwitchMovementMode();
	}
	else
	{
		Protocol::C2S_LoadInventory loadInventoryPacket;
		const int64 serverTimeStamp = playerController->GetServerTimeStamp();
		loadInventoryPacket.set_timestamp(serverTimeStamp);
		playerController->Send(FGamePacketHandler::MakeSendBuffer(playerController, loadInventoryPacket));
	}
}

void UW_MainGame::InventoryOpenResponse()
{
	AGM_Game* gamemode = Cast<AGM_Game>(GetWorld()->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}

	APC_Game* playerController = Cast<APC_Game>(gamemode->GetNetworkController());
	if (GetOwningPlayer() != playerController)
	{
		return;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(gamemode->GetClientHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	misInventoryOpen = !misInventoryOpen;
	clientHUD->ShowWidgetFromName(FString(TEXT("Inventory")));
	playerController->SwitchUIMode();
	
}
