// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UWInvenFrame.generated.h"

/**
 * 
 */
class UACInventoryComponent;
class UACEquipment;

UCLASS()
class PROJECT_LD_API UUWInvenFrame : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(UACInventoryComponent* InvenComponent, UACEquipment* EquipmentComponent);

public:
	FORCEINLINE UACInventoryComponent*	GetInventoryComponent() const					{ return mInvenComponent; }
	FORCEINLINE UACEquipment*					GetEquipmentComponent() const					{ return mEquipmentComponent; }

public:
	void		SetInventoryComponent(UACInventoryComponent* InventoryComponent)			{ mInvenComponent = InventoryComponent; }
	void		SetEquipmentComponent(UACEquipment* EquipmentComponent)							{ mEquipmentComponent = EquipmentComponent; }

protected:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UACInventoryComponent* mInvenComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	UACEquipment* mEquipmentComponent;
};
