// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Handler/ClientHUD.h"
#include <UMG/Public/Blueprint/WidgetLayoutLibrary.h>
#include <Network/NetworkGameMode.h>
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY(CLIENT_HUD);

AClientHUD::AClientHUD()
{
	mIsInit = false;
}

bool AClientHUD::GetWidgetFromName(const FString& inWidgetName, UUserWidget* outWidget, int32& outNumber)
{
	if (false == mIsInit)
	{
		return false;
	}

	const int32 findPos = mWidgetNames.Find(inWidgetName);
	if (findPos == INDEX_NONE)
	{
		HUD_LOG(TEXT("Can't find widget : %s"), *inWidgetName);
		return false;
	}

	UUserWidget* findWidget = mWidgets[findPos];
	if (nullptr == findWidget)
	{
		HUD_LOG(TEXT("Invalid widget : %s "), *inWidgetName);
		return false;
	}

	outWidget = findWidget;
	outNumber = findPos;

	return true;
}

void AClientHUD::ShowWidgetFromName(const FString& inWidgetName)
{
	UUserWidget* widget = NewObject<UUserWidget>();
	int32 number = INDEX_NONE;
	bool ret = GetWidgetFromName(inWidgetName, widget, number);
	if (ret == false)
	{
		return;
	}

	if (widget == nullptr || number == INDEX_NONE)
	{
		return;
	}

	if (mUsedWidgets[number] == false)
	{
		SelfHitTestInvisibleWidget(widget);
		mUsedWidgets[number] = true;
	}

}

void AClientHUD::CleanWidgetFromName(const FString& inWidgetName)
{
	UUserWidget* widget = NewObject<UUserWidget>();
	int32 number = INDEX_NONE;
	bool ret = GetWidgetFromName(inWidgetName, widget, number);
	if (ret == false)
	{
		return;
	}

	if (widget == nullptr || number == INDEX_NONE)
	{
		return;
	}

	if (mUsedWidgets[number] == true)
	{
		CollapsedWidget(widget);
		mUsedWidgets[number] = false;
	}

}

void AClientHUD::CollapsedWidget(UUserWidget* inWidget)
{
	if (nullptr == inWidget)
	{
		return;
	}

	if (false == inWidget->IsInViewport())
	{
		inWidget->AddToPlayerScreen();
	}

	ESlateVisibility visible = inWidget->GetVisibility();
	switch (visible)
	{
	case ESlateVisibility::Collapsed:
	case ESlateVisibility::Hidden:
		break;
	case ESlateVisibility::Visible:
		inWidget->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case ESlateVisibility::HitTestInvisible:
		inWidget->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case ESlateVisibility::SelfHitTestInvisible:
		inWidget->SetVisibility(ESlateVisibility::Collapsed);
		break;
	default:
		break;
	}
	
}

void AClientHUD::SelfHitTestInvisibleWidget(UUserWidget* inWidget)
{
	if (nullptr == inWidget)
	{
		return;
	}

	if (false == inWidget->IsInViewport())
	{
		inWidget->AddToPlayerScreen();
	}

	ESlateVisibility visible = inWidget->GetVisibility();
	switch (visible)
	{
	case ESlateVisibility::Visible:
	case ESlateVisibility::HitTestInvisible:
	case ESlateVisibility::SelfHitTestInvisible:
		break;
	case ESlateVisibility::Collapsed:
		inWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	case ESlateVisibility::Hidden:
		inWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		break;
	default:
		break;
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

	//Base
	for (TSubclassOf<UUserWidget> widgetClass : mCommonUIWidgets)
	{
		UUserWidget* newWidget = CreateWidget<UUserWidget>(GetWorld(), widgetClass);
		newWidget->AddToViewport();
		newWidget->SetVisibility(ESlateVisibility::Collapsed);
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
		newWidget->AddToViewport();
		newWidget->SetVisibility(ESlateVisibility::Collapsed);
		mWidgets.Add(newWidget);

		FString newWidgetName = newWidget->GetClass()->GetName();
		newWidgetName.RemoveAt(0, 3);
		newWidgetName.RemoveAt(newWidgetName.Len() - 2 , newWidgetName.Len());
		mWidgetNames.Add(newWidgetName);
	}

	//Used UI
	mUsedWidgets.Init(false, mWidgets.Num());
	
	mIsInit = true;
	networkGameMode->ProcessClientHUD(true);
	HUD_LOG(TEXT("ClientHUD Init : %d"), mWidgets.Num());
}

void AClientHUD::DrawHUD()
{
	Super::DrawHUD();

}