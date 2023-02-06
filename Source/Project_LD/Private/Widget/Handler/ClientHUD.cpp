// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Handler/ClientHUD.h"
#include <UMG/Public/Blueprint/WidgetLayoutLibrary.h>
#include <Network/NetworkGameMode.h>
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY(CLIENT_HUD);

AClientHUD::AClientHUD()
{
	mIsInit = false;
	mZorder.Store(0);
}

UUserWidget* AClientHUD::GetWidgetFromName(const FString& widgetName)
{
	if (false == mIsInit)
	{
		return nullptr;
	}

	const int32 findPos = mWidgetNames.Find(widgetName);
	if (findPos == INDEX_NONE)
	{
		HUD_LOG(TEXT("Can't find widget : %s"), *widgetName);
		return nullptr;
	}

	UUserWidget* findWidget = mWidgets[findPos];
	if (nullptr == findWidget)
	{
		HUD_LOG(TEXT("Invalid widget : %s "), *widgetName);
		return nullptr;
	}

	return findWidget;
}

void AClientHUD::ShowWidgetFromName(const FString& widgetName)
{
	if (false == mIsInit)
	{
		return;
	}

	const int32 findPos = mWidgetNames.Find(widgetName);
	if (findPos == INDEX_NONE)
	{
		HUD_LOG(TEXT("Can't find widget : %s"), *widgetName);
		return;
	}

	UUserWidget* findWidget = mWidgets[findPos];
	if (nullptr == findWidget)
	{
		HUD_LOG(TEXT("Invalid widget : %s "), *widgetName);
		return;
	}

	int32 oldZorder = mZorder.AddExchange(1);
	if (false == findWidget->IsInViewport())
	{
		findWidget->AddToPlayerScreen();
	}	
}

void AClientHUD::CleanWidgetFromName(const FString& widgetName)
{
	if (false == mIsInit)
	{
		return;
	}

	const int32 findPos = mWidgetNames.Find(widgetName);
	if (findPos == INDEX_NONE)
	{
		HUD_LOG(TEXT("Can't find widget : %s"), *widgetName);
		return;
	}

	UUserWidget* findWidget = mWidgets[findPos];
	if (nullptr == findWidget)
	{
		HUD_LOG(TEXT("Invalid widget : %s "), *widgetName);
		return;
	}

	if (true == findWidget->IsInViewport())
	{
		findWidget->RemoveFromViewport();
	}
}

void AClientHUD::AllCleanWidget()
{
	for (UUserWidget* widget : mWidgets)
	{
		if (widget->IsInViewport())
		{
			widget->RemoveFromViewport();
		}
	}
}

void AClientHUD::AllCollapsedWidget()
{
	for (UUserWidget* widget : mWidgets)
	{
		if (widget->IsInViewport())
		{
			widget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void AClientHUD::AllSelfHitTestInvisibleWidget()
{
	for (UUserWidget* widget : mWidgets)
	{
		if (widget->IsInViewport())
		{
			widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
}

bool AClientHUD::IsInit()
{
	return mIsInit;
}

void AClientHUD::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* gameMode = GetWorld()->GetAuthGameMode();
	ANetworkGameMode* networkGameMode = Cast<ANetworkGameMode>(gameMode);

	const int32 maxWidgetNum = mAllUIWidgets.Num();
	if (maxWidgetNum < 0)
	{
		networkGameMode->ProcessClientHUD(false);
		return;
	}

	for (TSubclassOf<UUserWidget> widgetClass : mAllUIWidgets)
	{
		UUserWidget* newWidget = CreateWidget<UUserWidget>(GetWorld(), widgetClass);
		mWidgets.Add(newWidget);

		FString newWidgetName = newWidget->GetClass()->GetName();
		newWidgetName.RemoveAt(0, 3);
		newWidgetName.RemoveAt(newWidgetName.Len() - 2 , newWidgetName.Len());
		mWidgetNames.Add(newWidgetName);
	}
	
	mIsInit = true;
	networkGameMode->ProcessClientHUD(true);
	HUD_LOG(TEXT("ClientHUD Init : %d"), mWidgets.Num());
}

void AClientHUD::DrawHUD()
{
	Super::DrawHUD();

}