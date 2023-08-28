// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Skill/Skill_Buff.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include <Components/SphereComponent.h>
#include <Framework/Game/NC_Game.h>
#include "UObject/ConstructorHelpers.h"

// Sets default values
ASkill_Buff::ASkill_Buff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mPlayerInCheckCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CheckCollision"));
	mPlayerInCheckCollision->SetupAttachment(RootComponent);
	mPlayerInCheckCollision->SetSphereRadius(430.f);
	mPlayerInCheckCollision->OnComponentBeginOverlap.AddDynamic(this, &ASkill_Buff::OnOverlapBegin);
	mPlayerInCheckCollision->OnComponentEndOverlap.AddDynamic(this, &ASkill_Buff::OnOverlapEnd);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> SUMMON_PARTICLE(TEXT("NiagaraSystem'/Game/GameContent/Animation/Male/Skill/Buff/NS_Buff_Summon.NS_Buff_Summon'"));
	if (SUMMON_PARTICLE.Succeeded())
	{
		mSummonParticle = SUMMON_PARTICLE.Object;
	}
}

void ASkill_Buff::AppearSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration)
{
	Super::AppearSkill(InRemoteID,InObjectID,InSkillID,InLocation,InRotation,InDuration);

	if (mSummonParticle)
	{
		FVector Location = InLocation;
		Location.Z = Location.Z - 80.f;
		mSpawnedParticle = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), mSummonParticle, Location, FRotator(), FVector(5), true);
	}
}

void ASkill_Buff::ReactionSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration)
{
	Super::ReactionSkill(InRemoteID, InObjectID, InSkillID, InLocation, InRotation, InDuration);
}

void ASkill_Buff::Appear()
{
	if (mSummonParticle)
	{
		FVector Location = GetActorLocation();
		Location.Z = Location.Z - 80.f;
		mSpawnedParticle = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), mSummonParticle, Location, FRotator(), FVector(5), true);
	}
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

void ASkill_Buff::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (mSpawnedParticle)
	{
		mSpawnedParticle->DestroyComponent();
	}

	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/GameContent/Animation/Male/Skill/Buff/NS_Buff_Disappear.NS_Buff_Disappear'")))
	{
		FVector Location = GetActorLocation();
		Location.Z = Location.Z - 90.f;
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, Location);
	}
}

void ASkill_Buff::CheckApplyPlayerBuff()
{

}

void ASkill_Buff::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ANC_Game>(OtherActor) != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player In"));
		Cast<ANC_Game>(OtherActor)->ActiveBuffParticle();
	}
}

void ASkill_Buff::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ANC_Game>(OtherActor) != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Out"));
		Cast<ANC_Game>(OtherActor)->DeActiveBuffParticle();
	}
}
