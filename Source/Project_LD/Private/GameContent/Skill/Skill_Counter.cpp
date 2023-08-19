// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Skill/Skill_Counter.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ASkill_Counter::ASkill_Counter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent		= CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	mParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("mFirstParticle"));

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> PARTICLE(TEXT("NiagaraSystem'/Game/GameContent/Animation/Male/Skill/Counter/NS_CounterStart.NS_CounterStart'"));
	if (PARTICLE.Succeeded())
	{
		mParticle->SetAsset(PARTICLE.Object);
	}

	mParticle->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASkill_Counter::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle NextCallTimer;

	GetWorldTimerManager().SetTimer(NextCallTimer, this, &ASkill_Counter::CallEndParticle, 0.14f, false);
}

void ASkill_Counter::CallEndParticle()
{
	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/GameContent/Animation/Male/Skill/Counter/NS_CounterShield.NS_CounterShield'")))
	{
		FVector Location = GetActorLocation() + GetActorForwardVector() * 150.f;
		FRotator Rotation = RootComponent->GetRelativeRotation();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, Location, Rotation);
	}
}

// Called every frame
void ASkill_Counter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

