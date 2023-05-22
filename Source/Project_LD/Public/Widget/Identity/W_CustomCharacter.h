// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Struct/Game/CharacterDatas.h>
#include "W_CustomCharacter.generated.h"

class UButton;
class UTextBlock;
class UImage;
class UW_ColorPicker;
class ANetworkCharacter;
class AAppearanceCharacter;
struct FCharacterAppearance;
enum class EEquipment : uint8;
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
	UButton* mMaleButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* mFemaleButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* mSkinColorButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* mHairColorButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* mEyeColorButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* mEyebrowColorButton;

	UPROPERTY(Meta = (BindWidget))
	UImage* mSkinColor;

	UPROPERTY(Meta = (BindWidget))
	UImage* mHairColor;

	UPROPERTY(Meta = (BindWidget))
	UImage* mEyeColor;

	UPROPERTY(Meta = (BindWidget))
	UImage* mEyebrowColor;

public:
	UFUNCTION()
		void Click_Create();
	
	UFUNCTION()
		void Click_MaleRace();

	UFUNCTION()
		void Click_FemaleRace();

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
		void ToggleColorPicker(EAppearance inDummyPart);

	UFUNCTION()
		void UpdateDummyCharacterPartColor();

	UFUNCTION()
		void UpdateColorPicker();

	UFUNCTION()
		void UpdateEquipment();

	UFUNCTION()
		void SetDummyCharacter(AAppearanceCharacter* inDummyCharacter);

	UFUNCTION()
		void SetClassText(const ECharacterClass inClass);

public:

	UPROPERTY()
	UWidget* mBackButton;

	UPROPERTY()
	UWidget* mEyebrowBox;

	UPROPERTY()
	UW_ColorPicker* mColorPicker;

	UPROPERTY()
	EAppearance mCurrentDummyAppearance;

	UPROPERTY()
	AAppearanceCharacter* mCurrentDummyCharacter;

	FCharacterAppearance mTempCharacterAppearance;
	FCharacterEquipment mTempCharacterEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	int32	mHairNumber;

	int32	mOldHairNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	ECharacterRace	mCurrentDummyRace;

	bool IsSetupCharacter;
};
