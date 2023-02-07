// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Identity/C_Dummy.h"

// Sets default values
AC_Dummy::AC_Dummy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_Dummy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Dummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_Dummy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

