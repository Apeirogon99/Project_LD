// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Skill/Skill_SwordSpirit.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
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

	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> LOOP_PARTICLE(TEXT("ParticleSystem'/Game/Test/Particle/P_Skill_ChargeLoop.P_Skill_ChargeLoop'"));
	if (LOOP_PARTICLE.Succeeded())
	{	
		mLoopParticle = LOOP_PARTICLE.Object;
	}

	mCurrentCharge = 0;
	mCountingScale = 0;
	mAppearActiveTime = 0;
	bAppearActive = false;
	bIsSpawn = false;
}

void ASkill_SwordSpirit::AppearSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration)
{
	Super::AppearSkill(InRemoteID, InObjectID, InSkillID, InLocation, InRotation, InDuration);
	
	bAppearActive = true;
	mLoopSpawnParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mLoopParticle, InLocation, InRotation, FVector(0.3f), false);
	GetWorld()->GetTimerManager().SetTimer(ChargeTimer, this, &ASkill_SwordSpirit::ManagedChargeValue, 1.f, true);
}

void ASkill_SwordSpirit::ReactionSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration)
{
	Super::ReactionSkill(InRemoteID, InObjectID, InSkillID, InLocation, InRotation, InDuration);

	bAppearActive = false;
	AppearBeforeManageParticle();

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

// Called when the game starts or when spawned
void ASkill_SwordSpirit::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkill_SwordSpirit::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(ChargeTimer);

	if (mLoopSpawnParticle)
	{
		mLoopSpawnParticle->DestroyComponent();
	}

	if (mReactionSpawnParticle)
	{
		mReactionSpawnParticle->DestroyComponent();
	}
}

void ASkill_SwordSpirit::ManagedChargeValue()
{
	if (mCurrentCharge < 2)
	{
		mCurrentCharge++;
		if (UParticleSystem* Particle = LoadObject<UParticleSystem>(nullptr, TEXT("ParticleSystem'/Game/Test/Particle/P_Skill_Charge2.P_Skill_Charge2'")))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation(), FRotator(), FVector(0.3f), true);
		}
	}
}

void ASkill_SwordSpirit::AppearBeforeManageParticle()
{
	if (mLoopSpawnParticle)
	{
		mLoopSpawnParticle->DestroyComponent();
	}

	GetWorldTimerManager().ClearTimer(ChargeTimer);
}

// Called every frame
void ASkill_SwordSpirit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAppearActive)
	{
		mAppearActiveTime += DeltaTime;
	}

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

