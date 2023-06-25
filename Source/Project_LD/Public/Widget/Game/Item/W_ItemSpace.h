// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_ItemSpace.generated.h"

/**
 * 
 */
class UBorder;
class UCanvasPanel;
class USizeBox;
class UImage;
class UACInventoryComponent;
class UACEquipment;
class UUWEquipItem;

UCLASS()
class PROJECT_LD_API UW_ItemSpace : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Size")
	float mSizeX;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Size")
	float mSizeY;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Id")
	int32 mCategoryId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panel")
	TSubclassOf<UUserWidget> mImageAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panel")
	UUWEquipItem* EquipmentItemSlot;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<UTexture2D*> mTextureArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	UCanvasPanel* ItemCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	USizeBox* SlotSizeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	UBorder* categoryBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	UImage* ImgSlotFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	UImage* ImgSlot;

	bool bRigthItemCategory;
	bool bExist;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UACInventoryComponent* mInvenComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	UACEquipment* mEquipmentComponent;

public:
	void Init(UACInventoryComponent* InvenComponent, UACEquipment* EquipmentComponent);

	UFUNCTION()
	void FalseExist();

	UFUNCTION()
	void Refresh(UItemObjectData* ItemData);

	UFUNCTION()
	void ReMakeWidget(UItemObjectData* ItemObjectDatat);

	//void ReplacePacket(UItemObjectData* InvenObjectData, UItemObjectData* EquipObejctData);
};
