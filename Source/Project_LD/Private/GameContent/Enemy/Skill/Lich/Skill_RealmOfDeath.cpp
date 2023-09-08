// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_RealmOfDeath.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystem.h"

// Sets default values
ASkill_RealmOfDeath::ASkill_RealmOfDeath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_RealmOfDeath::ActiveSkill(FVector InLocation, FRotator InRotation)
{

}

void ASkill_RealmOfDeath::ReactionSkill(FVector InLocation, FRotator InRotation)
{
	if (UParticleSystem* Particle = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/VFX_AoE_ShockWave/Particles/P_AOE_10.P_AOE_10'")))
	{
		UE_LOG(LogTemp, Warning, TEXT("Location %f %f %f"), InLocation.X, InLocation.Y, InLocation.Z);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, InLocation, InRotation, FVector(1.f));
	}
}

void ASkill_RealmOfDeath::DeactiveSkill(FVector InLocation, FRotator InRotation)
{
}

// Called when the game starts or when spawned
void ASkill_RealmOfDeath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_RealmOfDeath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

