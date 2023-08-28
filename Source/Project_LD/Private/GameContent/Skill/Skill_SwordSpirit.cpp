// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Skill/Skill_SwordSpirit.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ASkill_SwordSpirit::ASkill_SwordSpirit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> REACTION_PARTICLE(TEXT("NiagaraSystem'/Game/GameContent/Animation/Male/Skill/SwordSpirit/NS_SwordSpirit.NS_SwordSpirit'"));
	if (REACTION_PARTICLE.Succeeded())
	{
		mReactionParticle = REACTION_PARTICLE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> APPEAR1_PARTICLE(TEXT("NiagaraSystem'/Game/GameContent/Animation/Male/Skill/SwordSpirit/NS_Charge1.NS_Charge1'"));
	if (APPEAR1_PARTICLE.Succeeded())
	{
		mAppear1Particle = APPEAR1_PARTICLE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> APPEAR2_PARTICLE(TEXT("NiagaraSystem'/Game/GameContent/Animation/Male/Skill/SwordSpirit/NS_Charge2.NS_Charge2'"));
	if (APPEAR2_PARTICLE.Succeeded())
	{
		mAppear2Particle = APPEAR2_PARTICLE.Object;
	}

	mCurrentCharge = 0;
	mCountingScale = 0;
	bIsSpawn = false;
}

void ASkill_SwordSpirit::AppearSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration)
{
	Super::AppearSkill(InRemoteID, InObjectID, InSkillID, InLocation, InRotation, InDuration);
	
	if (mAppear1Particle && mAppear2Particle)
	{
		FTimerHandle SecondParticleTimer;
		FTimerHandle LastParticleTimer;

		mAppear1SpawnParticle = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), mAppear1Particle, InLocation, InRotation, FVector(1), true);
		GetWorldTimerManager().SetTimer(SecondParticleTimer, this, &ASkill_SwordSpirit::SpawnSecondParticle, 1.0, false);
		GetWorldTimerManager().SetTimer(LastParticleTimer, this, &ASkill_SwordSpirit::SpawnLastParticle, 2.0, false);
	}
}

void ASkill_SwordSpirit::ReactionSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration)
{
	Super::ReactionSkill(InRemoteID, InObjectID, InSkillID, InLocation, InRotation, InDuration);

	if (mReactionParticle)
	{
		mDuration = InDuration;
		if (mDuration == 0)
		{
			return;
		}

		if (mDuration >= 2.f)
		{
			mDuration = 2.f;
		}

		const float Min = 40.f;
		const float Max = 80.f;

		float InCreaseMin = 80.f;
		float InCreaseMax = 160.f;

		InCreaseMin *= mDuration / 2.0f;
		InCreaseMax *= mDuration / 2.0f;

		mReactionSpawnParticle = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), mReactionParticle, InLocation, InRotation, FVector(5), true);
		mReactionSpawnParticle->SetFloatParameter("BeamMin", Min + InCreaseMin);
		mReactionSpawnParticle->SetFloatParameter("BeamMax", Max + InCreaseMax);
		bIsSpawn = true;
	}
}

void ASkill_SwordSpirit::Reaction()
{
	if (mReactionParticle)
	{
		mDuration = aa;
		if (mDuration == 0)
		{
			return;
		}

		if (mDuration >= 2.f)
		{
			mDuration = 2.f;
		}

		const float Min = 40.f;
		const float Max = 80.f;

		float InCreaseMin = 80.f;
		float InCreaseMax = 160.f;

		InCreaseMin *= mDuration / 2.0f;
		InCreaseMax *= mDuration / 2.0f;

		mReactionSpawnParticle = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), mReactionParticle, GetActorLocation(), GetActorRotation(), FVector(5), true);
		mReactionSpawnParticle->SetFloatParameter("BeamMin", Min + InCreaseMin);
		mReactionSpawnParticle->SetFloatParameter("BeamMax", Max + InCreaseMax);
		bIsSpawn = true;
	}
}

// Called when the game starts or when spawned
void ASkill_SwordSpirit::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(ChargeTimer, this, &ASkill_SwordSpirit::ManagedChargeValue, 1.f, true);
}

void ASkill_SwordSpirit::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(ChargeTimer);
}

void ASkill_SwordSpirit::ManagedChargeValue()
{
	if (mCurrentCharge < 2)
	{
		mCurrentCharge++;
	}
}

void ASkill_SwordSpirit::SpawnSecondParticle()
{
	mAppear2SpawnParticle = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), mAppear2Particle, mLocation, mRotation, FVector(1), true);
	//색변경
}

void ASkill_SwordSpirit::SpawnLastParticle()
{
	//색변경
}

// Called every frame
void ASkill_SwordSpirit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsSpawn)
	{
		if (mReactionSpawnParticle)
		{
			mCountingScale += DeltaTime;
			if (mCountingScale <= 0.4f)
			{
				float Param1 = mCountingScale * 4.f;
				float Param2 = mCountingScale * 2.f;
				Param1 *= mDuration / 2.0f;
				mReactionSpawnParticle->SetFloatParameter("MeshX", Param1 + Param2);
				mReactionSpawnParticle->SetFloatParameter("MeshZ", Param1 + Param2);
			}
			else if (mCountingScale <= 1.0f)
			{
				float Param1 = mCountingScale * 0.6f + 1.6f;
				float Param2 = mCountingScale * 0.3f + 0.8f;
				Param1 *= mDuration / 2.0f;
				mReactionSpawnParticle->SetFloatParameter("MeshX", Param1 + Param2);
				mReactionSpawnParticle->SetFloatParameter("MeshZ", Param1 + Param2);
			}
			else
			{

			}
		}
	}
}

