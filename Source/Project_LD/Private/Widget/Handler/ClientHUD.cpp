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

UUserWidget* AClientHUD::GetWidgetFromName(const FString& inWidgetName)
{
	if (false == mIsInit)
	{
		return nullptr;
	}

	const int32 findPos = mWidgetNames.Find(inWidgetName);
	if (findPos == INDEX_NONE)
	{
		HUD_LOG(TEXT("Can't find widget : %s"), *inWidgetName);
		return nullptr;
	}

	UUserWidget* findWidget = mWidgets[findPos];
	if (nullptr == findWidget)
	{
		HUD_LOG(TEXT("Invalid widget : %s "), *inWidgetName);
		return nullptr;
	}

	return findWidget;
}

void AClientHUD::ShowWidgetFromName(const FString& inWidgetName)
{
	if (false == mIsInit)
	{
		return;
	}

	const int32 findPos = mWidgetNames.Find(inWidgetName);
	if (findPos == INDEX_NONE)
	{
		HUD_LOG(TEXT("Can't find widget : %s"), *inWidgetName);
		return;
	}

	UUserWidget* findWidget = mWidgets[findPos];
	if (nullptr == findWidget)
	{
		HUD_LOG(TEXT("Invalid widget : %s "), *inWidgetName);
		return;
	}

	int32 oldZorder = mZorder.AddExchange(1);
	if (false == findWidget->IsInViewport())
	{
		findWidget->AddToPlayerScreen();
	}	
}

void AClientHUD::CleanWidgetFromName(const FString& inWidgetName)
{
	if (false == mIsInit)
	{
		return;
	}

	const int32 findPos = mWidgetNames.Find(inWidgetName);
	if (findPos == INDEX_NONE)
	{
		HUD_LOG(TEXT("Can't find widget : %s"), *inWidgetName);
		return;
	}

	UUserWidget* findWidget = mWidgets[findPos];
	if (nullptr == findWidget)
	{
		HUD_LOG(TEXT("Invalid widget : %s "), *inWidgetName);
		return;
	}

	if (true == findWidget->IsInViewport())
	{
		findWidget->RemoveFromViewport();
	}
}

void AClientHUD::AllCleanWidget()
{
	if (false == mIsInit)
	{
		return;
	}

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
	if (false == mIsInit)
	{
		return;
	}

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
	if (false == mIsInit)
	{
		return;
	}

	for (UUserWidget* widget : mWidgets)
	{
		if (widget->IsInViewport())
		{
			widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
}

void AClientHUD::AllCollapsedButOneWidget(const FString& inWidgetName)
{
	if (false == mIsInit)
	{
		return;
	}

	AllCollapsedWidget();

	ShowWidgetFromName(inWidgetName);

}

void AClientHUD::AllSelfHitTestInvisibleButOneWidget(const FString& inWidgetName)
{
	if (false == mIsInit)
	{
		return;
	}

	CleanWidgetFromName(inWidgetName);

	AllSelfHitTestInvisibleWidget();

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

	//Base
	for (TSubclassOf<UUserWidget> widgetClass : mCommonUIWidgets)
	{
		UUserWidget* newWidget = CreateWidget<UUserWidget>(GetWorld(), widgetClass);
		mWidgets.Add(newWidget);

		FString newWidgetName = newWidget->GetClass()->GetName();
		newWidgetName.RemoveAt(0, 3);
		newWidgetName.RemoveAt(newWidgetName.Len() - 2, newWidgetName.Len());
		mWidgetNames.Add(newWidgetName);
	}

	//Driven
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