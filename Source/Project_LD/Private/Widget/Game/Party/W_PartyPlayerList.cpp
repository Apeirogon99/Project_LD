// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Party/W_PartyPlayerList.h"
#include <Widget/Game/Party/W_PartyPlayerCell.h>
#include <Widget/WidgetUtils.h>

#include <Components/ScrollBox.h>
#include <Components/Button.h>

#include <NetworkController.h>
#include <NetworkGameMode.h>

#include <FGamePacketHandler.h>
#include <NetworkUtils.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UW_PartyPlayerList::NativeConstruct()
{
	Super::NativeConstruct();

	mPartyScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("mPartyScrollBox")));

	mCreateParty = Cast<UButton>(GetWidgetFromName(TEXT("mCreateParty")));

	if (mCreateParty != nullptr)
	{
		mCreateParty->OnClicked.AddUniqueDynamic(this, &UW_PartyPlayerList::Click_CreateParty);
	}

	ClearPartyList();

	UpdatePartyList();
}

void UW_PartyPlayerList::NativeDestruct()
{
	Super::NativeDestruct();

	ClearPartyList();
}

void UW_PartyPlayerList::Click_CreateParty()
{
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

	if (0 == this->GetPartyPlayerListNumber())
	{
		Protocol::C2S_CreateParty createPartyPacket;
		createPartyPacket.set_timestamp(networkController->GetServerTimeStamp());

		SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(networkController, createPartyPacket);
		networkController->Send(pakcetBuffer);

		clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));
	}
}

void UW_PartyPlayerList::ClearPartyList()
{
	for (UUserWidget* widget : mPartyPlayerLists)
	{
		widget->RemoveFromParent();
	}
	mPartyPlayerLists.Empty();

	for (int32 ChildIndex = mPartyScrollBox->GetChildrenCount() - 1; ChildIndex >= 0; ChildIndex--)
	{
		mPartyScrollBox->RemoveChildAt(ChildIndex);
	}
	mPartyScrollBox->ClearChildren();


	OnChangeCreateWidget(true);
}

void UW_PartyPlayerList::AddPartyList(const int64& inRemoteID, const int64& inLeaderRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsSelf)
{
	UW_PartyPlayerCell* newCell = Cast<UW_PartyPlayerCell>(CreateWidget(GetWorld(), mPartyPlayerCellClass));
	if (nullptr == newCell)
	{
		return;
	}

	mPartyPlayerLists.Push(newCell);

	mPartyScrollBox->AddChild(newCell);
	mPartyScrollBox->ScrollToEnd();

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
			Protocol::C2S_RequestLeaderParty leaderPartyPacket;
			leaderPartyPacket.set_remote_id(inRemoteID);
			leaderPartyPacket.set_timestamp(networkController->GetServerTimeStamp());

			SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(networkController, leaderPartyPacket);
			networkController->Send(pakcetBuffer);

			clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));
		});

	newCell->mActionButtonDelegateA = actionButtonDelegatgeA;

	FPartyActionButtonDelegate actionButtonDelegatgeB;
	actionButtonDelegatgeB.BindLambda([=]()
		{
			Protocol::C2S_RequestLeaveParty leavePartyPacket;
			leavePartyPacket.set_remote_id(inRemoteID);
			leavePartyPacket.set_timestamp(networkController->GetServerTimeStamp());

			SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(networkController, leavePartyPacket);
			networkController->Send(pakcetBuffer);

			clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));
		});

	newCell->mActionButtonDelegateB = actionButtonDelegatgeB;

	newCell->SetPlayerInfo(inRemoteID, inLevel, inClass, inPlayerName);
	newCell->SetListType(inIsSelf, inLeaderRemoteID, EPartyListType::PlayerList);

	UpdatePartyList();
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

	UpdatePartyList();
}

void UW_PartyPlayerList::UpdatePartyList()
{
	if (0 == this->GetPartyPlayerListNumber())
	{
		OnChangeCreateWidget(true);
	}
	else
	{
		OnChangeCreateWidget(false);
	}
}

bool UW_PartyPlayerList::OnChangeCreateWidget_Implementation(bool isCreate)
{
	return false;
}

int32 UW_PartyPlayerList::GetPartyPlayerListNumber()
{
	return mPartyPlayerLists.Num();
}
