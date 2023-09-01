// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/Skill/Lich/LichSkillBase.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ILichSkillBase::ILichSkillBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	//mSpawnedParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));


	//static ConstructorHelpers::FObjectFinder<UParticleSystem> MAINPARTICLE(TEXT("ParticleSystem'/Game/RPGEffects/Particles/P_Priest_Sphere.P_Priest_Sphere'"));
	//if (MAINPARTICLE.Succeeded())
	//{
	//	mSpawnedParticle->SetTemplate(MAINPARTICLE.Object);
	//}
}