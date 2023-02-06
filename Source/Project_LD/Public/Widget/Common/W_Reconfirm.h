// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Reconfirm.generated.h"

DECLARE_DELEGATE(FCancleButtonDelegate);
DECLARE_DELEGATE(FConfirmButtonDelegate);

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_Reconfirm : public UUserWidget
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
		UTextBlock* mReconfirmText;

	UPROPERTY(Meta = (BindWidget))
		UButton* mConfirmButton;

	UPROPERTY(Meta = (BindWidget))
		UButton* mCancleButton;

public:
	UFUNCTION(BlueprintCallable)
		void SetTitleText(const FString& inTitle);

	UFUNCTION(BlueprintCallable)
		void SetReconfirmText(const FString& inReconfirm);

public:
	UFUNCTION()
		void Click_Confirm();

	UFUNCTION()
		void Click_Cancle();

public:
	FCancleButtonDelegate mCancleDelegate;
	FConfirmButtonDelegate mReConfirmDelegate;
};
