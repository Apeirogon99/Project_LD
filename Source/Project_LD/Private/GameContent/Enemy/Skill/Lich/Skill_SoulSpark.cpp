// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_SoulSpark.h"
#include "NiagaraFunctionLibrary.h"
#include "Niagara/Classes/NiagaraSystem.h"

// Sets default values
ASkill_SoulSpark::ASkill_SoulSpark()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_SoulSpark::ActiveSkill(FVector InLocation, FRotator InRotation)
{
}

void ASkill_SoulSpark::ReactionSkill(FVector InLocation, FRotator InRotation)
{
	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/GameContent/Animation/Enemy/Lich/Particle/NS_SoulSpark.NS_SoulSpark'")))
	{
		FVector Loc = InLocation + InRotation.Quaternion().GetForwardVector() * 100.f;
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, Loc, InRotation, FVector(1), true);
	}
}

void ASkill_SoulSpark::DeactiveSkill(FVector InLocation, FRotator InRotation)
{
}

// Called when the game starts or when spawned
void ASkill_SoulSpark::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_SoulSpark::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

