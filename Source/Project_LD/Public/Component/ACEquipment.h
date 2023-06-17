// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
		
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TArray<UW_ItemSpace*> mEquipmentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TArray<UItemObjectData*> mEquipmentData;

public:
	void Init(UUWInventory* inventory);

	void	ClearEquipment();
	void LoadEquipment(int64 ObjectID, int32 ItemCode, int32 PartCode);
	void ChangedItemSpace(int32 PartID, UItemObjectData* ItemData);
};
