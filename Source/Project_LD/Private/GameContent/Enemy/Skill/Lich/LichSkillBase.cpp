// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/LichSkillBase.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ALichSkillBase::ALichSkillBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSpawnedParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	mSpawnedParticle->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> MAINPARTICLE(TEXT("ParticleSystem'/Game/RPGEffects/Particles/P_Priest_Sphere.P_Priest_Sphere'"));
	if (MAINPARTICLE.Succeeded())
	{
		mSpawnedParticle->SetTemplate(MAINPARTICLE.Object);
	}
}

void ALichSkillBase::ActiveSkill()
{
}

void ALichSkillBase::DeactiveSkill()
{
}

// Called when the game starts or when spawned
void ALichSkillBase::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ALichSkillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

