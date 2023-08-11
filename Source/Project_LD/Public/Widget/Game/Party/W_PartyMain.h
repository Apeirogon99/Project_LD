// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PartyMain.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_PartyMain : public UUserWidget
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
		UButton* mPlayerListTab;

	UPROPERTY(Meta = (BindWidget))
		UButton* mRequestPartyTab;

	UPROPERTY(Meta = (BindWidget))
		UButton* mRequestListTab;

	UPROPERTY(Meta = (BindWidget))
		UButton* mDragButton;

public:
	UFUNCTION()
		void Click_PartyListTab();

	UFUNCTION()
		void Click_RequestPartyTab();

	UFUNCTION()
		void Click_RequestListTab();

public:
	UFUNCTION(BlueprintNativeEvent)
		void OnPlayerListTab();
	virtual void OnPlayerListTab_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void OnRequestListTab();
	virtual void OnRequestListTab_Implementation();

public:
	UFUNCTION()
		void UpdateLocation();

	UFUNCTION()
		void Pressed_Drag();

	UFUNCTION()
		void Released_Drag();

private:
	UPROPERTY()
		UWidget* mPartyPlayerList;

	UPROPERTY()
		UWidget* mPartyRequesrList;

private:
	FVector2D		mPressedMousePoint;
	FTimerHandle	mUpdateLocationTimerHandle;
};
