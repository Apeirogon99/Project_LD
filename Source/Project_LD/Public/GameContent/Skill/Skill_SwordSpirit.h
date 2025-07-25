// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill_Parent.h"
#include "Skill_SwordSpirit.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class PROJECT_LD_API ASkill_SwordSpirit : public ASkill_Parent
{
	GENERATED_BODY()
	
public:
	virtual void AppearSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration) override;
	virtual void ReactionSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration) override;

public:	
	// Sets default values for this actor's properties
	ASkill_SwordSpirit();

public:
	FORCEINLINE float GetActiveTime() const { return mAppearActiveTime; }

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void ManagedChargeValue();
	void AppearBeforeManageParticle();

private:
	UPROPERTY()
	FTimerHandle ChargeTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 mCurrentCharge;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* mLoopParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* mLoopSpawnParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* mReactionParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* mReactionSpawnParticle;

	UPROPERTY()
	FVector mLocation;

	UPROPERTY()
	FRotator mRotation;

	bool bIsSpawn;
	bool bAppearActive;

	float mCountingScale;
	float mDuration; 
	float mAppearActiveTime;
};
