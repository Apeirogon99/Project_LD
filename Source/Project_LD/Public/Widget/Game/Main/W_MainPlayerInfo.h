// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_MainPlayerInfo.generated.h"

/**
 * 
 */
class UTextBlock;

UCLASS()
class PROJECT_LD_API UW_MainPlayerInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init();

public:
	UFUNCTION()
	void UpdateExpBar();

public:
	UPROPERTY()
	UWidget* mExpBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_Name;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
