// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PartyMain.generated.h"

class UTextBlock;
class UButton;
class UImage;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_PartyMain : public UUserWidget
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
		UButton* mPlayerListTab;

	UPROPERTY(Meta = (BindWidget))
		UButton* mRequestPartyTab;

	UPROPERTY(Meta = (BindWidget))
		UButton* mRequestListTab;

	UPROPERTY(Meta = (BindWidget))
		UButton* mDragButton;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* mPlayerCount;

	UPROPERTY(Meta = (BindWidget))
		UImage* mResponeImage;

public:
	UFUNCTION()
	void ClearPlayerList();

	UFUNCTION()
	void PushPlayerList(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsSelf, const bool& inIsLeader);

	UFUNCTION()
	void ReleasePlayerList(const int64& inRemoteID);

	UFUNCTION()
	void ClearRequestList();

	UFUNCTION()
	void PushRequestList(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName);

	UFUNCTION()
	void ReleaseRequestList(const int64& inRemoteID);

public:
	UFUNCTION()
		void Click_PartyListTab();

	UFUNCTION()
		void Click_RequestPartyTab();

	UFUNCTION()
		void Click_RequestListTab();

public:
	UFUNCTION(BlueprintNativeEvent)
		void OnPlayerListTab();
	virtual void OnPlayerListTab_Implementation();

	UFUNCTION(BlueprintNativeEvent)
		void OnRequestListTab();
	virtual void OnRequestListTab_Implementation();

public:
	UFUNCTION()
		void UpdateLocation();

	UFUNCTION()
		void Pressed_Drag();

	UFUNCTION()
		void Released_Drag();

public:
	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mHaveRequestListTexture;

	UPROPERTY(EditAnywhere, Category = "Widget")
		UTexture2D* mNotHaveRequestListTexture;

private:
	UPROPERTY()
		UWidget* mPartyPlayerList;

	UPROPERTY()
		UWidget* mPartyRequesrList;

private:
	FVector2D		mPressedMousePoint;
	FTimerHandle	mUpdateLocationTimerHandle;
};
