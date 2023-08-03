// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_WorldChat.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_WorldChat : public UUserWidget
{
	GENERATED_BODY()

public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* mChatLog;

public:
	UFUNCTION()
		void SetWorldChat(const FString& inPlayerName, const FString& inMessage, const float& inDuration);

private:
	UPROPERTY()
		float mChatTime;

	UPROPERTY()
		bool mIsMessage;
};
