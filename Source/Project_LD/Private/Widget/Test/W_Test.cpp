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

	mSendButton = Cast<UButton>(GetWidgetFromName(TEXT("mSendButton")));

	mServerTimeStampText = Cast<UTextBlock>(GetWidgetFromName(TEXT("mServerTimeStampText")));
	mClientTimeStampText = Cast<UTextBlock>(GetWidgetFromName(TEXT("mClientTimeStampText")));

	if (mSendButton != nullptr)
	{
		mSendButton->OnClicked.AddDynamic(this, &UW_Test::Click_SendButton);
	}

}

void UW_Test::InitWidget(const int32 inClientTimeStamp, const int32 inServerTimeStamp)
{
	mClientTimeStamp = FString::FromInt(inClientTimeStamp);
	mServerTimeStamp = FString::FromInt(inServerTimeStamp);

	mClientTimeStampText->SetText(FText::FromString(mClientTimeStamp));
	mServerTimeStampText->SetText(FText::FromString(mServerTimeStamp));
}

void UW_Test::Click_SendButton()
{
	APlayerController* owningController = GetOwningPlayer();
	ANetworkController* networkController = Cast<ANetworkController>(owningController);

	const int64 clientTimeStamp = networkController->GetNetworkTimeStamp();

	Protocol::C2S_GetRoundTripTime packet;

	SendBufferPtr sendBuffer = FIdentityPacketHandler::MakeSendBuffer(networkController, packet);
	networkController->Send(sendBuffer);
}
