// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SelectCharacterButton.generated.h"

class UButton;
class UTextBlock;
class UAnimationAsset;
class AC_Dummy;

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_SelectCharacterButton : public UUserWidget
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
	UButton* mCharacterButton;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mCharacterInfoText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mButtonText;

public:
	UFUNCTION()
	void Click_Character();

public:
	UFUNCTION()
	void SetCharacterInfo(const FString& inLevel, const FString& inName);

protected:
	UFUNCTION()
		void StartCharacter();

	UFUNCTION()
		void CreateCharacter();

	UFUNCTION()
		void CancleExitGame();

public:
	UPROPERTY(EditAnywhere, Category = "Default")
	int32 mCharacterButtonNumber;

	UPROPERTY(EditAnywhere, Category = "Default")
	FVector mCharacterLocation;

	UPROPERTY(EditAnywhere, Category = "Default")
	FRotator mCharacterRotation;

	UPROPERTY(EditAnywhere, Category = "Default")
	TSubclassOf<AC_Dummy> mDummyCharacterClass;

	UPROPERTY(EditAnywhere, Category = "Default")
	UAnimationAsset* mDefaultCharacterAnimation;

	UPROPERTY(EditAnywhere, Category = "Default")
	UAnimationAsset* mSelectCharacterAnimation;

private:
	bool mIsInfo;

	UPROPERTY()
	AC_Dummy* character;
};
