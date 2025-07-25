// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Main/W_PlayerBar.h"
#include "Components/ProgressBar.h"

void UW_PlayerBar::NativeConstruct()
{
	Super::NativeConstruct();

	HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthBar")));
	ManaBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ManaBar")));
}

void UW_PlayerBar::NativeDestruct()
{
	Super::NativeDestruct();
}
