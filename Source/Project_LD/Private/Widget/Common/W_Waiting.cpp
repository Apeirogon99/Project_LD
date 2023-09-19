// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Common/W_Waiting.h"
#include <Components/TextBlock.h>

#include <NetworkController.h>
#include <FGamePacketHandler.h>
#include <NetworkUtils.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include <Handler/ClientHUD.h>

void UW_Waiting::NativeConstruct()
{
	Super::NativeConstruct();

	mTitle = Cast<UTextBlock>(GetWidgetFromName(TEXT("mTitle")));
	mTime = Cast<UTextBlock>(GetWidgetFromName(TEXT("mTime")));

	mTimeCount = 0;
	mDeltaCount = 0.0f;
}

//void UW_Waiting::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
//{
//	Super::NativeTick(MyGeometry, InDeltaTime);
//
//	if (mTimeCount != 0)
//	{
//		mDeltaCount += InDeltaTime;
//		if (mDeltaCount >= 1.0f)
//		{
//			SetTime(mTimeCount - 1);
//			mDeltaCount = 0.0f;
//		}
//	}
//
//}

void UW_Waiting::SetTitle(const FString& inTitle)
{
	if (mTitle != nullptr)
	{
		FText text = FText::FromString(inTitle);
		mTitle->SetText(text);
	}
}

void UW_Waiting::SetTime(const int32& inTime)
{
	if (mTime != nullptr)
	{
		mTimeCount = inTime;
		FString time = FString::FromInt(mTimeCount);
		time.Append(TEXT("초"));

		FText text = FText::FromString(time);
		mTime->SetText(text);
	}
}
