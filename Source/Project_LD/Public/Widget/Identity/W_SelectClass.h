// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SelectClass.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_SelectClass : public UUserWidget
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
		UButton* mWarriorButton;

	UPROPERTY(Meta = (BindWidget))
		UButton* mWizardButton;

public:
	UFUNCTION()
		void Click_Warrior();

	UFUNCTION()
		void Click_Wizard();

protected:
	UFUNCTION()
		void SelectClass(const FString& inClass, EClass inClassNum);


	UPROPERTY()
		UWidget* mBackButton;
};
