// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_NotifyFriend.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_NotifyFriend : public UUserWidget
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
		UTextBlock* mNotifyFriend;

public:
	UFUNCTION()
		void SetNotifyFriend(const FString& inPlayerName, const bool& inConnect);

	UFUNCTION(BlueprintNativeEvent)
	void OnNotifyFriend();
	virtual void OnNotifyFriend_Implementation();
};
