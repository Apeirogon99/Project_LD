// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/Game/GameDatas.h"
#include <Component/ACInventoryComponent.h>
#include "UWInventory.generated.h"

/**
 * 
 */
class UBorder;
class UBackgroundBlur;

UCLASS()
class PROJECT_LD_API UUWInventory : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	UPROPERTY()
	UWidget* GridInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panel", meta = (BindWidget))
		UBorder* BackgroundBorder;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UACInventoryComponent* mInvenComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "default")
	float mTileSize;

public:
	UFUNCTION()
	void InitInventory(UACInventoryComponent* InventoryComponent, float size);

	void InventoryLoadRequest();
	void InventoryLoadRespawn();
};
