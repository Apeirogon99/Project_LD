// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Debug_Box.generated.h"

UCLASS()
class PROJECT_LD_API ADebug_Box : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADebug_Box();

public:
	UFUNCTION(BlueprintNativeEvent)
	void DebugInit(FVector StartVector, FVector EndVector, FVector BoxVector);
	virtual void DebugInit_Implementation(FVector StartVector, FVector EndVector, FVector BoxVector);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
