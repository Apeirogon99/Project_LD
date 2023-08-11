// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Party/W_PartyMain.h"
#include "Widget/Game/Party/W_PartyNotify.h"
#include "Widget/Game/Party/W_PartyPlayerCell.h"
#include "Widget/Game/Party/W_PartyPlayerInfo.h"
#include "Widget/Game/Party/W_PartyPlayerInfoList.h"
#include "Widget/Game/Party/W_PartyRequestList.h"
#include "Widget/Game/Party/W_PlayerBuffInfo.h"

#include <Widget/WidgetUtils.h>
#include <Protobuf/Handler/PacketUtils.h>
#include <FGamePacketHandler.h>
#include <NetworkUtils.h>
#include <Blueprint/WidgetLayoutLibrary.h>

#include <Game/GM_Game.h>
#include <Game/PC_Game.h>

#include <Blueprint/WidgetTree.h>

#include <Components/Button.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UW_PartyMain::NativeConstruct()
{
	Super::NativeConstruct();

	mPlayerListTab = Cast<UButton>(GetWidgetFromName(TEXT("mPlayerListTab")));
	mRequestPartyTab = Cast<UButton>(GetWidgetFromName(TEXT("mRequestPartyTab")));
	mRequestListTab = Cast<UButton>(GetWidgetFromName(TEXT("mRequestListTab")));

	mDragButton = Cast<UButton>(GetWidgetFromName(TEXT("mDragButton")));

	if (mPlayerListTab != nullptr)
	{
		mPlayerListTab->OnClicked.AddUniqueDynamic(this, &UW_PartyMain::Click_PartyListTab);
	}

	if (mRequestPartyTab != nullptr)
	{
		mRequestPartyTab->OnClicked.AddUniqueDynamic(this, &UW_PartyMain::Click_RequestPartyTab);
	}

	if (mRequestListTab != nullptr)
	{
		mRequestListTab->OnClicked.AddUniqueDynamic(this, &UW_PartyMain::Click_RequestListTab);
	}

	if (mDragButton != nullptr)
	{
		mDragButton->OnPressed.AddUniqueDynamic(this, &UW_PartyMain::Pressed_Drag);
		mDragButton->OnReleased.AddUniqueDynamic(this, &UW_PartyMain::Released_Drag);
	}

	mPartyPlayerList = this->WidgetTree->FindWidget(FName(TEXT("BW_PartyPlayerList")));
	if (mPartyPlayerList != nullptr)
	{

	}

	mPartyRequesrList = this->WidgetTree->FindWidget(FName(TEXT("BW_PartyRequestList")));
	if (mPartyRequesrList != nullptr)
	{

	}
}

void UW_PartyMain::NativeDestruct()
{
}

void UW_PartyMain::Click_PartyListTab()
{
	OnPlayerListTab();
}

void UW_PartyMain::Click_RequestPartyTab()
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

			Protocol::C2S_RequestEnterParty requestPacket;
			requestPacket.set_nick_name(friendName);
			requestPacket.set_timestamp(networkController->GetServerTimeStamp());

			SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(networkController, requestPacket);
			networkController->Send(pakcetBuffer);

			clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));
			clientHUD->CleanWidgetFromName(TEXT("EditBox"));
		});

	UWidgetUtils::SetEditBox(clientHUD, TEXT("파티 요청"), TEXT("친구 이름"), TEXT("요청"), buttonDelegate);
}

void UW_PartyMain::Click_RequestListTab()
{
	OnRequestListTab();
}

void UW_PartyMain::OnPlayerListTab_Implementation()
{
}

void UW_PartyMain::OnRequestListTab_Implementation()
{
}

void UW_PartyMain::UpdateLocation()
{
	float WaitTime = 0.01f;
	GetWorld()->GetTimerManager().SetTimer(mUpdateLocationTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			FVector2D currentMousePoint = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());

			FWidgetTransform widgetTransform;
			widgetTransform.Translation = currentMousePoint - mPressedMousePoint;
			widgetTransform.Scale = FVector2D(1, 1);
			widgetTransform.Shear = FVector2D(0, 0);
			widgetTransform.Angle = 0.0f;
			SetRenderTransform(widgetTransform);

		}), WaitTime, true);
}

void UW_PartyMain::Pressed_Drag()
{
	FVector2D currentMousePoint = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2D currentViewportPoint = RenderTransform.Translation;
	mPressedMousePoint = currentMousePoint - currentViewportPoint;
	UpdateLocation();
}

void UW_PartyMain::Released_Drag()
{
	if (true == GetWorld()->GetTimerManager().IsTimerActive(mUpdateLocationTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(mUpdateLocationTimerHandle);
	}
}
