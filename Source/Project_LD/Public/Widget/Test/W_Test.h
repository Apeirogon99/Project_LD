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
	void Update(const int32 inCurClientTimeStamp, const int32 inServerTimeStamp, const int32 inDiffTimeStamp, const int32 inClientTimeStamp);

	UFUNCTION()
		void Click_SendButton();

private:
	UPROPERTY(Meta = (BindWidget))
	UButton* mSendButton;


	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mCurTimeStampText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mServerTimeStampText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mDiffTimeStampText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mClientTimeStampText;

private:
	FString	mCurTimeStamp;
	FString	mServerTimeStamp;
	FString	mDiffTimeStamp;
	FString	mClientTimeStamp;
};
