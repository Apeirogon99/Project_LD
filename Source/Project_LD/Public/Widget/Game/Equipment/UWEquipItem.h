// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct/Game/GameDatas.h"
#include "UWEquipItem.generated.h"

/**
 * 
 */
class UBorder;
class UImage;
class USizeBox;

DECLARE_DELEGATE(FOnEquipItemRemoved);

UCLASS()
class PROJECT_LD_API UUWEquipItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FOnEquipItemRemoved OnEquipItemRemoved;

public:
	void SetImage();
	void SetFrameSize(float X, float Y);
	void Init();

public:
	FORCEINLINE bool									GetIsEnter() const								{ return bIsEnter; }
	FORCEINLINE bool									GetIsFirst() const								{ return bIsFirst; }
	FORCEINLINE UItemObjectData*				GetItemObjectData() const					{ return mItemObjectData; }
	FORCEINLINE TArray<UTexture2D*>		GetFrameTextureArr() const				{ return mFrameTextureArr; }

public:
	void SetIsEnter(bool Enter)																			{ bIsEnter = Enter; }
	void SetIsFirst(bool First)																				{ bIsFirst = First; }
	void SetItemObjectData(UItemObjectData* ItemObjectData)						{ mItemObjectData = ItemObjectData; }
	void SetFrameTextureArr(TArray<UTexture2D*> FrameTextureArr)		{ mFrameTextureArr = FrameTextureArr; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* BackgroundBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USizeBox* BackgroundSizeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemBackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	UItemObjectData* mItemObjectData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	TArray<UTexture2D*> mFrameTextureArr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	bool bIsEnter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	bool bIsFirst = true;
};
