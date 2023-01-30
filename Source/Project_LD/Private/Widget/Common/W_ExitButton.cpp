// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_ExitButton.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Network/NetworkGameMode.h>

void UW_ExitButton::NativeConstruct()
{
	Super::NativeConstruct();

	mExitButton = Cast<UButton>(GetWidgetFromName(TEXT("mExitButton")));

	mExitText = Cast<UTextBlock>(GetWidgetFromName(TEXT("mExitText")));

	if (mExitButton != nullptr)
	{
		mExitButton->OnClicked.AddDynamic(this, &UW_ExitButton::Click_Exit);
	}

	if (mExitText != nullptr)
	{

	}
}

void UW_ExitButton::SetExitText(const FString& inText)
{
	FText text = FText::FromString(inText);
	mExitText->SetText(text);
}

void UW_ExitButton::Click_Exit()
{
	AGameModeBase* gameMode = GetWorld()->GetAuthGameMode();
	ANetworkGameMode* networkGameMode = Cast<ANetworkGameMode>(gameMode);

	bool exitResult = networkGameMode->RequestExitGame();
	if (false == exitResult)
	{
		return;
	}
}
