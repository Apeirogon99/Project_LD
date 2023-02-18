// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Button.generated.h"

DECLARE_DELEGATE(FButtonClickDelegate);

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_Button : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UPROPERTY(Meta = (BindWidget))
		UButton* mButton;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* mButtonText;

public:
	UFUNCTION(BlueprintCallable)
		void SetText(const FString& inText);

public:
	UFUNCTION()
		void Click_Button();

public:
	FButtonClickDelegate mButtonDelegate;
};
