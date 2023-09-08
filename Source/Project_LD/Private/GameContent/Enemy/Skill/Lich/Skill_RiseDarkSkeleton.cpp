// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_RiseDarkSkeleton.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystem.h"

// Sets default values
ASkill_RiseDarkSkeleton::ASkill_RiseDarkSkeleton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_RiseDarkSkeleton::ActiveSkill(FVector InLocation, FRotator InRotation)
{
	if (UParticleSystem* Particle = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/GameContent/Animation/Enemy/Lich/Particle/P_Lich_RiseDarkSkeleton.P_Lich_RiseDarkSkeleton'")))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, InLocation, InRotation, FVector(1.f));
	}
}

void ASkill_RiseDarkSkeleton::ReactionSkill(FVector InLocation, FRotator InRotation)
{
}

void ASkill_RiseDarkSkeleton::DeactiveSkill(FVector InLocation, FRotator InRotation)
{
}

// Called when the game starts or when spawned
void ASkill_RiseDarkSkeleton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_RiseDarkSkeleton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

