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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent* mSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* mSkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USphereComponent* mSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UItemObjectData* mItemObjectData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
	UTexture2D* mIcon;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UParticleSystem* mItemSpawnParticle;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<UParticleSystem*> mPickUpParticle;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UParticleSystem* mItemGainParticle;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UUserWidget> mItemNameClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UParticleSystemComponent* mItemSpawnParticleComponent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UWidgetComponent* mItemNameWidgetComponent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
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
