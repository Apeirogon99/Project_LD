// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Skill/Skill_SlamAttack.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"

// Sets default values
ASkill_SlamAttack::ASkill_SlamAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> MAINPARTICLE(TEXT("ParticleSystem'/Game/GameContent/Animation/Male/Skill/SlamAttack/P_SlamAttack.P_SlamAttack'"));
	if (MAINPARTICLE.Succeeded())
	{
		mMainParticle = MAINPARTICLE.Object;
	}
}

void ASkill_SlamAttack::AppearSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration)
{
	Super::AppearSkill(InRemoteID, InObjectID, InSkillID, InLocation, InRotation, InDuration);

	if (mMainParticle)
	{
		FVector Location = InLocation;
		Location.Z = Location.Z - 80.f;
		mSpawnedParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mMainParticle, FTransform(InRotation, Location, FVector(1)), true);
	}
}

void ASkill_SlamAttack::ReactionSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration)
{
	Super::ReactionSkill(InRemoteID, InObjectID, InSkillID, InLocation, InRotation, InDuration);
}

// Called when the game starts or when spawned
void ASkill_SlamAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkill_SlamAttack::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (mSpawnedParticle)
	{
		mSpawnedParticle->DestroyComponent();
	}
}

// Called every frame
void ASkill_SlamAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

