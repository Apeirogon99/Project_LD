// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Singin.generated.h"

class UEditableTextBox;
class UCheckBox;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_Singin : public UUserWidget
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
		UEditableTextBox* mEditId;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* mEditPassword;

	UPROPERTY(Meta = (BindWidget))
		UButton* mSinginButton;

	UPROPERTY(Meta = (BindWidget))
		UButton* mSingupButton;

	UPROPERTY(Meta = (BindWidget))
		UCheckBox* mAutoSingin;

public:
	UFUNCTION()
		void Click_Singin();

	UFUNCTION()
		void Click_Singup();

	UFUNCTION()
		void Committed_ID(const FText& message);

	UFUNCTION()
		void Committed_Password(const FText& message);

	UFUNCTION()
		void Check_AutoSingin(bool bIsChecked);

	UFUNCTION()
		void EnableSinginButton();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
		FLinearColor mButtonActiveColor;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
		FLinearColor mButtonDeactivationColor;

private:
	UPROPERTY()
		FString mID;

	UPROPERTY()
		FString mPassword;

	UPROPERTY()
		bool	mIsAutoSingin;
};
