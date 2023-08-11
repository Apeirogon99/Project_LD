// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Party/W_PartyPlayerList.h"
#include <Widget/Game/Party/W_PartyPlayerCell.h>
#include <Widget/WidgetUtils.h>

#include <Components/ScrollBox.h>

#include <NetworkController.h>
#include <NetworkGameMode.h>

#include <FGamePacketHandler.h>
#include <NetworkUtils.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UW_PartyPlayerList::NativeConstruct()
{
	Super::NativeConstruct();

	mPartyScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("mPartyScrollBox")));
}

void UW_PartyPlayerList::NativeDestruct()
{
	Super::NativeDestruct();

	ClearPartyList();
}

void UW_PartyPlayerList::ClearPartyList()
{
	for (UUserWidget* widget : mPartyPlayerLists)
	{
		widget->RemoveFromParent();
	}

	for (int32 ChildIndex = mPartyScrollBox->GetChildrenCount() - 1; ChildIndex >= 0; ChildIndex--)
	{
		mPartyScrollBox->RemoveChildAt(ChildIndex);
	}

	mPartyScrollBox->ClearChildren();
}

void UW_PartyPlayerList::AddPartyList(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsSelf, const bool& inIsLeader)
{
	UW_PartyPlayerCell* newCell = Cast<UW_PartyPlayerCell>(CreateWidget(GetWorld(), mPartyPlayerCellClass));
	if (nullptr == newCell)
	{
		return;
	}

	ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
	if (nullptr == gameMode)
	{
		return;

	}

	APlayerController* owningController = GetOwningPlayer();
	if (nullptr == owningController)
	{
		return;

	}

	ANetworkController* networkController = Cast<ANetworkController>(owningController);
	if (nullptr == networkController)
	{
		return;

	}

	AClientHUD* clientHUD = gameMode->GetClientHUD();
	if (nullptr == clientHUD)
	{
		return;

	}

	FPartyActionButtonDelegate actionButtonDelegatgeA;
	actionButtonDelegatgeA.BindLambda([=]()
		{
			std::string partyName = UNetworkUtils::ConvertString(inPlayerName);

			Protocol::C2S_RequestLeaderParty leaderPartyPacket;
			leaderPartyPacket.set_nick_name(partyName);
			leaderPartyPacket.set_timestamp(networkController->GetServerTimeStamp());

			SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(networkController, leaderPartyPacket);
			networkController->Send(pakcetBuffer);

			clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));
		});

	newCell->mActionButtonDelegateA = actionButtonDelegatgeA;

	FPartyActionButtonDelegate actionButtonDelegatgeB;
	actionButtonDelegatgeB.BindLambda([=]()
		{
			std::string partyName = UNetworkUtils::ConvertString(inPlayerName);

			Protocol::C2S_RequestLeaveParty leavePartyPacket;
			leavePartyPacket.set_nick_name(partyName);
			leavePartyPacket.set_timestamp(networkController->GetServerTimeStamp());

			SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(networkController, leavePartyPacket);
			networkController->Send(pakcetBuffer);

			clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));
		});

	newCell->mActionButtonDelegateB = actionButtonDelegatgeB;

	newCell->SetPlayerInfo(inRemoteID, inLevel, inClass, inPlayerName);
	newCell->SetListType(inIsSelf, EPartyListType::PlayerList, inIsLeader);

	mPartyScrollBox->AddChild(newCell);
	mPartyScrollBox->ScrollToEnd();
}

void UW_PartyPlayerList::RemovePartyList(const int64& inRemoteID)
{
	for (UUserWidget* widget : mPartyPlayerLists)
	{
		UW_PartyPlayerCell* partyWidget = Cast<UW_PartyPlayerCell>(widget);
		if (nullptr == partyWidget)
		{
			return;
		}

		if (inRemoteID == partyWidget->GetRemoteID())
		{
			widget->RemoveFromParent();
			mPartyPlayerLists.Remove(widget);
			break;
		}
	}

	mPartyScrollBox->ClearChildren();
	for (UUserWidget* widget : mPartyPlayerLists)
	{
		mPartyScrollBox->AddChild(widget);
	}
	mPartyScrollBox->ScrollToEnd();
}
