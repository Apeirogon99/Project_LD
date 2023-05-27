// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Struct/Game/GameDatas.h>
#include <Component/ACInventoryComponent.h>
#include <Widget/Game/Inventory/StoreInven/UWGridInventory.h>
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/Border.h"
#include "Components/BackgroundBlur.h"
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
	virtual void NativeDestruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	UPROPERTY()
	UWidget* GridInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panel", meta = (BindWidget))
	UBorder* BackgroundBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panel", meta = (BindWidget))
	UBackgroundBlur* BackgroundBlur;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UACInventoryComponent* ACInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "default")
	float TileSize;

public:
	UFUNCTION()
	void InitInventory(UACInventoryComponent* InventoryComponent, float size);
};
