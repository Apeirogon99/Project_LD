// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Projectile/ArcherSkeletonArrow.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

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
	mMesh->SetRelativeRotation(FRotator(270.f, 0.f, 270.f));
	mMesh->SetRelativeScale3D(FVector(2.f, 1.f, 2.f));
	mMesh->SetCollisionProfileName(FName(TEXT("NoCollision")));

	mArrowTail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ArrowTail"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_ArrowTail(TEXT("ParticleSystem'/Game/GameContent/Projectile/Arrow/P_ArrowTail.P_ArrowTail'"));
	if (P_ArrowTail.Succeeded())
	{
		mArrowTail->SetTemplate(P_ArrowTail.Object);
	}

	mArrowTail->SetupAttachment(mMesh);
	mArrowTail->SetRelativeLocation(FVector(0.f, -40.f, 0.f));

}

// Called when the game starts or when spawned
void AArcherSkeletonArrow::BeginPlay()
{
	Super::BeginPlay();
	
}