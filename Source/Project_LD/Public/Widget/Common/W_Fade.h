// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Fade.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_Fade : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION(BlueprintImplementableEvent)
		void FadeClear();

	UFUNCTION(BlueprintImplementableEvent)
		void FadeIn();

	UFUNCTION(BlueprintImplementableEvent)
		void FadeOut();
};
