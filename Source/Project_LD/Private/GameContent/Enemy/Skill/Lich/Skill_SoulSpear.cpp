// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_SoulSpear.h"
#include <Network/NetworkUtils.h>
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include <Niagara/Classes/NiagaraSystem.h>
#include <NiagaraComponent.h>

ASkill_SoulSpear::ASkill_SoulSpear()
{
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

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

	mTail = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Tail"));

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_ArrowTail(TEXT("NiagaraSystem'/Game/GameContent/Animation/Enemy/Skeleton/Effect/NS_ArrowTail.NS_ArrowTail'"));
	if (NS_ArrowTail.Succeeded())
	{
		mTail->SetAsset(NS_ArrowTail.Object);
	}
	mTail->SetupAttachment(mMesh);
	mTail->SetRelativeLocation(FVector(0.f, -40.f, 0.f));
	mTail->SetRelativeRotation(FRotator(0.f, 0.f, 270.f));
}

void ASkill_SoulSpear::BeginPlay()
{
	Super::BeginPlay();
}

void ASkill_SoulSpear::Tick(float DeltaTime)
{
	Super::BeginPlay();
}

void ASkill_SoulSpear::ActiveSkill()
{
}

void ASkill_SoulSpear::DeactiveSkill()
{
}

void ASkill_SoulSpear::OnReady()
{
}

void ASkill_SoulSpear::OnStart()
{
}
