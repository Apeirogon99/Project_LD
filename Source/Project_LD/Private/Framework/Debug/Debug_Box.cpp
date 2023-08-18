// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Debug/Debug_Box.h"

// Sets default values
ADebug_Box::ADebug_Box()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADebug_Box::DebugInit_Implementation(FVector StartVector, FVector EndVector, FVector BoxVector, float duration)
{
	UE_LOG(LogTemp, Warning, TEXT("ADebug_Box::Init_Implementation"));
}

// Called when the game starts or when spawned
void ADebug_Box::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADebug_Box::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADebug_Box::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

