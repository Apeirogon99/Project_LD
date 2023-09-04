// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_BlinkAttack.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystem.h"

// Sets default values
ASkill_BlinkAttack::ASkill_BlinkAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_BlinkAttack::ActiveSkill(FVector InLocation, FRotator InRotation)
{
	//if (UParticleSystem* Particle = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/GameContent/Animation/Enemy/Lich/Particle/P_Lich_Blink.P_Lich_Blink'")))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Location %f %f %f"), InLocation.X, InLocation.Y, InLocation.Z);
	//	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, InLocation, InRotation, FVector(1.f));
	//}
}

void ASkill_BlinkAttack::ReactionSkill(FVector InLocation, FRotator InRotation)
{
}

void ASkill_BlinkAttack::DeactiveSkill()
{
}

// Called when the game starts or when spawned
void ASkill_BlinkAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_BlinkAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

