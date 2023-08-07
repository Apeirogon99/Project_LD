// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_FriendRequestList.generated.h"

class UButton;
class UScrollBox;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_FriendRequestList : public UUserWidget
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
		UScrollBox* mFriendScrollBox;

	UPROPERTY(Meta = (BindWidget))
		UButton*	mRequest;

public:
	UFUNCTION()
		void Click_Request();

public:
	UFUNCTION()
		void ClearFriendList();

	UFUNCTION()
		void AddFriendList(const FString& inPlayerName);

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> mFriendCellClass;

	UPROPERTY()
		TArray<UUserWidget*> mFriendLists;
};
