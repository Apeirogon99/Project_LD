// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/MiniMap/W_PointOfInterest.h"
#include <GM_Game.h>
#include <Widget/Handler/ClientHUD.h>
#include <Game/MiniMap/W_MiniMap.h>

void UW_PointOfInterest::GetMinMapWidget(UUserWidget*& InWidget)
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	AGM_Game* gameMode = Cast<AGM_Game>(world->GetAuthGameMode());
	if (nullptr == gameMode)
	{
		return;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	UUserWidget* widget = clientHUD->GetWidgetFromName(TEXT("MiniMap"));
	if (nullptr == widget)
	{
		return;
	}

	InWidget = widget;
}
