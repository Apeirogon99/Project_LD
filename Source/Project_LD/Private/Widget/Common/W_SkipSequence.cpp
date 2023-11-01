// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_SkipSequence.h"
#include <Components/Button.h>

#include <Framework/Gameinstance/LDGameInstance.h>
#include <NetworkController.h>
#include <FGamePacketHandler.h>
#include <NetworkUtils.h>

void UW_SkipSequence::NativeConstruct()
{
	Super::NativeConstruct();

	mSkipButton = Cast<UButton>(GetWidgetFromName(TEXT("mSkipButton")));

	if (mSkipButton != nullptr)
	{
		mSkipButton->OnClicked.AddDynamic(this, &UW_SkipSequence::Click_SkipButton);
	}
}

void UW_SkipSequence::NativeDestruct()
{
	Super::NativeDestruct();

	if (mSkipButton->OnClicked.IsBound())
	{
		mSkipButton->OnClicked.Clear();
	}
}

void UW_SkipSequence::UpdateSkipSequence(FString inMaxNumber, FString inLeastNumber)
{
	mMaxNumber = FText::FromString(inMaxNumber);
	mLeastNumber = FText::FromString(inLeastNumber);
}

void UW_SkipSequence::Click_SkipButton()
{
	UWorld* world = this->GetWorld();
	if (nullptr == world)
	{
		return;
	}

	APlayerController* owningController = GetOwningPlayer();
	ANetworkController* networkController = Cast<ANetworkController>(owningController);
	if (nullptr == networkController)
	{
		return;
	}

	ULDGameInstance* instance = Cast<ULDGameInstance>(world->GetGameInstance());
	if (nullptr == instance)
	{
		return;
	}

	Protocol::C2S_SkipSequence skipPacket;
	skipPacket.set_dungeon_id(instance->GetDungeonID());

	SendBufferPtr sendBuffer = FGamePacketHandler::MakeSendBuffer(nullptr, skipPacket);
	networkController->Send(sendBuffer);
}
