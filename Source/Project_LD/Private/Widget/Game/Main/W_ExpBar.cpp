// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Main/W_ExpBar.h"
#include "Components/ProgressBar.h"

void UW_ExpBar::NativeConstruct()
{
	Super::NativeConstruct();

	ExpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ExpBar")));
}
