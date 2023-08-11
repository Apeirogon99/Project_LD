// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Friend/W_FriendList.h"
#include <Widget/Game/Friend/W_FriendCell.h>
#include <Widget/WidgetUtils.h>

#include <Components/ScrollBox.h>

#include <NetworkController.h>
#include <NetworkGameMode.h>

#include <FGamePacketHandler.h>
#include <NetworkUtils.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UW_FriendList::NativeConstruct()
{
	Super::NativeConstruct();

	mFriendScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("mFriendScrollBox")));
}

void UW_FriendList::NativeDestruct()
{
	Super::NativeDestruct();

	ClearFriendList();
}

void UW_FriendList::ClearFriendList()
{
	for (UUserWidget* widget : mFriendLists)
	{
		widget->RemoveFromParent();
	}

	for (int32 ChildIndex = mFriendScrollBox->GetChildrenCount() - 1; ChildIndex >= 0; ChildIndex--)
	{
		mFriendScrollBox->RemoveChildAt(ChildIndex);
	}

	mFriendScrollBox->ClearChildren();
}

void UW_FriendList::AddFriendList(const FString& inPlayerName, const int32& inLevel, const int32& inClass, const int32& inLocale, const int32& inState)
{
	UW_FriendCell* newCell = Cast<UW_FriendCell>(CreateWidget(GetWorld(), mFriendCellClass));
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

	newCell->SetPlayerName(inPlayerName);
	newCell->SetPlayerInfo(inLevel, inClass, inLocale, true);
	newCell->SetConnectStateImage(StaticCast<EConnectState>(inState), true);
	newCell->SetActionImage(EActionState::Invite);

	FActionButtonDelegate actionButtonDelegatge;
	actionButtonDelegatge.BindLambda([=]()
		{
			std::string partyName = UNetworkUtils::ConvertString(inPlayerName);

			Protocol::C2S_RequestEnterParty requestPartyPacket;
			requestPartyPacket.set_nick_name(partyName);
			requestPartyPacket.set_timestamp(networkController->GetServerTimeStamp());

			SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(networkController, requestPartyPacket);
			networkController->Send(pakcetBuffer);

			clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));
		});

	newCell->mActionButtonDelegate = actionButtonDelegatge;

	mFriendScrollBox->AddChild(newCell);
	mFriendScrollBox->ScrollToEnd();
}
