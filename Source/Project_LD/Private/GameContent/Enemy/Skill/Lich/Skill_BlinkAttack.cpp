// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/Skill_BlinkAttack.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystem.h"
#include <GS_Game.h>
#include <GameContent/Enemy/E_Lich.h>

// Sets default values
ASkill_BlinkAttack::ASkill_BlinkAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkill_BlinkAttack::ActiveSkill(FVector InLocation, FRotator InRotation)
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

	FTimerHandle ActiveParticleTimer;

	mLocation = InLocation;
	mRotator = InRotation;
	lich->OnDisappear();

	GetWorldTimerManager().SetTimer(ActiveParticleTimer, this, &ASkill_BlinkAttack::ActiveParticle, 0.5f, false);
}

void ASkill_BlinkAttack::ReactionSkill(FVector InLocation, FRotator InRotation)
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

	lich->OnAppear();

	if (UParticleSystem* Particle = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/GameContent/Animation/Enemy/Lich/Particle/P_Lich_Blink.P_Lich_Blink'")))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, InLocation, InRotation, FVector(1.f));
	}
}

void ASkill_BlinkAttack::DeactiveSkill(FVector InLocation, FRotator InRotation)
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

void ASkill_BlinkAttack::ActiveParticle()
{
	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/GameContent/Animation/Enemy/Lich/Particle/NS_Lich_Blink.NS_Lich_Blink'")))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, mLocation, mRotator);
	}
}

