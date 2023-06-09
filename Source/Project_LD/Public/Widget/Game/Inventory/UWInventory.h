// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/Game/GameDatas.h"
#include "UWInventory.generated.h"

/**
 * 
 */
class UBorder;
class UBackgroundBlur;
class UTextBlock;
class UButton;
class UACInventoryComponent;

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
	UWidget* mGridInventory;

	UPROPERTY()
	UWidget* mEquipmentWindow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Border", meta = (BindWidget))
	UBorder* BackgroundBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Title", meta = (BindWidget))
	UTextBlock* TB_InvenTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Button", meta = (BindWidget))
	UButton* Btn_CloseInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Money", meta = (BindWidget))
	UTextBlock* TB_Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Money", meta = (BindWidget))
	UTextBlock* TB_Silver;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Money", meta = (BindWidget))
	UTextBlock* TB_Bronze;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UACInventoryComponent* mInvenComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "default")
	float mTileSize;

public:
	UFUNCTION()
	void InitInventory(UACInventoryComponent* InventoryComponent, float size);

	UFUNCTION()
	void CloseInventory();

	void RefreshMoney(int32 moneyGold, int32 moneySilver, int32 moneyBronze);

	void InventoryLoadRequest();
	void InventoryLoadRespawn();
};
