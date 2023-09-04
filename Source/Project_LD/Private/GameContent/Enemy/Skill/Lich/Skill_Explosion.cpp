// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_Explosion.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystem.h"

// Sets default values
ASkill_Explosion::ASkill_Explosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_Explosion::ActiveSkill(FVector InLocation, FRotator InRotation)
{
	if (UParticleSystem* Particle = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/GameContent/Animation/Enemy/Lich/Particle/P_Lich_Explosion.P_Lich_Explosion'")))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, InLocation, InRotation,FVector(1.f));
	}
}

void ASkill_Explosion::ReactionSkill()
{
}

void ASkill_Explosion::DeactiveSkill()
{
}

// Called when the game starts or when spawned
void ASkill_Explosion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_Explosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

