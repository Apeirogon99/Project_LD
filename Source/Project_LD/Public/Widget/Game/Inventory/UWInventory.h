// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Component/ACInventoryComponent.h>
#include <Widget/Game/Inventory/StoreInven/UWGridInventory.h>
#include "Blueprint/UserWidget.h"
#include "UWInventory.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UUWInventory : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (BindWidget))
	UUWGridInventory* InventoryStore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", Meta = (ExposeOnSpawn = true))
	UACInventoryComponent* ACInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "default", Meta = (ExposeOnSpawn = true))
	float TileSize;

public:
	UFUNCTION()
	void DelayInit();
};
