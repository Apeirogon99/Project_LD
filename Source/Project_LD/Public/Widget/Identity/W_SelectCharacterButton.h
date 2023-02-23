// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SelectCharacterButton.generated.h"

class UButton;
class UTextBlock;
class UAnimationAsset;
class ANetworkCharacter;
struct FCharacterAppearance;
struct FCharacterDatas;

UENUM(BlueprintType)
enum class EClickMode : uint8
{
	None			UMETA(DisplayName = "None"),
	Create 			UMETA(DisplayName = "Create"),
	Start			UMETA(DisplayName = "Start"),
	Appearance		UMETA(DisplayName = "Appearance"),
	Delete			UMETA(DisplayName = "Delete"),
	ReviseName		UMETA(DisplayName = "ReviseName"),
};

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_SelectCharacterButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
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
	void SetCharacterInfo(const FCharacterDatas& inCharacterDatas, const FCharacterAppearance& inCharacterAppearance);

	UFUNCTION()
	void SetClickMode(EClickMode inClickMode);

	UFUNCTION()
	void PreviousClickMode();

protected:
	UFUNCTION()
		void StartCharacter();

	UFUNCTION()
		void CreateCharacter();

	UFUNCTION()
		void AppearanceCharacter();

	UFUNCTION()
		void DeleteCharacter();

	UFUNCTION()
		void ReviseNameCharacter();

	UFUNCTION()
		void CancleButton();

public:
	UPROPERTY(EditAnywhere, Category = "Default")
	int32 mCharacterButtonNumber;

	UPROPERTY(EditAnywhere, Category = "Default")
	FVector mCharacterLocation;

	UPROPERTY(EditAnywhere, Category = "Default")
	FRotator mCharacterRotation;

	UPROPERTY(EditAnywhere, Category = "Default")
	TSubclassOf<ANetworkCharacter> mDummyCharacterClass;

private:

	UPROPERTY()
	ANetworkCharacter* mCharacter;

	UPROPERTY()
	EClickMode mClickMode;
};
