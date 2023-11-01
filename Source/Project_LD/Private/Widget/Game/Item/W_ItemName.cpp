// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Item/W_ItemName.h"
#include "Components/TextBlock.h"

void UW_ItemName::NativeConstruct()
{
	Super::NativeConstruct();

	mName = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));
}

void UW_ItemName::NativeDestruct()
{
	Super::NativeDestruct();
}

void UW_ItemName::SetNameText(const FString& inName)
{
	if (mName)
	{
		FText Name = FText::FromString(inName);
		mName->SetText(Name);
	}
}
