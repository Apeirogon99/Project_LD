// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_ResponseUseKeyAction.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_ResponseUseKeyAction : public UUserWidget
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
		UTextBlock* mMessage;

public:
	UFUNCTION(BlueprintCallable)
		void SetResponseUseKeyAction(const int32& inKey, const FString& inMessage);

public:
	UFUNCTION(BlueprintNativeEvent)
		void OnActiveAnimation();
	virtual void OnActiveAnimation_Implementation();

};
