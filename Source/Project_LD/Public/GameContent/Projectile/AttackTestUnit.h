// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameContent/Projectile/LineProjectile.h"
#include "AttackTestUnit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AAttackTestUnit : public ALineProjectile
{
	GENERATED_BODY()
	
public:
	AAttackTestUnit();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void BeginOverlapUnit();
	void EndOverlapUnit();
	
	void ChangeMovement(const FVector& inLocation, const FRotator& inRotation);
	void SetExtent(const FVector& inExtent);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mMesh;

	UPROPERTY()
	UMaterialInstanceDynamic* mOverlapMaterial;
};
