// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SkipSequence.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_SkipSequence : public UUserWidget
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
		UButton* mSkipButton;

public:
	void UpdateSkipSequence(FString inMaxNumber, FString inLeastNumber);

public:
	UFUNCTION()
		void Click_SkipButton();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
		FText mMaxNumber;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
		FText mLeastNumber;
};
