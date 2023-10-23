// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Framework/Interface/InteractiveInterface.h"
#include "StartPack.generated.h"

class USphereComponent;

UCLASS()
class PROJECT_LD_API AStartPack : public AActor, public IInteractiveInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStartPack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interactive(ANC_Game* inPlayer) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StartPack", meta = (AllowPrivateAccess = "true"))
	USceneComponent* mSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StartPack", meta = (AllowPrivateAccess = "true"))
	USphereComponent* mSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StartPack", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mStaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "StartPack", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* mParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "StartPack", meta = (AllowPrivateAccess = "true"))
	bool mIsOverlap;
};
