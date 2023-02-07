// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SelectCharacter.generated.h"

class UW_SelectCharacterButton;
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
		void LoadCharacterInfo(int32 inNumber, const FString& inLevel, const FString& inName);

protected:
	void LoadChild();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TArray<UWidget*>	mCharacterButtonWidgets;
};
