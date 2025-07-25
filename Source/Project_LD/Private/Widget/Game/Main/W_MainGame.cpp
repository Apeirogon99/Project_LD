// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Main/W_MainGame.h"
#include <Widget/Handler/ClientHUD.h>
#include <Widget/Game/Chat/W_Chat.h>

#include <Widget/Game/Main/W_BottomUI.h>
#include <Widget/Game/Main/W_MainPlayerInfo.h>

#include <Widget/Game/Friend/W_FriendMain.h>
#include <Widget/Game/Friend/W_NotifyFriend.h>

#include <Widget/Game/Party/W_PartyNotify.h>
#include <Widget/Game/Party/W_PartyPlayerInfo.h>
#include <Widget/Game/Party/W_PartyPlayerInfoList.h>
#include <Widget/Game/Party/W_PartyMain.h>

#include "Components/Border.h"
#include "Components/Button.h"
#include "Blueprint/WidgetTree.h"

#include <Game/GM_Game.h>
#include <Game/PC_Game.h>

#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>

void UW_MainGame::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerSightBorder = Cast<UBorder>(GetWidgetFromName(TEXT("PlayerSightBorder")));
	if (PlayerSightBorder == nullptr)
	{
		return;
	}

	Btn_Inventory = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Inventory")));
	if (Btn_Inventory != nullptr)
	{
		Btn_Inventory->OnClicked.AddUniqueDynamic(this, &UW_MainGame::InventoryOpenRequest);
	}

	Btn_Chat = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Chat")));
	if (Btn_Inventory != nullptr)
	{
		Btn_Chat->OnClicked.AddUniqueDynamic(this, &UW_MainGame::ChatOpen);
	}

	Btn_Friend = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Friend")));
	if (Btn_Friend != nullptr)
	{
		Btn_Friend->OnClicked.AddUniqueDynamic(this, &UW_MainGame::FriendOpenRequest);
	}

	Btn_Party = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Party")));
	if (Btn_Party != nullptr)
	{
		Btn_Party->OnClicked.AddUniqueDynamic(this, &UW_MainGame::PartyOpenRequest);
	}

	misInventoryOpen = false;
	misChatOpen = false;
	misFriendOpen = false;
	misPartyOpen = false;
}

void UW_MainGame::NativeDestruct()
{
	Super::NativeDestruct();

	if (mBottomUI != nullptr)
	{
		mBottomUI = nullptr;
	}
	if (mMainPlayerInfo != nullptr)
	{
		mMainPlayerInfo = nullptr;
	}
	if (PlayerSightBorder != nullptr)
	{
		PlayerSightBorder = nullptr;
	}
	if (Btn_Chat != nullptr)
	{
		Btn_Chat = nullptr;
	}
	if (Btn_Inventory != nullptr)
	{
		Btn_Inventory = nullptr;
	}
	if (Btn_Friend != nullptr)
	{
		Btn_Friend = nullptr;
	}
	if (Btn_Party != nullptr)
	{
		Btn_Party = nullptr;
	}
	if (mNotifyFriend != nullptr)
	{
		mNotifyFriend = nullptr;
	}
	if (mNotifyParty != nullptr)
	{
		mNotifyParty = nullptr;
	}
	if (mPartyPlayerInfoList != nullptr)
	{
		mPartyPlayerInfoList = nullptr;
	}
}

void UW_MainGame::Init()
{
	mBottomUI = this->WidgetTree->FindWidget(FName(TEXT("BottomUI")));
	if (mBottomUI == nullptr)
	{
		return;
	}

	mMainPlayerInfo = this->WidgetTree->FindWidget(FName(TEXT("MainPlayerInfo")));
	if (mMainPlayerInfo == nullptr)
	{
		return;
	}

	mPartyPlayerInfoList = this->WidgetTree->FindWidget(FName(TEXT("PartyPlayerInfoList")));
	if (mPartyPlayerInfoList == nullptr)
	{
		return;
	}

	mNotifyFriend = this->WidgetTree->FindWidget(FName(TEXT("NotifyFriend")));
	if (mNotifyFriend != nullptr)
	{
		UW_NotifyFriend* notify = Cast<UW_NotifyFriend>(mNotifyFriend);
		notify->SetVisibility(ESlateVisibility::Hidden);
	}

	mNotifyParty = this->WidgetTree->FindWidget(FName(TEXT("NotifyParty")));
	if (mNotifyParty != nullptr)
	{
		UW_PartyNotify* notify = Cast<UW_PartyNotify>(mNotifyParty);
		notify->SetVisibility(ESlateVisibility::Hidden);
	}

	Cast<UW_BottomUI>(mBottomUI)->Init();
	Cast<UW_MainPlayerInfo>(mMainPlayerInfo)->Init();
}

