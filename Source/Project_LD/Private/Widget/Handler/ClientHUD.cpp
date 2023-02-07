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
	UUserWidget* widget = GetWidgetFromName(inWidgetName);
	if (nullptr == widget)
	{
		return;
	}

	if (false == widget->IsInViewport())
	{
		widget->AddToViewport();
		//widget->AddToPlayerScreen();
	}	
}

void AClientHUD::CleanWidgetFromName(const FString& inWidgetName)
{
	UUserWidget* widget = GetWidgetFromName(inWidgetName);
	if (nullptr == widget)
	{
		return;
	}

	if (true == widget->IsInViewport())
	{
		widget->RemoveFromViewport();
	}
}

void AClientHUD::CollapsedWidgetFromName(const FString& inWidgetName)
{
	UUserWidget* widget = GetWidgetFromName(inWidgetName);
	if (nullptr == widget)
	{
		return;
	}

	if (true == widget->IsInViewport())
	{
		widget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AClientHUD::SelfHitTestInvisibleWidgetFromName(const FString& inWidgetName)
{
	UUserWidget* widget = GetWidgetFromName(inWidgetName);
	if (nullptr == widget)
	{
		return;
	}

	if (true == widget->IsInViewport())
	{
		widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
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
		if (nullptr != widget)
		{
			if (true == widget->IsInViewport())
			{
				widget->RemoveFromViewport();
			}
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
		if (nullptr != widget)
		{
			if (true == widget->GetIsVisible())
			{
				ESlateVisibility visible =  widget->GetVisibility();
				switch (visible)
				{
				case ESlateVisibility::Collapsed:
				case ESlateVisibility::Hidden:
					break;
				case ESlateVisibility::Visible:
					widget->SetVisibility(ESlateVisibility::Collapsed);
					break;
				case ESlateVisibility::HitTestInvisible:
					widget->SetVisibility(ESlateVisibility::Collapsed);
					break;
				case ESlateVisibility::SelfHitTestInvisible:
					widget->SetVisibility(ESlateVisibility::Collapsed);
					break;
				default:
					break;
				}
			}
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
		if (nullptr != widget)
		{
			if (widget->GetIsVisible())
			{
				ESlateVisibility visible = widget->GetVisibility();
				switch (visible)
				{
				case ESlateVisibility::Visible:
				case ESlateVisibility::HitTestInvisible:
				case ESlateVisibility::SelfHitTestInvisible:
					break;
				case ESlateVisibility::Collapsed:
					widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					break;
				case ESlateVisibility::Hidden:
					widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
					break;
				default:
					break;
				}
			}
		}
	}
}

void AClientHUD::AllCollapsedButOneWidget(const FString& inWidgetName)
{
	AllCollapsedWidget();

	ShowWidgetFromName(inWidgetName);

}

void AClientHUD::AllSelfHitTestInvisibleButOneWidget(const FString& inWidgetName)
{
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