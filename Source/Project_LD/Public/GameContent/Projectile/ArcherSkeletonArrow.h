// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LineProjectile.h"
#include "ArcherSkeletonArrow.generated.h"

class USphereComponent;
class UNiagaraComponent;

UCLASS()
class PROJECT_LD_API AArcherSkeletonArrow : public ALineProjectile
{
	GENERATED_BODY()
	
public:	
	AArcherSkeletonArrow();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* mArrowTail;

};
