// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstructionBase.generated.h"

class UBoxComponent;

UCLASS()
class PROJECT_LD_API AObstructionBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstructionBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void SetObstructioType(int32 inType);

	UFUNCTION()
	void SetBlockingExtent(FVector inExtent);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* mBlocking;
};
