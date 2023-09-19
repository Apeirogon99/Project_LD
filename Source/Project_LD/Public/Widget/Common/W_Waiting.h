// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Waiting.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_Waiting : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mTitle;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mTime;

public:
	UFUNCTION(BlueprintCallable)
		void SetTitle(const FString& inTitle);

	UFUNCTION(BlueprintCallable)
		void SetTime(const int32& inTime);

private:
	UPROPERTY()
		int32 mTimeCount;

	UPROPERTY()
		float mDeltaCount;
};
