// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_Fade.h"

void UW_Fade::NativeConstruct()
{
	Super::NativeConstruct();

	this->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}