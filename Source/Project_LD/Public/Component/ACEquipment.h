// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>
#include "ACEquipment.generated.h"

class UUWInventory;
class UW_ItemSpace;
class UItemObjectData;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_LD_API UACEquipment : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACEquipment();

public:
	void Init(UUWInventory* inventory);
	void	ClearEquipment();
	void LoadEquipment(const google::protobuf::RepeatedPtrField<Protocol::SItem>& inEqipments);
	void ChangedItemSpace(int32 PartID, UItemObjectData* ItemData);
	void CanItemDropWidgetCheck(UItemObjectData* ItemObjectData);
	void DropItemWidget();

public:
	FORCEINLINE TArray<UW_ItemSpace*>			GetEquipmentWidget() const					{ return mEquipmentWidget; }
	FORCEINLINE TArray<UItemObjectData*>		GetEquipmentObjectData() const			{ return mEquipmentData; }

public:
	void SetEquipmentWidget(TArray<UW_ItemSpace*> EquipmentWidget)		{ mEquipmentWidget = EquipmentWidget; }
	void SetEquipmentData(TArray<UItemObjectData*> EquipmentData)			{ mEquipmentData = EquipmentData; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	TArray<UW_ItemSpace*> mEquipmentWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	TArray<UItemObjectData*> mEquipmentData;
};
