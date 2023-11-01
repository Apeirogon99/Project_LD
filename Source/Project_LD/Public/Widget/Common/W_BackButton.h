// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_BackButton.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_BackButton : public UUserWidget
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
		UButton* mBackButton;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* mBackText;

public:
	UFUNCTION(BlueprintCallable)
		void SetBackText(const FString& inText);

	UFUNCTION(BlueprintCallable)
		void SetBackButton(const FString& inLevel);

public:
	UFUNCTION()
		void Click_Back();

public:
	UPROPERTY()
		FString mLevel;
};
