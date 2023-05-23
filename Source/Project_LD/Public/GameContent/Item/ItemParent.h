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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UItemObjectData* ItemObjectData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	virtual void PickUpItem() override;
};
