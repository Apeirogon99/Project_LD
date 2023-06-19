// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Blueprint/IUserObjectListEntry.h>
#include "W_SelectServerButton.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_SelectServerButton : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

public:
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mServerName;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mServerState;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* mServerCharacterCount;

	UPROPERTY(Meta = (BindWidget))
	UButton* mSelectServerButton;

public:
	UFUNCTION()
		void Click_SelectServerButton();

	UFUNCTION()
		void Init(const int32 inServerID, const FString& inName, const float inState, const int32 inCharacterCount, const bool inBackGround);

private:
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		bool mIsBackGround;

	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		int32 mServerID;

	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		FString mName;

	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		float mState;

	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
		int32 mCharacterCount;
};
