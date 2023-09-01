// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Projectile/LineProjectile.h"
#include <Network/NetworkUtils.h>
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ALineProjectile::ALineProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	mIsLocationCorrection = false;

	mSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereRoot"));
	mSphere->InitSphereRadius(20.f);

	RootComponent = mSphere;

	mProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("mProjectileMovementComponent"));
	mProjectileMovementComponent->SetUpdatedComponent(mSphere);
	mProjectileMovementComponent->InitialSpeed = 0.0f;
	mProjectileMovementComponent->MaxSpeed = 0.0f;
	mProjectileMovementComponent->bRotationFollowsVelocity = false;
	mProjectileMovementComponent->bRotationRemainsVertical = false;
	mProjectileMovementComponent->bShouldBounce = false;
	mProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	mCorrectionVelocity = 0.0f;
}

// Called when the game starts or when spawned
void ALineProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALineProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovementCorrection(DeltaTime);
}

void ALineProjectile::InitProjectile(float inSpeed, float inMaxspeed)
{
	mSpeed = inSpeed;
	mMaxSpeed = inMaxspeed;
}

void ALineProjectile::LineProjectileMovement(const FVector& inLocation, const FRotator& inRotation, const float& inDuration)
{
	FVector foward = inRotation.Quaternion().GetForwardVector();
	FVector velocity = foward * mProjectileMovementComponent->InitialSpeed;

	FVector deadReckoningLocation = inLocation + (velocity * inDuration);

	FVector curLocation = this->GetActorLocation();
	float locationDistance = FVector::Dist(curLocation, deadReckoningLocation);
	if (locationDistance > 1.0f)
	{
		mIsLocationCorrection = true;
		mTargetLoction = deadReckoningLocation;
		mCorrectionVelocity = 0.2f;
	}

	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("cur[%ws], new[%ws], dead[%ws], distance[%f], duration[%f]"), *curLocation.ToString(), *inLocation.ToString(), *deadReckoningLocation.ToString(), locationDistance, inDuration), ELogLevel::Error);
}

void ALineProjectile::MovementCorrection(const float inDeltaTime)
{
	if (false == mIsLocationCorrection)
	{
		return;
	}

	FVector curLocation = this->GetActorLocation();

	FVector correctionLocation = FMath::VInterpTo(curLocation, mTargetLoction, inDeltaTime, mCorrectionVelocity);

	float distance = FVector::Dist(curLocation, correctionLocation);
	if (distance <= 1.0f)
	{
		this->SetActorLocation(mTargetLoction, false, nullptr, ETeleportType::None);
		mIsLocationCorrection = false;
	}
	else
	{
		this->SetActorLocation(correctionLocation, false, nullptr, ETeleportType::None);
	}
}

void ALineProjectile::Ready()
{

	OnReady();
}

void ALineProjectile::Start()
{

	mProjectileMovementComponent->InitialSpeed	= mSpeed;
	mProjectileMovementComponent->MaxSpeed		= mMaxSpeed;

	OnStart();
}

