// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_EnterDungeon.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

#include <NetworkController.h>
#include <FGamePacketHandler.h>
#include <NetworkUtils.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include <Handler/ClientHUD.h>

void UW_EnterDungeon::NativeConstruct()
{
	Super::NativeConstruct();

	mEnter = Cast<UButton>(GetWidgetFromName(TEXT("mEnter")));
	mCancle = Cast<UButton>(GetWidgetFromName(TEXT("mCancle")));

	mTitle = Cast<UTextBlock>(GetWidgetFromName(TEXT("mTitle")));
	mMessage = Cast<UTextBlock>(GetWidgetFromName(TEXT("mMessage")));

	if (mEnter != nullptr)
	{
		mEnter->OnClicked.AddDynamic(this, &UW_EnterDungeon::Click_EnterButton);
	}

	if (mCancle != nullptr)
	{
		mCancle->OnClicked.AddDynamic(this, &UW_EnterDungeon::Click_CancleButton);
	}
}

void UW_EnterDungeon::NativeDestruct()
{
	Super::NativeDestruct();

	if (mEnter->OnClicked.IsBound())
	{
		mEnter->OnClicked.Clear();
	}

	if (mCancle->OnClicked.IsBound())
	{
		mCancle->OnClicked.Clear();
	}
}

void UW_EnterDungeon::SetTitle(const FString& inTitle)
{
	if (mTitle != nullptr)
	{
		FText text = FText::FromString(inTitle);
		mTitle->SetText(text);
	}
}

void UW_EnterDungeon::SetMessage(const FString& inMessage)
{
	if (mMessage != nullptr)
	{
		FText text = FText::FromString(inMessage);
		mMessage->SetText(text);
	}
}

void UW_EnterDungeon::SetDungeon(const int32& inDungeonID)
{
	mDungeonID = inDungeonID;
}

void UW_EnterDungeon::Click_EnterButton()
{
	APlayerController* owningController = GetOwningPlayer();
	ANetworkController* networkController = Cast<ANetworkController>(owningController);
	if (nullptr == networkController)
	{
		return;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(networkController->GetHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));

	Protocol::C2S_RequestEnterDungeon enterPacket;
	enterPacket.set_dungeon_type(mDungeonID);

	SendBufferPtr sendBuffer = FGamePacketHandler::MakeSendBuffer(nullptr, enterPacket);
	networkController->Send(sendBuffer);

	clientHUD->CleanWidgetFromName(TEXT("EnterDungeon"));

}

void UW_EnterDungeon::Click_CancleButton()
{
	APlayerController* owningController = GetOwningPlayer();
	ANetworkController* networkController = Cast<ANetworkController>(owningController);
	if (nullptr == networkController)
	{
		return;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(networkController->GetHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	clientHUD->CleanWidgetFromName(TEXT("EnterDungeon"));

}