// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PartyPlayerInfo.generated.h"

class UTextBlock;
class UImage;
class UProgressBar;
class UScrollBox;
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

	UPROPERTY(Meta = (BindWidget))
	UProgressBar* mHP;

	UPROPERTY(Meta = (BindWidget))
	UProgressBar* mMP;

	UPROPERTY(Meta = (BindWidget))
	UScrollBox* BuffList;

public:
	UFUNCTION()
		void SetPlayerInfo(const int64& inRemoteID, const int64& inLeaderRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsSelf);

	//UFUNCTION()
	//	void PushBuff(const int32& inBuffID, const float inDuration = MAX_FLT);

	//UFUNCTION()
	//	void ReleaseBuff(const int32& inBuffID);

	UFUNCTION()
	void UpdateHealthBar();

	UFUNCTION()
	void UpdateManaBar();

	UFUNCTION()
	void UpdateBuffInfo();

public:
	const int64& GetRemoteID();

public:
	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mWarriorClassTexture;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mWizardClassTexture;

	int buffArr[3];

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int64 mRemoteID;
};
