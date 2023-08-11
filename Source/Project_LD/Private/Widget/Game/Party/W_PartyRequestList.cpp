// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Party/W_PartyRequestList.h"
#include <Widget/Game/Party/W_PartyPlayerCell.h>
#include <Widget/WidgetUtils.h>

#include <Components/ScrollBox.h>

#include <NetworkController.h>
#include <NetworkGameMode.h>

#include <FGamePacketHandler.h>
#include <NetworkUtils.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UW_PartyRequestList::NativeConstruct()
{
	Super::NativeConstruct();

	mPartyScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("mPartyScrollBox")));
}

void UW_PartyRequestList::NativeDestruct()
{
	Super::NativeDestruct();

	ClearPartyList();
}

void UW_PartyRequestList::ClearPartyList()
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

void UW_PartyRequestList::AddPartyList(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName)
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

			Protocol::C2S_ResponeParty responePartyPacket;
			responePartyPacket.set_nick_name(partyName);
			responePartyPacket.set_action(1);
			responePartyPacket.set_timestamp(networkController->GetServerTimeStamp());

			SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(networkController, responePartyPacket);
			networkController->Send(pakcetBuffer);

			clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));
		});

	newCell->mActionButtonDelegateA = actionButtonDelegatgeA;

	FPartyActionButtonDelegate actionButtonDelegatgeB;
	actionButtonDelegatgeB.BindLambda([=]()
		{
			std::string partyName = UNetworkUtils::ConvertString(inPlayerName);

			Protocol::C2S_ResponeParty responePartyPacket;
			responePartyPacket.set_nick_name(partyName);
			responePartyPacket.set_action(2);
			responePartyPacket.set_timestamp(networkController->GetServerTimeStamp());

			SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(networkController, responePartyPacket);
			networkController->Send(pakcetBuffer);

			clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));
		});

	newCell->mActionButtonDelegateB = actionButtonDelegatgeB;

	newCell->SetPlayerInfo(inRemoteID, inLevel, inClass, inPlayerName);
	newCell->SetListType(false, EPartyListType::RequestList, false);

	mPartyScrollBox->AddChild(newCell);
	mPartyScrollBox->ScrollToEnd();
}
