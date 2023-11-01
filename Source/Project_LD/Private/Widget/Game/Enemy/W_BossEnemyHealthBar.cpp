// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Enemy/W_BossEnemyHealthBar.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UW_BossEnemyHealthBar::NativeConstruct()
{
	Super::NativeConstruct();

	mBossHealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("mBossHealthBar")));
	mName = Cast<UTextBlock>(GetWidgetFromName(TEXT("mName")));;
}

void UW_BossEnemyHealthBar::NativeDestruct()
{
	Super::NativeDestruct();
}

void UW_BossEnemyHealthBar::Init(AEnemyBase* InEnemy)
{
	mEnemy = InEnemy;
}

void UW_BossEnemyHealthBar::SetNameText(const FString& inName)
{
	if (mName)
	{
		FText Name = FText::FromString(inName);
		mName->SetText(Name);
	}
}

void UW_BossEnemyHealthBar::SetEnemy(AEnemyBase* inEnemy)
{
	mEnemy = inEnemy;
}
