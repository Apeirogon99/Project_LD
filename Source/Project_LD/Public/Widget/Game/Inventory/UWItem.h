// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/Game/GameDatas.h"
#include "UWItem.generated.h"

/**
 * 
 */
class USizeBox;
class UBorder;
class UImage;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRemoved, UItemObjectData*);

UCLASS(BlueprintType)
class PROJECT_LD_API UUWItem : public UUserWidget
{
	GENERATED_BODY()

public: 
	FOnRemoved OnRemoved;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USizeBox* BackgroundSizeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* BackgroundBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemBackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage;

public:
	void Refresh();
	void Rotate();

public:
	FORCEINLINE bool										GetIsEnter() const								{ return mIsEnter; }
	FORCEINLINE float										GetTileSize() const							{ return mTileSize; }
	FORCEINLINE UItemObjectData*					GetItemObjectData() const					{ return mItemObjectData; }
	FORCEINLINE FVector2D								GetSize() const									{ return mSize; }
	FORCEINLINE TArray<UTexture2D*>			GetFrameTextureArr() const				{ return mFrameTextureArr; }

public:
	void SetIsEnter(const bool IsEnter)																	{ mIsEnter = IsEnter; }
	void SetTileSize(const float TileSize)																{ mTileSize = TileSize; }
	void SetItemObjectData(UItemObjectData* ItemObjectData)							{ mItemObjectData = ItemObjectData; }
	void SetSize(const FVector2D Size)																	{ mSize = Size; }
	void SetFrameTextureArr(TArray<UTexture2D*> FrameTextureArr)			{ mFrameTextureArr = FrameTextureArr; }

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	bool mIsEnter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	float mTileSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	UItemObjectData* mItemObjectData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	FVector2D mSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	TArray<UTexture2D*> mFrameTextureArr;
};
