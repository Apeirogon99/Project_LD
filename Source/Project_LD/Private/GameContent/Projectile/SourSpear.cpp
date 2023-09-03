// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Projectile/SourSpear.h"
#include <Network/NetworkUtils.h>
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include <Niagara/Classes/NiagaraSystem.h>
#include <NiagaraComponent.h>


// Sets default values
ASourSpear::ASourSpear()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Arrow(TEXT("StaticMesh'/Game/UndeadPack/SkeletonEnemy/Mesh/Weapon/Bow/Arrow/SM_Arrow.SM_Arrow'"));
	if (SM_Arrow.Succeeded())
	{
		mMesh->SetStaticMesh(SM_Arrow.Object);
	}

	mMesh->SetupAttachment(RootComponent);
	mMesh->SetRelativeRotation(FRotator(270.f, 0.f, 270.f));
	mMesh->SetRelativeLocation(FVector(-40.f, 0.f, 0.f));
	mMesh->SetRelativeScale3D(FVector(2.f, 1.f, 2.f));
	mMesh->SetCollisionProfileName(FName(TEXT("NoCollision")));

	mArrowTail = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ArrowTail"));

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_ArrowTail(TEXT("NiagaraSystem'/Game/GameContent/Animation/Enemy/Skeleton/Effect/NS_ArrowTail.NS_ArrowTail'"));
	if (NS_ArrowTail.Succeeded())
	{
		mArrowTail->SetAsset(NS_ArrowTail.Object);
	}
	mArrowTail->SetupAttachment(mMesh);
	mArrowTail->SetRelativeLocation(FVector(0.f, -40.f, 0.f));
	mArrowTail->SetRelativeRotation(FRotator(0.f, 0.f, 270.f));
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

void ASourSpear::OnReady()
{
}

void ASourSpear::OnStart()
{
}

