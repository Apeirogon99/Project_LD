// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWEquipmentWindow.generated.h"

/**
 * 
 */
class UACInventoryComponent;
class UButton;
class UImage;
class UCanvasPanel;
class UTextBlock;

UCLASS()
class PROJECT_LD_API UUWEquipmentWindow : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	UButton* Btn_OpenState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button | Image", meta = (BindWidget))
	UImage* StateButtonIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | Canvas", meta = (BindWidget))
	UCanvasPanel* StatusCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SAttackDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SAttackDamageGrowthValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SArmor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SArmorGrowthValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SHealthGrowthValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SManaGrowthValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SMoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SMoveSpeedGrowthValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SAttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SAttackSpeedGrowthValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SCriticalPercent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SCriticalPercentGrowthValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SCriticalDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status | TextBlock", meta = (BindWidget))
	UTextBlock* TB_SCriticalDamageGrowthValue;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UACInventoryComponent* mInvenComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* mTextureRightArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	UTexture2D* mTextureLeftArrow;

public:
	void Init(UACInventoryComponent* InvenComponent);

	UFUNCTION()
	void OpenStatus();
};
