// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_OnslaughtOfShadows.h"
#include "NiagaraFunctionLibrary.h"
#include "Niagara/Classes/NiagaraSystem.h"

// Sets default values
ASkill_OnslaughtOfShadows::ASkill_OnslaughtOfShadows()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_OnslaughtOfShadows::ActiveSkill(FVector InLocation, FRotator InRotation)
{
	if (UBlueprint* bpActor = LoadObject<UBlueprint>(nullptr, TEXT("Blueprint'/Game/GameContent/Actor/EmitterLine/BP_Lich_shadows_Line.BP_Lich_shadows_Line'")))
	{
		UClass* bpClass = bpActor->GeneratedClass;

		FActorSpawnParameters SpawnParameters;

		SpawnParameters.Owner = this;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		UWorld* world = GetWorld();
		if (world)
		{
			FTimerHandle DestroyHandle;
			FVector Location = InLocation;
			Location.Z = Location.Z + 10.0f;
			mActiveLine = world->SpawnActor<AActor>(bpClass, Location, InRotation, SpawnParameters);

			GetWorldTimerManager().SetTimer(DestroyHandle, this, &ASkill_OnslaughtOfShadows::DeleteActor, 3.f, false);
		}
	}
}

void ASkill_OnslaughtOfShadows::ReactionSkill(FVector InLocation, FRotator InRotation)
{
	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/sA_Megapack_v1/sA_Rayvfx/Fx/NiagaraSystems/NS_Ray_3.NS_Ray_3'")))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, InLocation, InRotation, FVector(1.f));
	}
}

void ASkill_OnslaughtOfShadows::DeactiveSkill(FVector InLocation, FRotator InRotation)
{
}

// Called when the game starts or when spawned
void ASkill_OnslaughtOfShadows::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_OnslaughtOfShadows::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkill_OnslaughtOfShadows::DeleteActor()
{
	if (mActiveLine)
	{
		mActiveLine->Destroy();
	}
}

