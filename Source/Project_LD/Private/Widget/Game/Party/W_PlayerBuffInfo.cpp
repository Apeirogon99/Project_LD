// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Party/W_PlayerBuffInfo.h"
#include <Components/Image.h>

void UW_PlayerBuffInfo::NativeConstruct()
{
	Super::NativeConstruct();

	mBuffImage = Cast<UImage>(GetWidgetFromName(TEXT("mBuffImage")));
}

void UW_PlayerBuffInfo::NativeDestruct()
{
	Super::NativeDestruct();
}
