// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_SoulSpear.h"
#include <Network/NetworkUtils.h>
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include <Niagara/Public/NiagaraFunctionLibrary.h>
#include <Niagara/Classes/NiagaraSystem.h>
#include <NiagaraComponent.h>

ASkill_SoulSpear::ASkill_SoulSpear()
{
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SourSpear(TEXT("StaticMesh'/Game/sA_StylizedWizardSet/Models/SM_Projectile_Sphere.SM_Projectile_Sphere'"));
	if (SM_SourSpear.Succeeded())
	{
		mMesh->SetStaticMesh(SM_SourSpear.Object);
	}
	mMesh->SetupAttachment(RootComponent);
	mMesh->SetCollisionProfileName(FName(TEXT("NoCollision")));
	mMesh->SetHiddenInGame(true);

	mNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("mNiagaraComponent"));
	mNiagaraComponent->SetupAttachment(RootComponent);

	mSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASkill_SoulSpear::OnOverlapBegin);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_SoulSpearAttack(TEXT("NiagaraSystem'/Game/GameContent/Particle/Lich/SoulSpear/NS_SoulSpearAttack.NS_SoulSpearAttack'"));
	if (NS_SoulSpearAttack.Succeeded())
	{
		mAttack = NS_SoulSpearAttack.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_SoulSpearCastring(TEXT("NiagaraSystem'/Game/GameContent/Particle/Lich/SoulSpear/NS_SoulSpearCasting.NS_SoulSpearCasting'"));
	if (NS_SoulSpearCastring.Succeeded())
	{
		mCasting = NS_SoulSpearCastring.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_SoulSpearHit(TEXT("NiagaraSystem'/Game/GameContent/Particle/Lich/SoulSpear/NS_SoulSpearHit.NS_SoulSpearHit'"));
	if (NS_SoulSpearHit.Succeeded())
	{
		mHit = NS_SoulSpearHit.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_SoulSpearProjectile(TEXT("NiagaraSystem'/Game/GameContent/Particle/Lich/SoulSpear/NS_SoulSpearProjectile.NS_SoulSpearProjectile'"));
	if (NS_SoulSpearProjectile.Succeeded())
	{
		mProjectile = NS_SoulSpearProjectile.Object;
	}
}

void ASkill_SoulSpear::BeginPlay()
{
	Super::BeginPlay();
}

void ASkill_SoulSpear::ActiveSkill(FVector InLocation, FRotator InRotation)
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(world, mCasting, InLocation, InRotation);

	mNiagaraComponent->SetAsset(mProjectile);
	mNiagaraComponent->Activate();
}

void ASkill_SoulSpear::ReactionSkill(FVector Location, FRotator Rotation)
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(world, mAttack, Location, Rotation);

	FVector foward =  Rotation.Quaternion().GetForwardVector();
	this->InitProjectile(1000.0f, 1000.0f);

	FVector velocity = foward * this->mMaxSpeed;
	mProjectileMovementComponent->Velocity = velocity;

	this->ActiveProjectile();
}

void ASkill_SoulSpear::DeactiveSkill(FVector InLocation, FRotator InRotation)
{
}

void ASkill_SoulSpear::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(world, mHit, SweepResult.ImpactPoint, this->GetActorRotation());
	}
}
