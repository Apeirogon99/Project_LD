// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Chat.generated.h"

class UButton;
class UEditableTextBox;
class UScrollBox;

UENUM(BlueprintType)
enum class EChat : uint8
{
	Chat_Unspecified	UMETA(DisplayName = "Chat_Unspecified"),
	Chat_World			UMETA(DisplayName = "Chat_World"),
	Chat_Party			UMETA(DisplayName = "Chat_Party"),
	Chat_Friend			UMETA(DisplayName = "Chat_Friend"),
};

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_Chat : public UUserWidget
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
	UEditableTextBox* mEditMessage;

	UPROPERTY(Meta = (BindWidget))
	UButton* mSendButton;

	UPROPERTY(Meta = (BindWidget))
	UButton* mWorldTab;

	UPROPERTY(Meta = (BindWidget))
	UButton* mPartyTab;

	UPROPERTY(Meta = (BindWidget))
	UButton* mFriendTab;

	UPROPERTY(Meta = (BindWidget))
	UScrollBox* mMessageScrollBox;

	UPROPERTY(Meta = (BindWidget))
	UButton* mDragButton;

public:

	UFUNCTION()
	void Committed_Message(const FText& inEditValue, ETextCommit::Type inCommitType);

	UFUNCTION()
	void Chanage_Message(const FText& inEditValue);

	UFUNCTION()
	void Click_SendButton();

	UFUNCTION()
	void Click_WorldTab();

	UFUNCTION()
	void Click_PartyTab();

	UFUNCTION()
		void Pressed_Drag();

	UFUNCTION()
		void Released_Drag();

	UFUNCTION()
	void Click_FriendTab();

public:
	UFUNCTION()
	void AddMessage(const FString& inPlayerID, const FString& inMessage, const EChat& inChatType);

	UFUNCTION()
	void RefreshMessageLog();

	UFUNCTION()
	void UpdateLocation();

	UFUNCTION()
	void FocusChat();

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> mChatBoxWidgetClass;

	UPROPERTY()
	TArray<UUserWidget*> mMessageLogs;

	UPROPERTY()
	FText mChangeMessage;

	UPROPERTY()
	EChat mChatType;

private:
	FVector2D		mPressedMousePoint;
	FTimerHandle	mUpdateLocationTimerHandle;
};
