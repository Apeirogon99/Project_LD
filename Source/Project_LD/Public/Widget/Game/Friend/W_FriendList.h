// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_FriendList.generated.h"

class UScrollBox;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_FriendList : public UUserWidget
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

public:
	UFUNCTION()
		void ClearFriendList();

	UFUNCTION()
		void AddFriendList(const FString& inPlayerName, const int32& inLevel, const int32& inClass, const int32& inLocale, const int32& inState);

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> mFriendCellClass;

	UPROPERTY()
		TArray<UUserWidget*> mFriendLists;
};
