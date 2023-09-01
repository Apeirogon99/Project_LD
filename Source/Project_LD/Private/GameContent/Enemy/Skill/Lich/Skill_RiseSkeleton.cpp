// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Enemy/Skill/Lich/Skill_RiseSkeleton.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ASkill_RiseSkeleton::ASkill_RiseSkeleton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_RiseSkeleton::ActiveSkill()
{
	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/Test/NS_SpawnSkeleton.NS_SpawnSkeleton'")))
	{
		FVector Location = GetActorLocation();
		Location.Z = Location.Z - 120.f;
		FRotator Rotation = RootComponent->GetRelativeRotation();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, Location, Rotation);
	}
}

void ASkill_RiseSkeleton::DeactiveSkill()
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

