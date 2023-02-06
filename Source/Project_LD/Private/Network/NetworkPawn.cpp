// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkPawn.h"

// Sets default values
ANetworkPawn::ANetworkPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANetworkPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANetworkPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANetworkPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

