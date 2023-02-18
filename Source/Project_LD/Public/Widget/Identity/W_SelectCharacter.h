// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SelectCharacter.generated.h"

class UW_SelectCharacterButton;
struct FCharacterDatas;
enum class EClickMode : uint8;

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_SelectCharacter : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
		void LoadCharacterInfo(const FCharacterDatas& inCharacterDatas);

protected:
	UFUNCTION()
	void LoadChild();

	UFUNCTION()
		void OnAppearanceButton();

	UFUNCTION()
		void OnDeleteButton();

	UFUNCTION()
		void OnReviseNameButton();

	UFUNCTION()
		void PreviousAllButtonMode();

	void ChangeAllButtonMode(EClickMode inClickMode);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TArray<UWidget*>	mCharacterButtonWidgets;

	UPROPERTY()
		UWidget* mBackButton;

	UPROPERTY()
		UWidget* mAppearanceButton;

	UPROPERTY()
		UWidget* mDeleteButton;

	UPROPERTY()
		UWidget* mReviseNameButton;


	EClickMode mCurrentClickMode;
};
