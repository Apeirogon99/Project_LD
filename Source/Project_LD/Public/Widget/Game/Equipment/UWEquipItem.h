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

DECLARE_DELEGATE(FOnEquipItemRemoved);

UCLASS()
class PROJECT_LD_API UUWEquipItem : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* BackgroundBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemBackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	UItemObjectData* mItemObjectData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool mIsEnter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TArray<UTexture2D*> mFrameTextureArr;

public:
	bool bIsFirst = true;

	FOnEquipItemRemoved OnEquipItemRemoved;

public:
	void SetImage();

	void Init();
};
