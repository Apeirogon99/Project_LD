// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkCharacter.h"
#include <Network/NetworkUtils.h>
#include <Framework/Gameinstance/LDGameInstance.h>
#include <Struct/Game/GameDatas.h>
#include <Struct/Game/CharacterDatas.h>

// Sets default values
ANetworkCharacter::ANetworkCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ANetworkCharacter::~ANetworkCharacter()
{
}

// Called when the game starts or when spawned
void ANetworkCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANetworkCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANetworkCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}