void UW_MainGame::ChatOpen()
{
	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
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
	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
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

void UW_MainGame::FriendOpenRequest()
{
	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
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

	if (misFriendOpen)
	{
		misFriendOpen = !misFriendOpen;
		clientHUD->CleanWidgetFromName(FString(TEXT("FriendMain")));
	}
	else
	{
		const int64 serverTimeStamp = playerController->GetServerTimeStamp();
		const int32 listType = Cast<UW_FriendMain>(clientHUD->GetWidgetFromName(FString(TEXT("FriendMain"))))->GetFriendListType();

		Protocol::C2S_LoadFriendList loadFriendPacket;
		loadFriendPacket.set_list_type(listType);
		loadFriendPacket.set_timestamp(serverTimeStamp);
		playerController->Send(FGamePacketHandler::MakeSendBuffer(playerController, loadFriendPacket));
	}
}

void UW_MainGame::FriendOpenResponse(const google::protobuf::RepeatedPtrField<Protocol::SFriend>& inFriends, const int32& inListType)
{
	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
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

	misFriendOpen = !misFriendOpen;
	Cast<UW_FriendMain>(clientHUD->GetWidgetFromName(FString(TEXT("FriendMain"))))->LoadFriendListType(inFriends, inListType);
	clientHUD->ShowWidgetFromName(FString(TEXT("FriendMain")));
}

void UW_MainGame::PartyOpenRequest()
{
	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
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

	if (misPartyOpen)
	{
		clientHUD->CleanWidgetFromName(FString(TEXT("PartyMain")));
	}
	else
	{
		clientHUD->ShowWidgetFromName(FString(TEXT("PartyMain")));
	}
	misPartyOpen = !misPartyOpen;
}

void UW_MainGame::ClearPartyPlayerInfo()
{
	UW_PartyPlayerInfoList* list = Cast<UW_PartyPlayerInfoList>(mPartyPlayerInfoList);
	if (nullptr == list)
	{
		return;
	}
	list->ClearPartyPlayerInfoList();
}

void UW_MainGame::PushPartyPlayerInfo(const int64& inRemoteID, const int64& inLeaderRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsSelf)
{
	UW_PartyPlayerInfoList* list = Cast<UW_PartyPlayerInfoList>(mPartyPlayerInfoList);
	if (nullptr == list)
	{
		return;
	}

	list->AddPartyList(inRemoteID, inLeaderRemoteID, inLevel, inClass, inPlayerName, inIsSelf);
}

void UW_MainGame::ReleasePartyPlayerInfo(const int64& inRemoteID)
{
	UW_PartyPlayerInfoList* list = Cast<UW_PartyPlayerInfoList>(mPartyPlayerInfoList);
	if (nullptr == list)
	{
		return;
	}

	list->RemovePartyPlayerInfo(inRemoteID);
}

void UW_MainGame::FriendNotifyGame(const FString& inPlayerName, const bool& inConnect)
{
	UW_NotifyFriend* notify = Cast<UW_NotifyFriend>(mNotifyFriend);
	if (nullptr == notify)
	{
		return;
	}

	notify->SetNotifyFriend(inPlayerName, inConnect);
}

void UW_MainGame::PartyNotifyGame(const FString& inPlayerName, const int32& inAction)
{
	UW_PartyNotify* notify = Cast<UW_PartyNotify>(mNotifyParty);
	if (nullptr == notify)
	{
		return;
	}

	notify->SetNotifyParty(inPlayerName, inAction);
}

void UW_MainGame::InventoryOpenRequest()
{
	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
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
		clientHUD->ShowWidgetFromName(FString(TEXT("Minimap")));
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
	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
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
	clientHUD->CleanWidgetFromName(FString(TEXT("Minimap")));
	clientHUD->ShowWidgetFromName(FString(TEXT("Inventory")));
	playerController->SwitchUIMode();
	
}

void UW_MainGame::SkillTreeOpenRequest()
{
	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
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

	if (misSkillTreeOpen)
	{
		clientHUD->CleanWidgetFromName(FString(TEXT("SkillTree")));
	}
	else
	{
		clientHUD->ShowWidgetFromName(FString(TEXT("SkillTree")));
	}
	misSkillTreeOpen = !misSkillTreeOpen;
}

void UW_MainGame::SkillTreeOpenResponse()
{
}
