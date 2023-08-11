// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PartyNotify.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_PartyNotify : public UUserWidget
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
		UTextBlock* mNotifyParty;

public:
	UFUNCTION()
		void SetNotifyParty(const FString& inPlayerName, const int32& inAction);

	UFUNCTION(BlueprintNativeEvent)
		void OnNotifyParty(int32 inAction);
	virtual int32 OnNotifyParty_Implementation(int32 inAction);
};
