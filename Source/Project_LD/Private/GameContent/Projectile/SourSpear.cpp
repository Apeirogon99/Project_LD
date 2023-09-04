// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Projectile/SourSpear.h"
#include <Network/NetworkUtils.h>
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include <Niagara/Classes/NiagaraSystem.h>
#include <NiagaraComponent.h>


// Sets default values
ASourSpear::ASourSpear()
{

}

// Called when the game starts or when spawned
void ASourSpear::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASourSpear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}