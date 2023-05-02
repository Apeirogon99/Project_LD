// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Test/W_Test.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

#include <Network/NetworkController.h>
#include <Framework/Identity/IdentityPlayerController.h>
#include <Network/NetworkUtils.h>

#include <Protobuf/Handler/FIdentityPacketHandler.h>

void UW_Test::NativeConstruct()
{
	Super::NativeConstruct();

	mLeftButton		= Cast<UButton>(GetWidgetFromName(TEXT("mLeftButton")));
	mRightButton	= Cast<UButton>(GetWidgetFromName(TEXT("mRightButton")));

	mIValueText		= Cast<UTextBlock>(GetWidgetFromName(TEXT("mIValueText")));
	mSValueText		= Cast<UTextBlock>(GetWidgetFromName(TEXT("mSValueText")));
	mTimeStampText	= Cast<UTextBlock>(GetWidgetFromName(TEXT("mTimeStampText")));

	if (mLeftButton != nullptr)
	{
		mLeftButton->OnClicked.AddDynamic(this, &UW_Test::Click_LeftButton);
	}

	if (mRightButton != nullptr)
	{
		mRightButton->OnClicked.AddDynamic(this, &UW_Test::Click_RightButton);
	}
}

void UW_Test::InitWidget(const int32 inIValue, const FString& inSValue, const int32 inTimeStamp)
{
	mIValue = FString::FromInt(inIValue);
	mSValue = inSValue;
	mTimeStamp = FString::FromInt(inTimeStamp);

	mIValueText->SetText(FText::FromString(mIValue));
	mSValueText->SetText(FText::FromString(mSValue));
	mTimeStampText->SetText(FText::FromString(mTimeStamp));
}

void UW_Test::Click_LeftButton()
{
	const int32		iValue = FCString::Atoi(*mIValue) + 1;
	const FString	sValue = FString(TEXT("LEFT"));
	const int32		timestamp = FCString::Atoi(*mTimeStamp) + 1000;

	TestProcess(iValue, sValue, timestamp);
}

void UW_Test::Click_RightButton()
{
	const int32		iValue = FCString::Atoi(*mIValue) + 5;
	const FString	sValue = FString(TEXT("RIGHT"));
	const int32		timestamp = FCString::Atoi(*mTimeStamp) + 5000;

	TestProcess(iValue, sValue, timestamp);
}

void UW_Test::TestProcess(const int32 inIValue, const FString& inSValue, const int32 inTimeStamp)
{
	APlayerController* owningController = GetOwningPlayer();
	ANetworkController* networkController = Cast<ANetworkController>(owningController);

	const int64 clientTimeStamp = networkController->GetNetworkTimeStamp();

	Protocol::C2S_GetRoundTripTime packet;

	SendBufferPtr sendBuffer = FIdentityPacketHandler::MakeSendBuffer(networkController, packet);
	networkController->Send(sendBuffer);
}
