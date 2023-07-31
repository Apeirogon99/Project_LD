// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Projectile/ArcherSkeletonArrow.h"
#include <Network/NetworkUtils.h>
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AArcherSkeletonArrow::AArcherSkeletonArrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mIsLocationCorrection = false;

	mSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereRoot"));
	mSphere->InitSphereRadius(20.f);

	mProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("mProjectileMovementComponent"));
	mProjectileMovementComponent->SetUpdatedComponent(mSphere);
	mProjectileMovementComponent->InitialSpeed = 1000.0f;
	mProjectileMovementComponent->MaxSpeed = 1000.0f;
	mProjectileMovementComponent->bRotationFollowsVelocity = false;
	mProjectileMovementComponent->bShouldBounce = false;
	mProjectileMovementComponent->ProjectileGravityScale = 0.0f;

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

void AArcherSkeletonArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ArrowMovementCorrection(DeltaTime);
}

void AArcherSkeletonArrow::ArrowSyncMovement(const FVector& inLocation, const float& inDuration)
{
	FVector curLocation = this->GetActorLocation();
	float locationDistance = FVector::Dist2D(curLocation, inLocation);
	if (locationDistance >= 1.0f)
	{
		mIsLocationCorrection = true;
		mTargetLoction = inLocation;
	}

	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("cur[%ws], new[%ws] distance[%f]"), *curLocation.ToString(), *inLocation.ToString(), locationDistance), ELogLevel::Error);
}

void AArcherSkeletonArrow::ArrowMovementCorrection(const float inDeltaTime)
{

	if (false == mIsLocationCorrection)
	{
		return;
	}

	FVector curLocation = this->GetActorLocation();
	float	velocity = 10.0f;

	FVector correctionLocation = FMath::VInterpTo(curLocation, mTargetLoction, inDeltaTime, velocity);

	float distance = FVector::Dist2D(curLocation, correctionLocation);
	if (distance <= 1.0f)
	{
		this->SetActorLocation(mTargetLoction, false, nullptr, ETeleportType::None);
		mIsLocationCorrection = false;
	}
	else
	{
		this->SetActorLocation(correctionLocation, false, nullptr, ETeleportType::None);
	}

	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("cur[%ws], cor[%ws], distance[%f]"), *curLocation.ToString(), *correctionLocation.ToString(), distance), ELogLevel::Error);
}
