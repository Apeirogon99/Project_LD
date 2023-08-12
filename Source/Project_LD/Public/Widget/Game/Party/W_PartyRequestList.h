// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PartyRequestList.generated.h"

class UScrollBox;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_PartyRequestList : public UUserWidget
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
		UScrollBox* mPartyScrollBox;

public:
	UFUNCTION()
		void ClearPartyList();

	UFUNCTION()
		void AddRequestPartyList(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName);

	UFUNCTION()
		void RemoveRequestPartyList(const int64& inRemoteID);

public:
	int32 GetRequestPartyPlayerListNumber();

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> mPartyPlayerCellClass;

	UPROPERTY()
		TArray<UUserWidget*> mPartyPlayerLists;
};
