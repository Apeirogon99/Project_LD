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

	mCurTimeStampText		= Cast<UTextBlock>(GetWidgetFromName(TEXT("mCurTimeStampText")));
	mServerTimeStampText	= Cast<UTextBlock>(GetWidgetFromName(TEXT("mServerTimeStampText")));
	mDiffTimeStampText		= Cast<UTextBlock>(GetWidgetFromName(TEXT("mDiffTimeStampText")));
	mClientTimeStampText	= Cast<UTextBlock>(GetWidgetFromName(TEXT("mClientTimeStampText")));

	if (mSendButton != nullptr)
	{
		mSendButton->OnClicked.AddDynamic(this, &UW_Test::Click_SendButton);
	}

}

void UW_Test::Update(const int32 inCurClientTimeStamp, const int32 inServerTimeStamp, const int32 inDiffTimeStamp, const int32 inClientTimeStamp)
{
	mCurTimeStamp		= FString::FromInt(inCurClientTimeStamp);
	mServerTimeStamp	= FString::FromInt(inServerTimeStamp);
	mDiffTimeStamp		= FString::FromInt(inDiffTimeStamp);
	mClientTimeStamp	= FString::FromInt(inClientTimeStamp);

	mCurTimeStampText->SetText(FText::FromString(mCurTimeStamp));
	mServerTimeStampText->SetText(FText::FromString(mServerTimeStamp));
	mDiffTimeStampText->SetText(FText::FromString(mDiffTimeStamp));
	mClientTimeStampText->SetText(FText::FromString(mClientTimeStamp));
}

void UW_Test::Click_SendButton()
{
	APlayerController* owningController = GetOwningPlayer();
	ANetworkController* networkController = Cast<ANetworkController>(owningController);
}
