// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameContent/Enemy/EnemyBase.h"
#include "E_NomalSkeleton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AE_NomalSkeleton : public AEnemyBase
{
	GENERATED_BODY()
		
public:
	AE_NomalSkeleton();
	~AE_NomalSkeleton();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Interactive(AC_Game* inPlayer) override;
};
