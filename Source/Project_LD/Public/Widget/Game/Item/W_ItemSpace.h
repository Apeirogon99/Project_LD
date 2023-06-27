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
class UItemObjectData;

UCLASS()
class PROJECT_LD_API UW_ItemSpace : public UUserWidget
{
	GENERATED_BODY()
	
public:
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

public:
	UFUNCTION()
	void FalseExist();

public:
	void Init(UACInventoryComponent* InvenComponent, UACEquipment* EquipmentComponent);
	void Refresh(UItemObjectData* ItemObjectData);
	void ReMakeWidget(UItemObjectData* ItemObjectData);
	void CreateItemWidget(UItemObjectData* ItemObjectData);
	//void ReplacePacket(UItemObjectData* InvenObjectData, UItemObjectData* EquipObejctData);

public:
	FORCEINLINE bool												GetIsRightItemCategory() const		{ return bRigthItemCategory; }
	FORCEINLINE bool												GetIsExist() const								{ return bExist; }
	FORCEINLINE float												GetSizeX() const									{ return mSizeX; }
	FORCEINLINE float												GetSizeY() const									{ return mSizeY; }
	FORCEINLINE int32												GetCategoryId() const							{ return mCategoryId; }
	FORCEINLINE TSubclassOf<UUserWidget>			GetImageAsset() const						{ return mImageAsset; }
	FORCEINLINE UUWEquipItem*							GetEquipmentItemSlot() const			{ return mEquipmentItemSlot; }
	FORCEINLINE TArray<UTexture2D*>					GetmTextureArr() const						{ return mTextureArr; }
	FORCEINLINE UACInventoryComponent*			GetInventoryComponent() const		{ return mInvenComponent; }
	FORCEINLINE UACEquipment*							GetEquipmentComponent() const		{ return mEquipmentComponent; }


public:
	void		SetIsRightItemCategory(const bool RigthItemCategory)												{ bRigthItemCategory = RigthItemCategory; }
	void		SetIsExist(const bool Exist)																							{ bExist = Exist; }
	void		SetSizeX(const float SizeX)																							{ mSizeX = SizeX; }
	void		SetSizeY(const float SizeY)																							{ mSizeY = SizeY; }
	void		SetCategoryId(const int32 CategoryId)																			{ mCategoryId = CategoryId; }
	void		SetImageAsset(const TSubclassOf<UUserWidget> ImageAsset)									{ mImageAsset = ImageAsset; }
	void		SetEquipmentItemSlot(UUWEquipItem* EquipmentItemSlot)										{ mEquipmentItemSlot = EquipmentItemSlot; }
	void		SetmTextureArr(const TArray<UTexture2D*> TextureArr)										{ mTextureArr = TextureArr; }
	void		SetInventoryComponent(UACInventoryComponent* InvenComponent)						{ mInvenComponent = InvenComponent; }
	void		SetEquipmentComponent(UACEquipment* EquipmentComponent)								{ mEquipmentComponent = EquipmentComponent; }

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bRigthItemCategory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bExist;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Size", meta = (AllowPrivateAccess = "true"))
	float mSizeX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Size", meta = (AllowPrivateAccess = "true"))
	float mSizeY;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Id", meta = (AllowPrivateAccess = "true"))
	int32 mCategoryId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Panel", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> mImageAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Panel", meta = (AllowPrivateAccess = "true"))
	UUWEquipItem* mEquipmentItemSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UTexture2D*> mTextureArr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UACInventoryComponent* mInvenComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	UACEquipment* mEquipmentComponent;
};
