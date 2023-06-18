// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Struct/Game/CharacterDatas.h>
#include "W_SelectCharacterButton.generated.h"

class UButton;
class UTextBlock;
class UAnimationAsset;
class ANetworkCharacter;
class AAppearanceCharacter;
class UImage;
struct FCharacterAppearance;
struct FCharacterData;

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
	UImage* mButtonImage;

public:
	UFUNCTION()
	void Click_Character();

public:
	UFUNCTION()
	void SetCharacterInfo(const FCharacterData& inCharacterData);

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
	TArray<TSubclassOf<AAppearanceCharacter>> mDummyCharacterClass;

	UPROPERTY(EditAnywhere, Category = "Default")
	UTexture2D* mAddTexture;

	UPROPERTY(EditAnywhere, Category = "Default")
	UTexture2D* mCheckTexture;

private:

	UPROPERTY()
	AAppearanceCharacter* mCharacter;

	UPROPERTY()
	EClickMode mClickMode;

	UPROPERTY()
	FCharacterData mCharacterData;
};
