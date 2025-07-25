// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Enemy/W_HealthBar.h"
#include "Components/ProgressBar.h"

void UW_HealthBar::NativeConstruct()
{
	Super::NativeConstruct();

	HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthBar")));
}

void UW_HealthBar::NativeDestruct()
{
	Super::NativeDestruct();
}
