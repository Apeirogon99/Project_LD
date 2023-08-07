// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>
#include "W_FriendMain.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_FriendMain : public UUserWidget
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
		UButton* mFriendTab;

	UPROPERTY(Meta = (BindWidget))
		UButton* mRequestTab;

	UPROPERTY(Meta = (BindWidget))
		UButton* mBlockTab;

public:
	UFUNCTION()
		void Click_FriendTab();

	UFUNCTION()
		void Click_RequestTab();

	UFUNCTION()
		void Click_BlockTab();

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnFriendTab();
	virtual void OnFriendTab_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void OnRequestTab();
	virtual void OnRequestTab_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void OnBlockTab();
	virtual void OnBlockTab_Implementation();

public:
	void LoadFriendListType(const google::protobuf::RepeatedPtrField<Protocol::SFriend>& inFriends, const int32& inListType);

public:
	const int32& GetFriendListType();

private:
	UPROPERTY()
		UWidget* mFriendList;

	UPROPERTY()
		UWidget* mFriendRequesrList;

	UPROPERTY()
		UWidget* mFriendBlockList;

	UPROPERTY()
		int32	mFriendListType;
};
