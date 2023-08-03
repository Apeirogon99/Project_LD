// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget/Game/Chat/W_Chat.h"
#include "W_ChatBox.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_ChatBox : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//virtual void NativeOnInitialized() override;
	//virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	//virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* mChatLog;

public:
	UFUNCTION()
	void SetChatBox(const FString& inPlayerName, const FString& inMessage, const EChat& inChatType);

public:
	UFUNCTION()
	const EChat& GetChatType() const;

private:
	EChat mChatType;
};
