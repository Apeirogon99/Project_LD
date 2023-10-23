// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Party/W_PartyPlayerInfoList.h"
#include <Widget/Game/Party/W_PartyPlayerInfo.h>
#include <Widget/WidgetUtils.h>

#include <Components/ScrollBox.h>
#include <Components/Button.h>

#include <NetworkController.h>
#include <NetworkGameMode.h>

#include <FGamePacketHandler.h>
#include <NetworkUtils.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UW_PartyPlayerInfoList::NativeConstruct()
{
	Super::NativeConstruct();

	mPartyPlayerInfoScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("mPartyPlayerInfoScrollBox")));
	mDragButton = Cast<UButton>(GetWidgetFromName(TEXT("mDragButton")));

	if (mDragButton != nullptr)
	{
		mDragButton->OnPressed.AddUniqueDynamic(this, &UW_PartyPlayerInfoList::Pressed_Drag);
		mDragButton->OnReleased.AddUniqueDynamic(this, &UW_PartyPlayerInfoList::Released_Drag);
	}

	ClearPartyPlayerInfoList();

	this->SetVisibility(ESlateVisibility::Hidden);
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
	mPartyPlayerInfoLists.Empty();

	for (int32 ChildIndex = mPartyPlayerInfoScrollBox->GetChildrenCount() - 1; ChildIndex >= 0; ChildIndex--)
	{
		mPartyPlayerInfoScrollBox->RemoveChildAt(ChildIndex);
	}

	mPartyPlayerInfoScrollBox->ClearChildren();
}

void UW_PartyPlayerInfoList::AddPartyList(const int64& inRemoteID, const int64& inLeaderRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsSelf)
{
	UW_PartyPlayerInfo* newCell = Cast<UW_PartyPlayerInfo>(CreateWidget(GetWorld(), mPartyPlayerInfoClass));
	if (nullptr == newCell)
	{
		return;
	}
	newCell->SetPlayerInfo(inRemoteID, inLeaderRemoteID, inLevel, inClass, inPlayerName, inIsSelf);

	mPartyPlayerInfoLists.Push(newCell);

	UPanelSlot* child = mPartyPlayerInfoScrollBox->AddChild(newCell);
	mPartyPlayerInfoScrollBox->ScrollToEnd();

	Cast<UW_PartyPlayerInfo>(child->Content)->SetPlayerInfo(inRemoteID, inLeaderRemoteID, inLevel, inClass, inPlayerName, inIsSelf);

	this->SetVisibility(ESlateVisibility::Visible);
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

	if (0 == mPartyPlayerInfoLists.Num())
	{
		this->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		mPartyPlayerInfoScrollBox->ClearChildren();
		for (UUserWidget* widget : mPartyPlayerInfoLists)
		{
			mPartyPlayerInfoScrollBox->AddChild(widget);
		}
		mPartyPlayerInfoScrollBox->ScrollToEnd();
	}
}

void UW_PartyPlayerInfoList::RequestPushBuff(const int64 inRemoteID, const int32& inBuffID, const int64& inBuffDuration)
{
	for (UUserWidget* PlayerInfo : mPartyPlayerInfoLists)
	{
		UW_PartyPlayerInfo* PlayerData = Cast<UW_PartyPlayerInfo>(PlayerInfo);
		if(nullptr == PlayerData)
		{
			return;
		}

		if (inRemoteID == PlayerData->GetRemoteID())
		{
			PlayerData->PushBuff(inBuffID, inBuffDuration);
		}
	}
}

void UW_PartyPlayerInfoList::RequestReleaseBuff(const int64 inRemoteID, const int32& inBuffID)
{
	for (UUserWidget* PlayerInfo : mPartyPlayerInfoLists)
	{
		UW_PartyPlayerInfo* PlayerData = Cast<UW_PartyPlayerInfo>(PlayerInfo);
		if (nullptr == PlayerData)
		{
			return;
		}

		if (inRemoteID == PlayerData->GetRemoteID())
		{
			PlayerData->ReleaseBuff(inBuffID);
		}
	}
}

void UW_PartyPlayerInfoList::UpdateLocation()
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

void UW_PartyPlayerInfoList::Pressed_Drag()
{
	FVector2D currentMousePoint = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2D currentViewportPoint = RenderTransform.Translation;
	mPressedMousePoint = currentMousePoint - currentViewportPoint;
	UpdateLocation();
}

void UW_PartyPlayerInfoList::Released_Drag()
{
	if (true == GetWorld()->GetTimerManager().IsTimerActive(mUpdateLocationTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(mUpdateLocationTimerHandle);
	}
}
