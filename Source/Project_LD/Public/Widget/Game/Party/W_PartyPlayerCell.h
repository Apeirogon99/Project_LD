// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PartyPlayerCell.generated.h"

UENUM(BlueprintType)
enum class EPartyListType : uint8
{
	None			UMETA(DisplayName = "None"),
	PlayerList 		UMETA(DisplayName = "Invite"),
	RequestList		UMETA(DisplayName = "Request"),
};

class UTextBlock;
class UImage;
class UButton;

DECLARE_DELEGATE(FPartyActionButtonDelegate);

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_PartyPlayerCell : public UUserWidget
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
		UTextBlock* mPlayerInfo;

	UPROPERTY(Meta = (BindWidget))
		UButton* mActionButtonA;

	UPROPERTY(Meta = (BindWidget))
		UButton* mActionButtonB;

	UPROPERTY(Meta = (BindWidget))
		UImage* mActionImageA;

	UPROPERTY(Meta = (BindWidget))
		UImage* mActionImageB;

	UPROPERTY(Meta = (BindWidget))
		UImage* mLeaderImage;

public:
	UFUNCTION()
		void Click_ActionButtonA();

	UFUNCTION()
		void Click_ActionButtonB();

public:
	UFUNCTION()
		void SetPlayerInfo(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName);
	
	UFUNCTION()
		void SetListType(const bool& inIsSelf, const int64& inLeaderRemoteID, const EPartyListType& inPartyListType);

	UFUNCTION()
		const int64& GetRemoteID();

public:
	FPartyActionButtonDelegate mActionButtonDelegateA;
	FPartyActionButtonDelegate mActionButtonDelegateB;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mWarriorClassTexture;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mWizardClassTexture;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mLeaderTexture;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mKickOutTexture;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mAcceptTexture;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mCancleTexture;

	UPROPERTY(EditAnywhere, Category = "Widget")
		int64	mRemoteID;
};
