// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <UMG/Public/Components/SizeBox.h>
#include <UMG/Public/Components/Border.h>
#include <UMG/Public/Components/Image.h>
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include <Struct/Game/GameDatas.h>
#include "UWItem.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRemoved, UItemObjectData*);

UCLASS(BlueprintType)
class PROJECT_LD_API UUWItem : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

	virtual void NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USizeBox* BackgroundSizeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* BackgroundBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	UItemObjectData* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FVector2D Size;

	FOnRemoved OnRemoved;

public:
	UFUNCTION(BlueprintCallable)
	void Refresh();

	UFUNCTION(BlueprintCallable)
	void Rotate();
};
