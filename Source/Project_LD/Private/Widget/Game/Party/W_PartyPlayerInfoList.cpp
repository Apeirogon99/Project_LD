// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Party/W_PartyPlayerInfoList.h"
#include <Widget/Game/Party/W_PartyPlayerInfo.h>
#include <Widget/WidgetUtils.h>

#include <Components/ScrollBox.h>

#include <NetworkController.h>
#include <NetworkGameMode.h>

#include <FGamePacketHandler.h>
#include <NetworkUtils.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UW_PartyPlayerInfoList::NativeConstruct()
{
	Super::NativeConstruct();

	mPartyPlayerInfoScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("mPartyPlayerInfoScrollBox")));
}

void UW_PartyPlayerInfoList::NativeDestruct()
{
	Super::NativeDestruct();

	ClearPartyPlayerInfoList();
}

void UW_PartyPlayerInfoList::ClearPartyPlayerInfoList()
{
	for (UUserWidget* widget : mPartyPlayerInfoLists)
	{
		widget->RemoveFromParent();
	}

	for (int32 ChildIndex = mPartyPlayerInfoScrollBox->GetChildrenCount() - 1; ChildIndex >= 0; ChildIndex--)
	{
		mPartyPlayerInfoScrollBox->RemoveChildAt(ChildIndex);
	}

	mPartyPlayerInfoScrollBox->ClearChildren();
}

void UW_PartyPlayerInfoList::AddPartyList(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsLeader)
{
	UW_PartyPlayerInfo* newCell = Cast<UW_PartyPlayerInfo>(CreateWidget(GetWorld(), mPartyPlayerInfoClass));
	if (nullptr == newCell)
	{
		return;
	}
	newCell->SetPlayerInfo(inRemoteID, inLevel, inClass, inPlayerName, inIsLeader);

	mPartyPlayerInfoScrollBox->AddChild(newCell);
	mPartyPlayerInfoScrollBox->ScrollToEnd();
}

void UW_PartyPlayerInfoList::RemovePartyPlayerInfo(const int64& inRemoteID)
{
	for (UUserWidget* widget : mPartyPlayerInfoLists)
	{
		UW_PartyPlayerInfo* infoWidget = Cast<UW_PartyPlayerInfo>(widget);
		if (nullptr == infoWidget)
		{
			return;
		}

		if (inRemoteID == infoWidget->GetRemoteID())
		{
			widget->RemoveFromParent();
			mPartyPlayerInfoLists.Remove(widget);
			break;
		}
	}

	mPartyPlayerInfoScrollBox->ClearChildren();
	for (UUserWidget* widget : mPartyPlayerInfoLists)
	{
		mPartyPlayerInfoScrollBox->AddChild(widget);
	}
	mPartyPlayerInfoScrollBox->ScrollToEnd();
}
