// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Struct/Game/GameDatas.h>
#include <Engine/Classes/Components/SphereComponent.h>
#include <Component/ACInventoryComponent.h>
#include <Framework/Interface/InventoryInterface.h>
#include <Framework/Character/GameCharacter.h>
#include "ItemParent.generated.h"

UCLASS()
class PROJECT_LD_API AItemParent : public AActor, public IInventoryInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemParent();
	AItemParent(int32 id);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")

	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UItemObjectData* ItemObjectData;

private:
	class UDataTable* DataTable;

	int32 ItemId;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual void PickUpItem() override;

private:
	void ItemObjectDataInit();
};
