// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Struct/Game/GameDatas.h>
#include <Engine/EngineTypes.h>
#include <Engine/Classes/Components/SphereComponent.h>
#include "GameFramework/Actor.h"
#include "ItemParent.generated.h"

UCLASS()
class PROJECT_LD_API AItemParent : public AActor
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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintSetter = SetItemObjectData, BlueprintGetter = GetItemObjectData, Category = "Component", meta = (AllowPrivateAccess = "true"))
	FItemData ItemObjectData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintSetter)
	void SetItemObjectData(FItemData Data) { ItemObjectData = Data; }

	UFUNCTION(BlueprintGetter)
	FItemData GetItemObjectData() { return ItemObjectData; }
};
