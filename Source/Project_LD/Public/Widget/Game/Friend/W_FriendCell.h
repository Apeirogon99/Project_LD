// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_FriendCell.generated.h"

class UTextBlock;
class UImage;
class UButton;

UENUM(BlueprintType)
enum class EConnectState : uint8
{
	None			UMETA(DisplayName = "None"),
	Connect 		UMETA(DisplayName = "Connect"),
	Away			UMETA(DisplayName = "Away"),
	DisConnect		UMETA(DisplayName = "DisConnect"),
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	None			UMETA(DisplayName = "None"),
	Invite 			UMETA(DisplayName = "Invite"),
	Request			UMETA(DisplayName = "Request"),
	Block			UMETA(DisplayName = "Block"),
};

DECLARE_DELEGATE(FActionButtonDelegate);

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_FriendCell : public UUserWidget
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
	UTextBlock* mPlayerName;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mPlayerInfo;

	UPROPERTY(Meta = (BindWidget))
	UButton* mActionButton;

	UPROPERTY(Meta = (BindWidget))
	UImage* mConnectStateImage;

	UPROPERTY(Meta = (BindWidget))
	UImage* mActionImage;

public:
	UFUNCTION()
	void Click_ActionButton();

public:
	UFUNCTION()
	void SetPlayerName(const FString& inPlayerName);

	UFUNCTION()
	void SetPlayerInfo(const int32& inLevel, const int32& inClass, const int32& inLocale);

	UFUNCTION()
	void SetConnectStateImage(const EConnectState& inConnectState, const bool& inVisuble);

	UFUNCTION()
	void SetActionImage(const EActionState& inActionState);

public:
	UFUNCTION()
		const FString& GetPlayerName();

public:
	FActionButtonDelegate mActionButtonDelegate;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mConnectState;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mAwayState;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mDisConnectState;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mInvite;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mRequest;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mBlock;

private:
	UPROPERTY()
		FString mName;
};
