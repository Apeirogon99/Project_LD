// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Notification.generated.h"

DECLARE_DELEGATE(FNotificationDelegate);

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_Notification : public UUserWidget
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
		UTextBlock* mTitleText;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* mNotificationText;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* mConfirmButtonText;

	UPROPERTY(Meta = (BindWidget))
		UButton* mConfirmButton;

public:
	UFUNCTION(BlueprintCallable)
		void SetNotification(const FString& inNotification);

	UFUNCTION(BlueprintCallable)
		void SetTitle(const FString& inTitle);

	UFUNCTION(BlueprintCallable)
		void SetButtonText(const FString& inButtonText);

public:
	UFUNCTION()
		void Click_Confirm();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
		FLinearColor mButtonActiveColor;

	FNotificationDelegate mNotificationDelegate;
};
