// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Debug/Debug_Circle.h"

// Sets default values
ADebug_Circle::ADebug_Circle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADebug_Circle::DebugInit_Implementation(float Radian, FVector StartVector, float duration)
{
}

// Called when the game starts or when spawned
void ADebug_Circle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADebug_Circle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

