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
	void InitWidget(const int32 inIValue, const FString& inSValue, const int32 inTimeStamp);

	UFUNCTION()
		void Click_LeftButton();

	UFUNCTION()
		void Click_RightButton();

protected:
	UFUNCTION()
	void TestProcess(const int32 inIValue, const FString& inSValue, const int32 inTimeStamp);

private:
	UPROPERTY(Meta = (BindWidget))
	UButton* mLeftButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* mRightButton;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mTimeStampText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mIValueText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mSValueText;

private:
	FString	mIValue;
	FString	mSValue;
	FString	mTimeStamp;
};
