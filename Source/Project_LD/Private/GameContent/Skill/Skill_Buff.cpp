// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Skill/Skill_Buff.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ASkill_Buff::ASkill_Buff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	mParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FIELDPARTICLE(TEXT("NiagaraSystem'/Game/GameContent/Animation/Male/Skill/Buff/NS_Buff_Summon.NS_Buff_Summon'"));
	if (FIELDPARTICLE.Succeeded())
	{
		mParticle->SetAsset(FIELDPARTICLE.Object);
	}

	mParticle->SetupAttachment(RootComponent);

	mParticle->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	mParticle->SetRelativeScale3D(FVector(5.f, 5.f, 5.f));
}

ASkill_Buff::~ASkill_Buff()
{
	//사라지는 파티클
}

// Called every frame
void ASkill_Buff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// protected //
// Called when the game starts or when spawned
void ASkill_Buff::BeginPlay()
{
	Super::BeginPlay();
	
}

