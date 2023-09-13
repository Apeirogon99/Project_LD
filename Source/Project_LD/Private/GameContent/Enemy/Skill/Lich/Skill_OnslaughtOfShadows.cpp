// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_OnslaughtOfShadows.h"
#include "NiagaraFunctionLibrary.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include <Kismet/GameplayStatics.h>
#include <GS_Game.h>
#include <Enemy/E_Lich.h>
#include "Components/BoxComponent.h"

// Sets default values
ASkill_OnslaughtOfShadows::ASkill_OnslaughtOfShadows()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_OnslaughtOfShadows::ActiveSkill(FVector InLocation, FRotator InRotation)
{
	/*
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
			Location.Z = Location.Z - 199.0f;
			mActiveLine = world->SpawnActor<AActor>(bpClass, Location, InRotation, SpawnParameters);
		}
	}
	*/
	if (UParticleSystem* Particle = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/GameContent/Animation/Enemy/Lich/Particle/P_Lich_Dash.P_Lich_Dash'")))
	{
		FTimerHandle Active;
		AGS_Game* gameState = Cast<AGS_Game>(GetWorld()->GetGameState());
		if (nullptr == gameState)
		{
			return;
		}
		AActor* actor = gameState->FindGameObject(mRemoteID);
		if (actor == nullptr)
		{
			return;
		}
		AE_Lich* lich = Cast<AE_Lich>(actor);
		if (lich == nullptr)
		{
			return;
		}
		mSmokeParticle = UGameplayStatics::SpawnEmitterAttached(Particle, lich->GetMesh(), TEXT("None"), FVector(0.f,0.f,80.f), FRotator(0), EAttachLocation::SnapToTarget, false);

		GetWorldTimerManager().SetTimer(Active, this, &ASkill_OnslaughtOfShadows::ActiveCollider, 0.1f, false);
	}
}

void ASkill_OnslaughtOfShadows::ReactionSkill(FVector InLocation, FRotator InRotation)
{

}

void ASkill_OnslaughtOfShadows::DeactiveSkill(FVector InLocation, FRotator InRotation)
{
}

// Called when the game starts or when spawned
void ASkill_OnslaughtOfShadows::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkill_OnslaughtOfShadows::Destroyed()
{
	Super::Destroyed();

	AGS_Game* gameState = Cast<AGS_Game>(GetWorld()->GetGameState());
	if (nullptr == gameState)
	{
		return;
	}
	AActor* actor = gameState->FindGameObject(mRemoteID);
	if (actor == nullptr)
	{
		return;
	}
	AE_Lich* lich = Cast<AE_Lich>(actor);
	if (lich == nullptr)
	{
		return;
	}

	lich->PlayLichAnim(8);
	lich->GetLichCheckCollider()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DeleteActor();

	if (mSmokeParticle)
	{
		mSmokeParticle->DeactivateSystem();
		mSmokeParticle->DestroyComponent();
	}
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

void ASkill_OnslaughtOfShadows::ActiveCollider()
{
	AGS_Game* gameState = Cast<AGS_Game>(GetWorld()->GetGameState());
	if (nullptr == gameState)
	{
		return;
	}
	AActor* actor = gameState->FindGameObject(mRemoteID);
	if (actor == nullptr)
	{
		return;
	}
	AE_Lich* lich = Cast<AE_Lich>(actor);
	if (lich == nullptr)
	{
		return;
	}
	lich->GetLichCheckCollider()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

