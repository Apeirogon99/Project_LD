// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Enemy/Skill/Lich/Skill_RiseSkeleton.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ASkill_RiseSkeleton::ASkill_RiseSkeleton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improvse performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_RiseSkeleton::ActiveSkill(FVector InLocation, FRotator InRotation)
{	
	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/GameContent/Animation/Enemy/Lich/Particle/NS_Lich_SpawnSkeleton.NS_Lich_SpawnSkeleton'")))
	{
		FVector Location = InLocation;
		Location.Z = Location.Z - 120.f;
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, Location, InRotation);
	}
}

void ASkill_RiseSkeleton::ReactionSkill(FVector InLocation, FRotator InRotation)
{
}

void ASkill_RiseSkeleton::DeactiveSkill(FVector InLocation, FRotator InRotation)
{
}

// Called when the game starts or when spawned
void ASkill_RiseSkeleton::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASkill_RiseSkeleton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

