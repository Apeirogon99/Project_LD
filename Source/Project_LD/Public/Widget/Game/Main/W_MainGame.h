// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "W_MainGame.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class PROJECT_LD_API UW_MainGame : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UWidget* mBottomUI;

public:
	UFUNCTION()
	void ChatOpen();

	UFUNCTION()
	void FocusChat();

	UFUNCTION()
	void InventoryOpenRequest();

	UFUNCTION()
	void InventoryOpenResponse();

public:
	void Init();

protected:
	virtual void NativeConstruct() override;

private:
	bool misInventoryOpen;
	bool misChatOpen;

private:
	UPROPERTY(meta = (BindWidget))
		UButton* Btn_Chat;

	UPROPERTY(meta = (BindWidget))
		UButton* Btn_Inventory;
};
