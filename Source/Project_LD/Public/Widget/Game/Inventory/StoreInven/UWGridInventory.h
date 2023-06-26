// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Struct/Inventory/InventoryFrame.h>
#include "UWGridInventory.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECT_LD_API FMousePositionReturn
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position") bool Right;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position") bool Down;
};

class UBorder;
class UCanvasPanel;
class UACInventoryComponent;
class UACEquipment;

UCLASS()
class PROJECT_LD_API UUWGridInventory : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panel", meta = (BindWidget))
	UBorder* GridBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panel", meta = (BindWidget))
	UCanvasPanel* GridCanvas_Panel;

public:
	void Init(UACInventoryComponent* InvenComponent, float Size, UACEquipment* EquipmentComponent);
	void CreateLineSegments();
	FMousePositionReturn MousePositionInTile(FVector2D MousePosition);

public:
	UFUNCTION()
	void Refresh();

	UFUNCTION()
	void CallRemoved_Single(UItemObjectData*& ItemData);

	UFUNCTION(BlueprintCallable)
	void GetPayload(UDragDropOperation* Operator, UItemObjectData*& Payload) const;

	UFUNCTION(BlueprintCallable)
	bool IsRoomAvailableForPayload(UItemObjectData* Payload) const;

public:
	FORCEINLINE bool												GetDrawDropLocation() const				{ return mDrawDropLocation; }
	FORCEINLINE float												GetTileSize() const								{ return mTileSize; }
	FORCEINLINE UACInventoryComponent*			GetInventoryComponent() const			{ return mInventoryComponent; }
	FORCEINLINE UACEquipment*							GetEquipmentComponent() const			{ return mEquipmentComponent; }
	FORCEINLINE TArray<FLine>								GetLineArr() const									{ return mLineArr; }
	FORCEINLINE TSubclassOf<UUserWidget>			GetImageAsset() const							{ return mImageAsset; }
	FORCEINLINE FIntPoint										GetDraggedItemTopLeftTile() const		{ return mDraggedItemTopLeftTile; }

public:
	void		SetDrawDropLocation(bool DrawDropLocation)														{ mDrawDropLocation = DrawDropLocation; }
	void		SetTileSize(float TileSize)																						{ mTileSize = TileSize; }
	void		SetInventoryComponent(UACInventoryComponent* InventoryComponent)			{ mInventoryComponent = InventoryComponent; }
	void		SetEquipmentComponent(UACEquipment* EquipmentComponent)							{ mEquipmentComponent = EquipmentComponent; }
	void		SetLineArr(TArray<FLine> LineArr)																			{ mLineArr = LineArr; }
	void		SetImageAsset(TSubclassOf<UUserWidget> ImageAsset)										{ mImageAsset = ImageAsset; }
	void		SetDraggedItemTopLeftTile(FIntPoint DraggedItemTopLeftTile)							{ mDraggedItemTopLeftTile = DraggedItemTopLeftTile; }

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drag Drop", meta = (AllowPrivateAccess = "true"))
	bool mDrawDropLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	float mTileSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UACInventoryComponent* mInventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	UACEquipment* mEquipmentComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	TArray<FLine> mLineArr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Panel", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> mImageAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drag Drop", meta = (AllowPrivateAccess = "true"))
	FIntPoint mDraggedItemTopLeftTile;
};