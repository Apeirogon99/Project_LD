// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWInvenFrame.generated.h"

/**
 * 
 */
class UACInventoryComponent;

UCLASS()
class PROJECT_LD_API UUWInvenFrame : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UACInventoryComponent* mInvenComponent;

public:
	void Init(UACInventoryComponent* InvenComponent);
};
