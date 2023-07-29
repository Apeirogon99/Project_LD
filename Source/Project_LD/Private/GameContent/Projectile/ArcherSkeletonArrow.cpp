// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Projectile/ArcherSkeletonArrow.h"
#include "Components/SphereComponent.h"

// Sets default values
AArcherSkeletonArrow::AArcherSkeletonArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereRoot"));
	mSphere->InitSphereRadius(40.f);

	RootComponent = mSphere;
}

// Called when the game starts or when spawned
void AArcherSkeletonArrow::BeginPlay()
{
	Super::BeginPlay();
	
}