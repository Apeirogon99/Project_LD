// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Projectile/ArcherSkeletonArrow.h"
#include "Components/SphereComponent.h"

// Sets default values
AArcherSkeletonArrow::AArcherSkeletonArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereRoot"));
	mSphere->InitSphereRadius(20.f);

	RootComponent = mSphere;

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Arrow(TEXT("StaticMesh'/Game/UndeadPack/SkeletonEnemy/Mesh/Weapon/Bow/Arrow/SM_Arrow.SM_Arrow'"));
	if (SM_Arrow.Succeeded())
	{
		mMesh->SetStaticMesh(SM_Arrow.Object);
	}

	mMesh->SetupAttachment(RootComponent);
	mMesh->SetRelativeScale3D(FVector(2.f, 1.f, 2.f));
}

// Called when the game starts or when spawned
void AArcherSkeletonArrow::BeginPlay()
{
	Super::BeginPlay();
	
}