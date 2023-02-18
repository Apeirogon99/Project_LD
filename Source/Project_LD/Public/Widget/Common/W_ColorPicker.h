// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_ColorPicker.generated.h"

class UButton;
class UImage;
class UTextBlock;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_ColorPicker : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UButton*			mDragButton;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UTextBlock*			mPickerTarget;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UEditableTextBox*	mColorEdit;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UButton*			mRefreshButton;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UButton*			mRandomButton;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UButton*			mPickerButton;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UImage*				mPickerPreviewImage;

public:
	UFUNCTION()
		void Pressed_Drag();

	UFUNCTION()
		void Released_Drag();

	UFUNCTION()
		void Click_Refresh();

	UFUNCTION()
		void Click_Random();

	UFUNCTION()
		void Click_Picker();

	UFUNCTION()
		void Committed_Color(const FText& inEditValue);

public:
	UFUNCTION(BlueprintCallable)
		void UpdateLocation();

	UFUNCTION(BlueprintCallable)
		void SetPickerTarget(const FString& inTarget);

	UFUNCTION(BlueprintCallable)
		void SetPickerPreviewColor(const FLinearColor& inColor);

	UFUNCTION(BlueprintCallable)
		void SetPickerColor(const FString& inColor);

	UFUNCTION(BlueprintCallable)
		const FString& GetColorString();

	UFUNCTION(BlueprintCallable)
		FLinearColor GetLinearColor();

	UFUNCTION(BlueprintNativeEvent)
	void OnUsed(FLinearColor inColor);
	virtual FLinearColor OnUsed_Implementation(FLinearColor inColor);

private:
	FVector2D		mPressedMousePoint;
	FTimerHandle	mUpdateLocationTimerHandle;

public:
	UPROPERTY(BlueprintReadWrite)
	FLinearColor	mLinearColor;

	UPROPERTY(BlueprintReadWrite)
	FLinearColor	mOldLinearColor;

	FString			mColorStr;
};
