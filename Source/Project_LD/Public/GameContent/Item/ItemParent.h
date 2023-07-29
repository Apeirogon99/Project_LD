// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Gameinstance/LDGameInstance.h"
#include "Struct/Game/GameDatas.h"
#include "Framework/Interface/InteractiveInterface.h"
#include "ItemParent.generated.h"

class USceneComponent;
class USkeletalMeshComponent;
class USphereComponent;
class UParticleSystem;
class UParticleSystemComponent;
class UWidgetComponent;
class AC_Game;

UCLASS()
class PROJECT_LD_API AItemParent : public AActor, public IInteractiveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemParent();

public:
	virtual void Interactive(ANC_Game* inPlayer) override;
	void Init(int32 Code, int32 GameObjectId);
	void FindPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Destroyed() override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USceneComponent* mSceneComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USkeletalMeshComponent* mSkeletalMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USphereComponent* mSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	UItemObjectData* mItemObjectData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Image", meta = (AllowPrivateAccess = "true"))
	UTexture2D* mIcon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* mItemSpawnParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UParticleSystem*> mPickUpParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* mItemGainParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> mItemNameClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* mItemSpawnParticleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* mItemNameWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AC_Game* mPlayer;

	UDataTable* mDataTable;

private:
	void ItemObjectDataInit(int32 Categoryid);
};
