// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Friend/W_FriendRequestList.h"
#include <Widget/Game/Friend/W_FriendCell.h>
#include <Widget/WidgetUtils.h>

#include <Components/Button.h>
#include <Components/ScrollBox.h>

#include <NetworkController.h>
#include <NetworkGameMode.h>

#include <FGamePacketHandler.h>
#include <NetworkUtils.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UW_FriendRequestList::NativeConstruct()
{
	Super::NativeConstruct();

	mRequest = Cast<UButton>(GetWidgetFromName(TEXT("mRequest")));

	mFriendScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("mFriendScrollBox")));

	if (mRequest != nullptr)
	{
		mRequest->OnClicked.AddUniqueDynamic(this, &UW_FriendRequestList::Click_Request);
	}
}

void UW_FriendRequestList::NativeDestruct()
{
	Super::NativeDestruct();

	ClearFriendList();
}

void UW_FriendRequestList::Click_Request()
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

	FButtonDelegate buttonDelegate;
	buttonDelegate.BindLambda([=](const FString& inFriendName)
		{
			std::string friendName = UNetworkUtils::ConvertString(inFriendName);

			Protocol::C2S_RequestFriend requestPacket;
			requestPacket.set_nick_name(friendName);
			requestPacket.set_action(1);
			requestPacket.set_timestamp(networkController->GetServerTimeStamp());

			SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(networkController, requestPacket);
			networkController->Send(pakcetBuffer);

			clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));
			clientHUD->CleanWidgetFromName(TEXT("EditBox"));
		});

	UWidgetUtils::SetEditBox(clientHUD, TEXT("친구 요청"), TEXT("친구 이름"), TEXT("요청"), buttonDelegate);

}

void UW_FriendRequestList::ClearFriendList()
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

void UW_FriendRequestList::AddFriendList(const FString& inPlayerName)
{
	UW_FriendCell* newCell = Cast<UW_FriendCell>(CreateWidget(GetWorld(), mFriendCellClass));
	if (nullptr == newCell)
	{
		return;
	}
	newCell->SetPlayerName(inPlayerName);
	newCell->SetPlayerInfo(0, 0, 0, false);
	newCell->SetConnectStateImage(EConnectState::None, false);
	newCell->SetActionImage(EActionState::Request);

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

	FActionButtonDelegate actionButtonDelegatge;
	actionButtonDelegatge.BindLambda([=]()
		{
			std::string friendName = UNetworkUtils::ConvertString(inPlayerName);

			Protocol::C2S_RequestFriend requestPacket;
			requestPacket.set_nick_name(friendName);
			requestPacket.set_action(2);
			requestPacket.set_timestamp(networkController->GetServerTimeStamp());

			SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(networkController, requestPacket);
			networkController->Send(pakcetBuffer);

			clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));
		});

	newCell->mActionButtonDelegate = actionButtonDelegatge;

	mFriendScrollBox->AddChild(newCell);
	mFriendScrollBox->ScrollToEnd();
}
