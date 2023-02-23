// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Struct/Game/CharacterDatas.h>
#include "W_CustomCharacter.generated.h"

class UButton;
class UTextBlock;
class UW_ColorPicker;
class ANetworkCharacter;
struct FCharacterAppearance;
enum class EPart : uint8;
enum class ETribe : uint8;
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
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mClassText;

	UPROPERTY(Meta = (BindWidget))
	UButton* mCreateButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* mTribeButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* mSkinButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* mHairButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* mEyeButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* mEyebrowButton;

public:
	UFUNCTION()
		void Click_Create();
	
	UFUNCTION()
		void Click_Tribe();

	UFUNCTION()
		void Click_Skin();

	UFUNCTION()
		void Click_Hair();

	UFUNCTION()
		void Click_Eye();

	UFUNCTION()
		void Click_Eyebrow();

public:
	UFUNCTION()
		bool CanUpdate();

	UFUNCTION()
		void ToggleColorPicker(EPart inDummyPart);

	UFUNCTION()
		void UpdateDummyCharacterPartColor();

	UFUNCTION()
		void SetClassText(const int32 inClass);

public:

	UPROPERTY()
	UWidget* mBackButton;

	UPROPERTY()
	UWidget* mTribeSelectWidget;

	UPROPERTY()
	UW_ColorPicker* mColorPicker;

	UPROPERTY()
	EPart mCurrentDummyPart;

	UPROPERTY()
	ANetworkCharacter* mCurrentDummyCharacter;

	FCharacterAppearance mTempCharacterAppearance;
};
