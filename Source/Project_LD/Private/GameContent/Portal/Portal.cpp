// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Portal/Portal.h"
#include <Niagara/Public/NiagaraFunctionLibrary.h>
#include <Niagara/Classes/NiagaraSystem.h>

#include "Components/SphereComponent.h"
#include <NiagaraComponent.h>

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = false;

	mSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereRoot"));
	mSphere->InitSphereRadius(20.f);

	RootComponent = mSphere;

	mSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &APortal::OnOverlapBegin);

	mNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("mNiagaraComponent"));
	mNiagaraComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_Portal(TEXT("NiagaraSystem'/Game/RPGEffects/ParticlesNiagara/StatusEffects/TeleportPortal/NS_Status_Teleport_Portal.NS_Status_Teleport_Portal'"));
	if (NS_Portal.Succeeded())
	{
		mPortal = NS_Portal.Object;
		mNiagaraComponent->SetAsset(NS_Portal.Object);
		mNiagaraComponent->Activate();
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_Burst(TEXT("NiagaraSystem'/Game/RPGEffects/ParticlesNiagara/StatusEffects/TeleportBurst/NS_Status_Teleport_Burst.NS_Status_Teleport_Burst'"));
	if (NS_Burst.Succeeded())
	{
		mBurst = NS_Burst.Object;
	}
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(world, mBurst, SweepResult.ImpactPoint, this->GetActorRotation());
	}
}

