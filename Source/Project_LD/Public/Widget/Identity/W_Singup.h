// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Singup.generated.h"

class UEditableTextBox;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_Singup : public UUserWidget
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
		UEditableTextBox* mEditEmail;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* mEditPassword;

	UPROPERTY(Meta = (BindWidget))
		UButton* mSingupButton;

	UPROPERTY(Meta = (BindWidget))
		UButton* mExitButton;

public:
	UFUNCTION()
		void Click_Singup();

	UFUNCTION()
		void Click_Exit();

	UFUNCTION()
		void Committed_ID(const FText& inId);

	UFUNCTION()
		void Committed_Email(const FText& inEmail);

	UFUNCTION()
		void Committed_Password(const FText& inPassword);

	UFUNCTION()
		void EnableSingupButton();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
		FLinearColor mButtonActiveColor;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
		FLinearColor mButtonDeactivationColor;

private:
	UPROPERTY()
		FString mID;

	UPROPERTY()
		FString mEmail;

	UPROPERTY()
		FString mEmailDomain;

	UPROPERTY()
		FString mPassword;
};
