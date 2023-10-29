// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Friend/W_FriendMain.h"
#include <Widget/Game/Friend/W_FriendCell.h>
#include <Widget/Game/Friend/W_FriendList.h>
#include <Widget/Game/Friend/W_FriendRequestList.h>
#include <Widget/Game/Friend/W_FriendBlockList.h>

#include <Widget/WidgetUtils.h>
#include <Protobuf/Handler/PacketUtils.h>
#include <Network/NetworkUtils.h>

#include <Game/GM_Game.h>
#include <Game/PC_Game.h>

#include <Blueprint/WidgetTree.h>
#include <Components/Button.h>
#include <Blueprint/WidgetLayoutLibrary.h>

void UW_FriendMain::NativeConstruct()
{
	Super::NativeConstruct();

	mFriendTab	= Cast<UButton>(GetWidgetFromName(TEXT("mFriendTab")));
	mRequestTab = Cast<UButton>(GetWidgetFromName(TEXT("mRequestTab")));
	mBlockTab	= Cast<UButton>(GetWidgetFromName(TEXT("mBlockTab")));

	mDragButton = Cast<UButton>(GetWidgetFromName(TEXT("mDragButton")));

	if (mFriendTab != nullptr)
	{
		mFriendTab->OnClicked.AddUniqueDynamic(this, &UW_FriendMain::Click_FriendTab);
	}

	if (mRequestTab != nullptr)
	{
		mRequestTab->OnClicked.AddUniqueDynamic(this, &UW_FriendMain::Click_RequestTab);
	}

	if (mBlockTab != nullptr)
	{
		mBlockTab->OnClicked.AddUniqueDynamic(this, &UW_FriendMain::Click_BlockTab);
	}

	if (mDragButton != nullptr)
	{
		mDragButton->OnPressed.AddUniqueDynamic(this, &UW_FriendMain::Pressed_Drag);
		mDragButton->OnReleased.AddUniqueDynamic(this, &UW_FriendMain::Released_Drag);
	}

	mFriendList = this->WidgetTree->FindWidget(FName(TEXT("BW_FriendList")));
	if (mFriendList != nullptr)
	{

	}

	mFriendRequesrList = this->WidgetTree->FindWidget(FName(TEXT("BW_FriendRequest")));
	if (mFriendRequesrList != nullptr)
	{

	}

	mFriendBlockList = this->WidgetTree->FindWidget(FName(TEXT("BW_FriendBlockList")));
	if (mFriendBlockList != nullptr)
	{

	}

	mFriendListType = 0;
}

void UW_FriendMain::NativeDestruct()
{
	Super::NativeDestruct();
}

void UW_FriendMain::Click_FriendTab()
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
	this->mFriendListType = 0;

	const int64 serverTimeStamp = playerController->GetServerTimeStamp();
	const int32 listType = this->mFriendListType;

	Protocol::C2S_LoadFriendList loadFriendPacket;
	loadFriendPacket.set_list_type(listType);
	loadFriendPacket.set_timestamp(serverTimeStamp);
	playerController->Send(FGamePacketHandler::MakeSendBuffer(playerController, loadFriendPacket));
}

void UW_FriendMain::Click_RequestTab()
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
	this->mFriendListType = 1;

	const int64 serverTimeStamp = playerController->GetServerTimeStamp();
	const int32 listType = this->mFriendListType;

	Protocol::C2S_LoadFriendList loadFriendPacket;
	loadFriendPacket.set_list_type(listType);
	loadFriendPacket.set_timestamp(serverTimeStamp);
	playerController->Send(FGamePacketHandler::MakeSendBuffer(playerController, loadFriendPacket));
}

void UW_FriendMain::Click_BlockTab()
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
	this->mFriendListType = 2;

	const int64 serverTimeStamp = playerController->GetServerTimeStamp();
	const int32 listType = this->mFriendListType;

	Protocol::C2S_LoadFriendList loadFriendPacket;
	loadFriendPacket.set_list_type(listType);
	loadFriendPacket.set_timestamp(serverTimeStamp);
	playerController->Send(FGamePacketHandler::MakeSendBuffer(playerController, loadFriendPacket));
}

void UW_FriendMain::OnFriendTab_Implementation()
{
}

void UW_FriendMain::OnRequestTab_Implementation()
{
}

void UW_FriendMain::OnBlockTab_Implementation()
{
}

void UW_FriendMain::LoadFriendListType(const google::protobuf::RepeatedPtrField<Protocol::SFriend>& inFriends, const int32& inListType)
{
	if (inListType == 0)
	{
		UW_FriendList* list = Cast<UW_FriendList>(mFriendList);
		if (nullptr == list)
		{
			return;
		}
		list->ClearFriendList();

		const int32 maxSize = inFriends.size();
		for (int32 index = 0; index < maxSize; ++index)
		{
			const Protocol::SFriend& curFriend = inFriends.Get(index);

			FString name		 = UNetworkUtils::ConvertFString(curFriend.nick_name());
			int32 level			 = curFriend.level();
			int32 characterClass = curFriend.character_class();
			int32 locale		 = curFriend.locale();
			int32 state			 = curFriend.state();

			list->AddFriendList(name, level, characterClass, locale, state);
		}

		OnFriendTab();
	}
	else if (inListType == 1)
	{
		UW_FriendRequestList* list = Cast<UW_FriendRequestList>(mFriendRequesrList);
		if (nullptr == list)
		{
			return;
		}
		list->ClearFriendList();

		const int32 maxSize = inFriends.size();
		for (int32 index = 0; index < maxSize; ++index)
		{
			const Protocol::SFriend& curFriend = inFriends.Get(index);
			FString name = UNetworkUtils::ConvertFString(curFriend.nick_name());
			list->AddFriendList(name);
		}

		OnRequestTab();
	}
	else if (inListType == 2)
	{
		UW_FriendBlockList* list = Cast<UW_FriendBlockList>(mFriendBlockList);
		if (nullptr == list)
		{
			return;
		}
		list->ClearFriendList();

		const int32 maxSize = inFriends.size();
		for (int32 index = 0; index < maxSize; ++index)
		{
			const Protocol::SFriend& curFriend = inFriends.Get(index);
			FString name = UNetworkUtils::ConvertFString(curFriend.nick_name());
			list->AddFriendList(name);
		}

		OnBlockTab();
	}
	else
	{

	}
}

void UW_FriendMain::UpdateLocation()
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

void UW_FriendMain::Pressed_Drag()
{
	FVector2D currentMousePoint = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2D currentViewportPoint = RenderTransform.Translation;
	mPressedMousePoint = currentMousePoint - currentViewportPoint;
	UpdateLocation();
}

void UW_FriendMain::Released_Drag()
{
	if (true == GetWorld()->GetTimerManager().IsTimerActive(mUpdateLocationTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(mUpdateLocationTimerHandle);
	}
}

const int32& UW_FriendMain::GetFriendListType()
{
	return mFriendListType;
}
