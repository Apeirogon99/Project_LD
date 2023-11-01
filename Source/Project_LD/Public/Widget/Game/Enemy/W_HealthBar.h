// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_HealthBar.generated.h"

/**
 * 
 */
class UProgressBar;

UCLASS()
class PROJECT_LD_API UW_HealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthBar;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};