// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LineProjectile.h"
#include "SourSpear.generated.h"

class USphereComponent;
class UNiagaraComponent;

UCLASS()
class PROJECT_LD_API ASourSpear : public ALineProjectile
{
	GENERATED_BODY()
	
public:	
	ASourSpear();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
};
