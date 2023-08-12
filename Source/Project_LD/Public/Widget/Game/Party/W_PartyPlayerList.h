// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PartyPlayerList.generated.h"

class UScrollBox;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_PartyPlayerList : public UUserWidget
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

	UPROPERTY(Meta = (BindWidget))
		UButton* mCreateParty;

public:
	UFUNCTION()
		void Click_CreateParty();

public:
	UFUNCTION()
		void ClearPartyList();

	UFUNCTION()
		void AddPartyList(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName, const bool& inIsSelf, const bool& inIsLeader);

	UFUNCTION()
	void RemovePartyList(const int64& inRemoteID);

	UFUNCTION()
		void UpdatePartyList();

public:
	UFUNCTION(BlueprintNativeEvent)
		void OnChangeCreateWidget(bool isCreate);
	virtual bool OnChangeCreateWidget_Implementation(bool isCreate);
	
public:
	int32 GetPartyPlayerListNumber();

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> mPartyPlayerCellClass;

	UPROPERTY()
		TArray<UUserWidget*> mPartyPlayerLists;
};
