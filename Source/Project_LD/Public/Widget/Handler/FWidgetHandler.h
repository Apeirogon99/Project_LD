// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Widget/Identity/W_Singin.h>
#include <Widget/Identity/W_Singup.h>

class APlayerController;

/**
 * 
 */
class PROJECT_LD_API FWidgetHandler
{
public:
	static bool HandleWidget(UClass* inWidget, APlayerController* inController)
	{
		UUserWidget* widget = CreateWidget(inController, inWidget);
		if (widget)
		{
			widget->AddToViewport();
			return true;
		}
		return false;
	}
};
