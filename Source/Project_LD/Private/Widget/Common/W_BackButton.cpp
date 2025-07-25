// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_BackButton.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Network/NetworkGameMode.h>

void UW_BackButton::NativeConstruct()
{
	Super::NativeConstruct();

	mBackButton = Cast<UButton>(GetWidgetFromName(TEXT("mBackButton")));

	mBackText = Cast<UTextBlock>(GetWidgetFromName(TEXT("mBackText")));

	if (mBackButton != nullptr)
	{
		mBackButton->OnClicked.AddDynamic(this, &UW_BackButton::Click_Back);
	}

	if (mBackText != nullptr)
	{

	}
}

void UW_BackButton::NativeDestruct()
{
	Super::NativeDestruct();

	if (mBackButton->OnClicked.IsBound())
	{
		mBackButton->OnClicked.Clear();
	}
}

void UW_BackButton::SetBackText(const FString& inText)
{
	FText text = FText::FromString(inText);
	mBackText->SetText(text);
}

void UW_BackButton::SetBackButton(const FString& inLevel)
{
	mLevel = inLevel;
}

void UW_BackButton::Click_Back()
{
	if (true == mLevel.IsEmpty())
	{
		return;
	}

	AGameModeBase* gameMode = GetWorld()->GetAuthGameMode();
	ANetworkGameMode* networkGameMode = Cast<ANetworkGameMode>(gameMode);
	networkGameMode->RequestTravelLevel(mLevel);

}
