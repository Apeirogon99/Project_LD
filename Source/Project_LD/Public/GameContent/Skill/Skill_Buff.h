// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill_Parent.h"
#include "Skill_Buff.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class USphereComponent;

UCLASS()
class PROJECT_LD_API ASkill_Buff : public ASkill_Parent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_Buff();
	
public:
	virtual void AppearSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration) override;
	virtual void ReactionSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* mSummonParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* mSpawnedParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* mPlayerInCheckCollision;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<int32> mActivePlayerId;

	bool IsLocalParty;

private:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
