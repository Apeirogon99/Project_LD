// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Debug_Circle.generated.h"

UCLASS()
class PROJECT_LD_API ADebug_Circle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADebug_Circle();

public:
	UFUNCTION(BlueprintNativeEvent)
	void DebugInit(float Radian, FVector StartVector, float duration);
	virtual void DebugInit_Implementation(float Radian, FVector StartVector, float duration);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
