// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Identity/W_SelectServerButton.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Struct/Identity/ServerData.h>

#include <Network/NetworkController.h>

#include <Protobuf/Handler/FIdentityPacketHandler.h>

#include <Widget/Handler/ClientHUD.h>
#include <Widget/WidgetUtils.h>

void UW_SelectServerButton::NativeConstruct()
{
	Super::NativeConstruct();

	mServerName				= Cast<UTextBlock>(GetWidgetFromName(TEXT("mServerName")));
	mServerState			= Cast<UTextBlock>(GetWidgetFromName(TEXT("mServerState")));
	mServerCharacterCount	= Cast<UTextBlock>(GetWidgetFromName(TEXT("mServerCharacterCount")));
	mSelectServerButton		= Cast<UButton>(GetWidgetFromName(TEXT("mSelectServerButton")));

	if (mSelectServerButton != nullptr)
	{
		mSelectServerButton->OnClicked.AddUniqueDynamic(this, &UW_SelectServerButton::Click_SelectServerButton);
	}
}

void UW_SelectServerButton::NativeOnListItemObjectSet(UObject* ListItemObject)
{

	UW_SelectServerButton* serverData = Cast<UW_SelectServerButton>(ListItemObject);
	if (nullptr == serverData)
	{
		return;
	}

	this->mServerID			= serverData->mServerID;
	this->mName				= serverData->mName;
	this->mState			= serverData->mState;
	this->mCharacterCount	= serverData->mCharacterCount;
	this->mIsBackGround		= serverData->mIsBackGround;

	mServerName->SetText(FText::FromString(mName));

	if (0.5f < mState)
	{
		mServerState->SetText(FText::FromString(TEXT("원활")));
	}
	else
	{
		mServerState->SetText(FText::FromString(TEXT("혼잡")));
	}

	mServerCharacterCount->SetText(FText::FromString(FString::Printf(TEXT("%d"), mCharacterCount)));
}

void UW_SelectServerButton::Click_SelectServerButton()
{
	APlayerController* owningController		= GetOwningPlayer();
	ANetworkController* networkController	= Cast<ANetworkController>(owningController);
	if (nullptr == networkController)
	{
		return;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(networkController->GetHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	FString recornfirmText = FString::Printf(TEXT("%s에 입장하시겠습니까?"), *mName);

	FConfirmButtonDelegate confirmDelegate;
	confirmDelegate.BindLambda([=]()
		{

			clientHUD->CleanWidgetFromName(TEXT("SelectServer"));
			clientHUD->CleanWidgetFromName(TEXT("Reconfirm"));
			clientHUD->ShowWidgetFromName(TEXT("LoadingServer"));

			Protocol::C2S_SelectServer selectPacket;
			selectPacket.set_server_id(mServerID);

			SendBufferPtr sendBuffer = FIdentityPacketHandler::MakeSendBuffer(networkController, selectPacket);
			networkController->Send(sendBuffer);
		});

	FCancleButtonDelegate cancleDelegate;
	cancleDelegate.BindLambda([=]()
		{
			clientHUD->CleanWidgetFromName(TEXT("Reconfirm"));
		});

	bool error = UWidgetUtils::SetReconfirm(clientHUD, TEXT("서버 선택"), recornfirmText, TEXT("선택"), TEXT("취소"),confirmDelegate, cancleDelegate);
	if (error == false)
	{
		return;
	}
}

void UW_SelectServerButton::Init(const int32 inServerID, const FString& inName, const float inState, const int32 inCharacterCount, const bool inBackGround)
{
	mServerID		= inServerID;
	mName			= inName;
	mState			= inState;
	mCharacterCount = inCharacterCount;
	mIsBackGround	= inBackGround;
}

