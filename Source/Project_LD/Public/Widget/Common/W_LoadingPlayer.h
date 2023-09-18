// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_LoadingPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_LoadingPlayer : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void UpdateLoadingPlayer(FString inMaxNumber, FString inLeastNumber);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
		FText mMaxNumber;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
		FText mLeastNumber;
};
