// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EditBox.generated.h"

DECLARE_DELEGATE_OneParam(FButtonDelegate, const FString&);

class UEditableTextBox;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_EditBox : public UUserWidget
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
		UTextBlock* mTitleText;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* mConfirmButtonText;

	UPROPERTY(Meta = (BindWidget))
		UEditableTextBox* mEditbox;

	UPROPERTY(Meta = (BindWidget))
		UButton* mConfirmButton;

public:
	UFUNCTION(BlueprintCallable)
		void SetEditHint(const FText& inHint);

	UFUNCTION(BlueprintCallable)
		void SetEditTitleText(const FText& inTitle);

	UFUNCTION(BlueprintCallable)
		void SetConfrimButtonText(const FText& inButtonText);

public:

	UFUNCTION()
		void Committed_Editbox(const FText& inEditValue);

	UFUNCTION()
		void Click_Confirm();

	UFUNCTION()
		void EnableButton();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Default")
		FLinearColor mButtonActiveColor;

	UPROPERTY(EditDefaultsOnly, Category = "Default")
		FLinearColor mButtonDeactivationColor;

	UPROPERTY()
		FString mEditValue;

	FButtonDelegate mConfirmDelegate;
};
