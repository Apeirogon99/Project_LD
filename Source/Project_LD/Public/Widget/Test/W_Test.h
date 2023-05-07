// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Test.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_Test : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
	void InitWidget(const int32 inClientTimeStamp, const int32 inServerTimeStamp);

	UFUNCTION()
		void Click_SendButton();

private:
	UPROPERTY(Meta = (BindWidget))
	UButton* mSendButton;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mServerTimeStampText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mClientTimeStampText;

private:
	FString	mClientTimeStamp;
	FString	mServerTimeStamp;
};
