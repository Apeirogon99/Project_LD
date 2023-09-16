// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EnterDungeon.generated.h"

class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_EnterDungeon : public UUserWidget
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
		UButton* mEnter;

	UPROPERTY(Meta = (BindWidget))
		UButton* mCancle;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* mTitle;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* mMessage;

public:
	UFUNCTION(BlueprintCallable)
		void SetTitle(const FString& inTitle);

	UFUNCTION(BlueprintCallable)
		void SetMessage(const FString& inMessage);

	UFUNCTION(BlueprintCallable)
		void SetDungeon(const int32& inDungeonID);

public:
	UFUNCTION()
		void Click_EnterButton();

	UFUNCTION()
		void Click_CancleButton();

private:

	UPROPERTY()
		int32 mDungeonID;
};
