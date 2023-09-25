// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/DarkKnight/DarkKnight_Berserk.h"
#include "NiagaraFunctionLibrary.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "Niagara/Public/NiagaraComponent.h"
#include <GS_Game.h>
#include <Enemy/E_DarkKnight.h>

// Sets default values
ADarkKnight_Berserk::ADarkKnight_Berserk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADarkKnight_Berserk::ActiveSkill(FVector InLocation, FRotator InRotation)
{
	UE_LOG(LogTemp, Warning, TEXT(" AE_DarkKnight::ActiveSkill() "));
	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/GameContent/Animation/Enemy/DarkKnight/Particle/NS_DarkKnight_Berserk.NS_DarkKnight_Berserk'")))
	{
		UE_LOG(LogTemp, Warning, TEXT(" AE_DarkKnight::ActiveSkill() Succ Load"));
		FTimerHandle AttachTimer;
		FVector Loc = InLocation;
		Loc.Z = Loc.Z - 50.f;
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, Loc, InRotation, FVector(1), true);

	}
}

void ADarkKnight_Berserk::ReactionSkill(FVector InLocation, FRotator InRotation)
{
}

void ADarkKnight_Berserk::DeactiveSkill(FVector InLocation, FRotator InRotation)
{
}

// Called when the game starts or when spawned
void ADarkKnight_Berserk::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADarkKnight_Berserk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADarkKnight_Berserk::AttachDarkKnight()
{
	AGS_Game* gameState = Cast<AGS_Game>(GetWorld()->GetGameState());
	if (nullptr == gameState)
	{
		return;
	}
	AActor* actor = gameState->FindGameObject(mRemoteID);
	if (nullptr == actor)
	{
		return;
	}
	AE_DarkKnight* darkKnight = Cast<AE_DarkKnight>(actor);
	if(nullptr == darkKnight)
	{
		return;
	}
	darkKnight->ActiveBerserk();
}