// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Gameinstance/LDGameInstance.h"
#include "Struct/Game/GameDatas.h"
#include "Framework/Interface/InventoryInterface.h"
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
	class USceneComponent* mSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class USkeletalMeshComponent* mSkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class USphereComponent* mSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UItemObjectData* mItemObjectData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
	UTexture2D* mIcon;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UParticleSystem* mMouseCursorParticle;

private:
	UDataTable* mDataTable;
	int32 mItemCode;
	int32 mGameObjectId;

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void PickUpItem(AC_Game* inPlayer) override;
	virtual void ItemDestroy() { this->Destroy(); };
	void Init(int32 Code, int32 GameObjectId);

private:
	void ItemObjectDataInit();
};
