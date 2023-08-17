// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Skill/Skill_SlamAttack.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"

// Sets default values
ASkill_SlamAttack::ASkill_SlamAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	mParticleFisrt = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FirstNiagaraComponent"));

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FIRST_PARTICLE(TEXT("NiagaraSystem'/Game/GameContent/Animation/Male/Skill/SlamAttack/NS_JumpAttack_First.NS_JumpAttack_First'"));
	if (FIRST_PARTICLE.Succeeded())
	{
		mParticleFisrt->SetAsset(FIRST_PARTICLE.Object);
	}

	mParticleFisrt->SetRelativeLocation(FVector(0.f, 0.f, 45.f));
}

// Called when the game starts or when spawned
void ASkill_SlamAttack::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle PreHeatTimerHandle;
	FTimerHandle SecondTimerHandle;

	GetWorldTimerManager().SetTimer(PreHeatTimerHandle, this, &ASkill_SlamAttack::CallPreHeatNiagara, 0.1f, false);
	GetWorldTimerManager().SetTimer(SecondTimerHandle, this, &ASkill_SlamAttack::CallSecondNiagara, 0.4f, false);
}

void ASkill_SlamAttack::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (mEarthActor != nullptr)
	{
		mEarthActor->Destroy();
	}
}

void ASkill_SlamAttack::CallSecondNiagara()
{
	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/GameContent/Animation/Male/Skill/SlamAttack/NS_JumpAttack_Second.NS_JumpAttack_Second'")))
	{
		FVector Location = GetActorLocation();
		Location.Z = Location.Z - 40.f;
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, Location);
	}
	UBlueprint* BlueprintObj = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, TEXT("Blueprint'/Game/GameContent/Animation/Male/Skill/SlamAttack/BP_JumpAttack_Earth.BP_JumpAttack_Earth'")));
	if (BlueprintObj)
	{
		UClass* EarthActorClass = BlueprintObj->GeneratedClass;

		UWorld* world = GetWorld();
		if (world == nullptr)
		{
			return;
		}
		FVector Location = GetActorLocation();
		Location.Z = Location.Z - 40.f;

		mEarthActor = world->SpawnActor<AActor>(EarthActorClass, Location, FRotator(0.f,90.f,0.f));
	}
}

void ASkill_SlamAttack::CallPreHeatNiagara()
{
	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/GameContent/Animation/Male/Skill/SlamAttack/NS_JumpAttack_Preheat.NS_JumpAttack_Preheat'")))
	{
		FVector Location = GetActorLocation();
		Location.Z = Location.Z - 40.f;
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, Location);
	}
}

// Called every frame
void ASkill_SlamAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

