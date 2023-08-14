// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Party/W_PartyMain.h"
#include "Widget/Game/Party/W_PartyNotify.h"
#include "Widget/Game/Party/W_PartyPlayerCell.h"
#include "Widget/Game/Party/W_PartyPlayerInfo.h"
#include "Widget/Game/Party/W_PartyPlayerInfoList.h"
#include "Widget/Game/Party/W_PartyPlayerList.h"
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
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UW_PartyMain::NativeConstruct()
{
	Super::NativeConstruct();

	mPlayerListTab = Cast<UButton>(GetWidgetFromName(TEXT("mPlayerListTab")));
	mRequestPartyTab = Cast<UButton>(GetWidgetFromName(TEXT("mRequestPartyTab")));
	mRequestListTab = Cast<UButton>(GetWidgetFromName(TEXT("mRequestListTab")));

	mPlayerCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("mPlayerCount")));

	mDragButton = Cast<UButton>(GetWidgetFromName(TEXT("mDragButton")));

	mResponeImage = Cast<UImage>(GetWidgetFromName(TEXT("mResponeImage")));

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
		UW_PartyPlayerList* widget = Cast<UW_PartyPlayerList>(mPartyPlayerList);
		if (nullptr == widget)
		{
			return;
		}

		FString countText;
		countText.Append(FString::FromInt(widget->GetPartyPlayerListNumber()));
		countText.Append(TEXT(" / 4"));
		mPlayerCount->SetText(FText::FromString(countText));
	}

	mPartyRequesrList = this->WidgetTree->FindWidget(FName(TEXT("BW_PartyRequestList")));
	if (mPartyRequesrList != nullptr)
	{
		UW_PartyRequestList* widget = Cast<UW_PartyRequestList>(mPartyRequesrList);
		if (nullptr == widget)
		{
			return;
		}

		if (widget->GetRequestPartyPlayerListNumber())
		{
			mResponeImage->SetBrushFromTexture(mHaveRequestListTexture);
		}
		else
		{
			mResponeImage->SetBrushFromTexture(mNotHaveRequestListTexture);
		}
	}
}

void UW_PartyMain::NativeDestruct()
{
	UW_PartyPlayerList* playerList = Cast<UW_PartyPlayerList>(mPartyPlayerList);
	if (nullptr == playerList)
	{
		return;
	}
	playerList->RemoveFromParent();

	UW_PartyRequestList* requestList = Cast<UW_PartyRequestList>(mPartyRequesrList);
	if (nullptr == requestList)
	{
		return;
	}
	requestList->RemoveFromParent();
}

void UW_PartyMain::ClearPlayerList()
{
	UW_PartyPlayerList* widget = Cast<UW_PartyPlayerList>(mPartyPlayerList);
	if (nullptr == widget)
	{
		return;
	}
	widget->ClearPartyList();

	FString countText;
	countText.Append(FString::FromInt(widget->GetPartyPlayerListNumber()));
	countText.Append(TEXT(" / 4"));
	mPlayerCount->SetText(FText::FromString(countText));
}

void UW_PartyMain::PushPlayerList(const int64& inRemoteID, const int64& inLeaderRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsSelf)
{
	UW_PartyPlayerList* widget = Cast<UW_PartyPlayerList>(mPartyPlayerList);
	if (nullptr == widget)
	{
		return;
	}
	widget->AddPartyList(inRemoteID, inLeaderRemoteID, inLevel, inClass, inPlayerName, inIsSelf);

	FString countText;
	countText.Append(FString::FromInt(widget->GetPartyPlayerListNumber()));
	countText.Append(TEXT(" / 4"));
	mPlayerCount->SetText(FText::FromString(countText));
}

void UW_PartyMain::ReleasePlayerList(const int64& inRemoteID)
{
	UW_PartyPlayerList* widget = Cast<UW_PartyPlayerList>(mPartyPlayerList);
	if (nullptr == widget)
	{
		return;
	}
	widget->RemovePartyList(inRemoteID);

	FString countText;
	countText.Append(FString::FromInt(widget->GetPartyPlayerListNumber()));
	countText.Append(TEXT(" / 4"));
	mPlayerCount->SetText(FText::FromString(countText));
}

void UW_PartyMain::ClearRequestList()
{
	UW_PartyRequestList* widget = Cast<UW_PartyRequestList>(mPartyRequesrList);
	if (nullptr == widget)
	{
		return;
	}
	widget->ClearPartyList();
}

void UW_PartyMain::PushRequestList(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName)
{
	UW_PartyRequestList* widget = Cast<UW_PartyRequestList>(mPartyRequesrList);
	if (nullptr == widget)
	{
		return;
	}
	widget->AddRequestPartyList(inRemoteID, inLevel, inClass, inPlayerName);

	if (widget->GetRequestPartyPlayerListNumber())
	{
		mResponeImage->SetBrushFromTexture(mHaveRequestListTexture);
	}
}

void UW_PartyMain::ReleaseRequestList(const int64& inRemoteID)
{
	UW_PartyRequestList* widget = Cast<UW_PartyRequestList>(mPartyRequesrList);
	if (nullptr == widget)
	{
		return;
	}
	widget->RemoveRequestPartyList(inRemoteID);

	if (0 == widget->GetRequestPartyPlayerListNumber())
	{
		mResponeImage->SetBrushFromTexture(mNotHaveRequestListTexture);
	}
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

	{
		UW_PartyPlayerList* widget = Cast<UW_PartyPlayerList>(mPartyPlayerList);
		if (nullptr == widget)
		{
			return;
		}

		if (0 == widget->GetPartyPlayerListNumber())
		{
			FNotificationDelegate notificationDelegate;
			notificationDelegate.BindLambda([=]()
				{
					clientHUD->CleanWidgetFromName(TEXT("Notification"));
				});

			bool ret = UWidgetUtils::SetNotification(clientHUD, TEXT("파티 생성"), TEXT("먼저 파티를 생성해 주세요"), TEXT("확인"), notificationDelegate);
			if (ret == false)
			{
				return;
			}

			return;
		}

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
