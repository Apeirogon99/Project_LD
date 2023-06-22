// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Gameinstance/LDGameInstance.h"
#include "Struct/Game/GameDatas.h"
#include "Framework/Interface/InventoryInterface.h"
#include "ItemParent.generated.h"

class USceneComponent;
class USkeletalMeshComponent;
class USphereComponent;
class UParticleSystem;
class UParticleSystemComponent;
class UWidgetComponent;
class AC_Game;

UCLASS()
class PROJECT_LD_API AItemParent : public AActor, public IInventoryInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemParent();

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USceneComponent* mSceneComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USkeletalMeshComponent* mSkeletalMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USphereComponent* mSphere;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	UItemObjectData* mItemObjectData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Image")
	UTexture2D* mIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystem* mItemSpawnParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UParticleSystem*> mPickUpParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystem* mItemGainParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> mItemNameClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UParticleSystemComponent* mItemSpawnParticleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetComponent* mItemNameWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AC_Game* mPlayer;

private:
	UDataTable* mDataTable;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Destroyed() override;

public:
	virtual void PickUpItem(AC_Game* inPlayer) override;
	void Init(int32 Code, int32 GameObjectId);
	void FindPlayer();

private:
	void ItemObjectDataInit(int32 Categoryid);
};
