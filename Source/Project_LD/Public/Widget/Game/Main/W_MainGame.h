// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "W_MainGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_MainGame : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;


private:
	bool misInventoryOpen;

public:
	void InventoryOpenRequest();
};
