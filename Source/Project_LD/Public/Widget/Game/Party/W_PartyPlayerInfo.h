// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PartyPlayerInfo.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_PartyPlayerInfo : public UUserWidget
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
		UImage* mClassImage;

	UPROPERTY(Meta = (BindWidget))
		UImage* mLeaderImage;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* mLevel;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* mName;

public:
	UFUNCTION()
		void SetPlayerInfo(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsLeader);

public:
	const int64& GetRemoteID();

public:
	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mWarriorClassTexture;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mWizardClassTexture;

private:
	int64 mRemoteID;
};
