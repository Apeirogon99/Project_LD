// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/DarkKnight/DarkKnight_Extermination.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ADarkKnight_Extermination::ADarkKnight_Extermination()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> EXTERMINATION(TEXT("NiagaraSystem'/Game/BigNiagaraBundle/NiagaraEffectMix2/Effects/NS_ShockWave.NS_ShockWave'"));
	if (EXTERMINATION.Succeeded())
	{
		mSpawnParticle = EXTERMINATION.Object;
	}
}

void ADarkKnight_Extermination::ActiveSkill(FVector InLocation, FRotator InRotation)
{
	if (mSpawnParticle)
	{
		mSpawnParticleStore = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), mSpawnParticle, InLocation, FRotator(0), FVector(1), false);
	}
}

void ADarkKnight_Extermination::ReactionSkill(FVector InLocation, FRotator InRotation)
{
	if (mSpawnParticleStore)
	{
		mSpawnParticleStore->SetFloatParameter("CustomScale", InRotation.Roll);
	}
}

void ADarkKnight_Extermination::DeactiveSkill(FVector InLocation, FRotator InRotation)
{
}

// Called when the game starts or when spawned
void ADarkKnight_Extermination::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADarkKnight_Extermination::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (mSpawnParticle)
	{
		mSpawnParticle = nullptr;
	}
	if (mSpawnParticleStore)
	{
		mSpawnParticleStore->Deactivate();
		mSpawnParticleStore = nullptr;
	}

}

// Called every frame
void ADarkKnight_Extermination::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

