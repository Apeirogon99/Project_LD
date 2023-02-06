// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_CustomCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_CustomCharacter : public UUserWidget
{
	GENERATED_BODY()

public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
public:
	UFUNCTION()
		void SendNickName(const FString& inNickName);

	UFUNCTION()
		void ResultNickName(const bool inResult);

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> mEditBoxClass;

private:
	UUserWidget* mEditNickNameBox;
};
