// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Main/W_BottomUI.h"
#include "Blueprint/WidgetTree.h"

void UW_BottomUI::NativeConstruct()
{
	mPlayerBar = this->WidgetTree->FindWidget(FName(TEXT("BW_PlayerBar")));
	if (mPlayerBar == nullptr)
	{
		return;
	}
}
