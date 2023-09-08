// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_SoulShackles.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystem.h"

// Sets default values
ASkill_SoulShackles::ASkill_SoulShackles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_SoulShackles::ActiveSkill(FVector InLocation, FRotator InRotation)
{
	if (UParticleSystem* Particle = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/GameContent/Animation/Enemy/Lich/Particle/P_Lich_SoulShackles_Appear.P_Lich_SoulShackles_Appear'")))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, InLocation, InRotation, FVector(1.f));
	}
}

void ASkill_SoulShackles::ReactionSkill(FVector InLocation, FRotator InRotation)
{
	if (UParticleSystem* Particle = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/GameContent/Animation/Enemy/Lich/Particle/P_Lich_SoulShackles_Reaction.P_Lich_SoulShackles_Reaction'")))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, InLocation, InRotation, FVector(1.f));
	}
}

void ASkill_SoulShackles::DeactiveSkill(FVector InLocation, FRotator InRotation)
{
}

// Called when the game starts or when spawned
void ASkill_SoulShackles::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_SoulShackles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

