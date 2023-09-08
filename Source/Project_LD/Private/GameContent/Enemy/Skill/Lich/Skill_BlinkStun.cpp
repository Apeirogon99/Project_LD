// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_BlinkStun.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystem.h"

// Sets default values
ASkill_BlinkStun::ASkill_BlinkStun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_BlinkStun::ActiveSkill(FVector InLocation, FRotator InRotation)
{
	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/GameContent/Animation/Enemy/Lich/Particle/NS_Lich_Blink.NS_Lich_Blink'")))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, InLocation, InRotation);
	}
}

void ASkill_BlinkStun::ReactionSkill(FVector InLocation, FRotator InRotation)
{
	if (UParticleSystem* Particle = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/GameContent/Animation/Enemy/Lich/Particle/P_Lich_Blink.P_Lich_Blink'")))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, InLocation, InRotation, FVector(1.f));
	}
}

void ASkill_BlinkStun::DeactiveSkill(FVector InLocation, FRotator InRotation)
{
}

// Called when the game starts or when spawned
void ASkill_BlinkStun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_BlinkStun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

