// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Projectile/AttackTestUnit.h"
#include <Network/NetworkUtils.h>
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Materials/MaterialInstanceDynamic.h>
#include <Components/StaticMeshComponent.h>
#include <Materials/MaterialInterface.h>

AAttackTestUnit::AAttackTestUnit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_CUBE(TEXT("StaticMesh'/Game/Blueprint/TestCube/TestCube.TestCube'"));
	if (SM_CUBE.Succeeded())
	{
		mMesh->SetStaticMesh(SM_CUBE.Object);
	}

	mMesh->SetupAttachment(RootComponent);
	mMesh->SetCollisionProfileName(FName(TEXT("NoCollision")));
}

// Called when the game starts or when spawned
void AAttackTestUnit::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	auto Cube = FindComponentByClass<UStaticMeshComponent>();
	auto Material = Cube->GetMaterial(0);

	mOverlapMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	Cube->SetMaterial(0, mOverlapMaterial);
	mOverlapMaterial->SetVectorParameterValue(TEXT("BaseColor"), FColor::Red);

	this->ActiveProjectile();
}

void AAttackTestUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAttackTestUnit::BeginOverlapUnit()
{
	mOverlapMaterial->SetVectorParameterValue(TEXT("BaseColor"), FColor::Green);
}

void AAttackTestUnit::EndOverlapUnit()
{
	mOverlapMaterial->SetVectorParameterValue(TEXT("BaseColor"), FColor::Red);
}

void AAttackTestUnit::ChangeMovement(const FVector& inLocation, const FRotator& inRotation)
{
	this->SetActorLocation(inLocation);
	this->SetActorRotation(inRotation);
}

void AAttackTestUnit::SetExtent(const FVector& inExtent)
{
	FVector newExtent = inExtent / 100.0f;
	mMesh->SetRelativeScale3D(newExtent);
}
