// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Projectile/SourSpear.h"

// Sets default values
ASourSpear::ASourSpear()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASourSpear::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASourSpear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

