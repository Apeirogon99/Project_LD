// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_ExpBar.generated.h"

/**
 * 
 */
class UProgressBar;

UCLASS()
class PROJECT_LD_API UW_ExpBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ExpBar;

protected:
	virtual void NativeConstruct() override;
};
