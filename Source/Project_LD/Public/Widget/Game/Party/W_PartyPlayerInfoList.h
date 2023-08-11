// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PartyPlayerInfoList.generated.h"

class UScrollBox;
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

public:
	UFUNCTION()
		void ClearPartyPlayerInfoList();

	UFUNCTION()
		void AddPartyList(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsLeader);

	UFUNCTION()
		void RemovePartyPlayerInfo(const int64& inRemoteID);

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> mPartyPlayerInfoClass;

	UPROPERTY()
		TArray<UUserWidget*> mPartyPlayerInfoLists;
};
