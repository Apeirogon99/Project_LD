// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_LoadingPlayer.h"

void UW_LoadingPlayer::NativeConstruct()
{
	Super::NativeConstruct();
}

void UW_LoadingPlayer::UpdateLoadingPlayer(FString inMaxNumber, FString inLeastNumber)
{
	mMaxNumber = FText::FromString(inMaxNumber);
	mLeastNumber = FText::FromString(inLeastNumber);
}
