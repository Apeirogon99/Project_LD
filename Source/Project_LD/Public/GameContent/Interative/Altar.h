// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Framework/Interface/InteractiveInterface.h"
#include "Altar.generated.h"

class USphereComponent;

UCLASS()
class PROJECT_LD_API AAltar : public AActor, public IInteractiveInterface
{
	GENERATED_BODY()
	
public:	
	AAltar();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Interactive(ANC_Game* inPlayer) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Altar", meta = (AllowPrivateAccess = "true"))
		USceneComponent* mSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Altar", meta = (AllowPrivateAccess = "true"))
		USphereComponent* mSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Altar", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* mStaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Altar", meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* mParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Altar", meta = (AllowPrivateAccess = "true"))
		bool mIsOverlap;
};
