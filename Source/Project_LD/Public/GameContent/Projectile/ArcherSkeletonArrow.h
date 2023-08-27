// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArcherSkeletonArrow.generated.h"

class USphereComponent;
class UNiagaraComponent;

UCLASS()
class PROJECT_LD_API AArcherSkeletonArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArcherSkeletonArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void ArrowSyncMovement(const FVector& inLocation, const FRotator& inRotation, const float& inDuration);
	void ArrowMovementCorrection(const float inDeltaTime);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* mSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* mProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* mArrowTail;

	bool	mIsLocationCorrection;
	FVector mTargetLoction;

	float	mCorrectionVelocity;
};
