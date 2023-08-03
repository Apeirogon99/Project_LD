// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_BottomUI.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_BottomUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UWidget* mPlayerBar;

protected:
	virtual void NativeConstruct() override;
};
