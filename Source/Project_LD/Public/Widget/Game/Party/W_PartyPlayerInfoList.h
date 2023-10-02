// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PartyPlayerInfoList.generated.h"

class UScrollBox;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_PartyPlayerInfoList : public UUserWidget
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
		UScrollBox* mPartyPlayerInfoScrollBox;

	UPROPERTY(Meta = (BindWidget))
		UButton* mDragButton;

public:
	UFUNCTION()
		void ClearPartyPlayerInfoList();

	UFUNCTION()
		void AddPartyList(const int64& inRemoteID, const int64& inLeaderRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsSelf);

	UFUNCTION()
		void RemovePartyPlayerInfo(const int64& inRemoteID);

public:
	void RequestPushBuff(const int64 inRemoteID, const int32& inBuffID, const int64& inBuffDuration);
	void RequestReleaseBuff(const int64 inRemoteID, const int32& inBuffID);

public:
	UFUNCTION()
		void UpdateLocation();

	UFUNCTION()
		void Pressed_Drag();

	UFUNCTION()
		void Released_Drag();

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> mPartyPlayerInfoClass;

	UPROPERTY()
		TArray<UUserWidget*> mPartyPlayerInfoLists;

private:
	FVector2D		mPressedMousePoint;
	FTimerHandle	mUpdateLocationTimerHandle;
};
