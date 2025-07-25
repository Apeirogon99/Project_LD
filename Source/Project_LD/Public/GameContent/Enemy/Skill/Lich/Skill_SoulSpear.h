// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameContent/Enemy/Skill/EnemySkillInterface.h>
#include "GameContent/Projectile/LineProjectile.h"
#include "Skill_SoulSpear.generated.h"

class UStaticMeshComponent;
class UNiagaraComponent;
class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API ASkill_SoulSpear : public ALineProjectile, public IEnemySkillInterface
{
	GENERATED_BODY()

public:
	ASkill_SoulSpear();

protected:
	virtual void BeginPlay() override;

public:
	virtual void ActiveSkill(FVector InLocation, FRotator InRotation) override;
	virtual void ReactionSkill(FVector InLocation, FRotator InRotation) override;
	virtual void DeactiveSkill(FVector InLocation, FRotator InRotation) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UNiagaraComponent* mNiagaraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UNiagaraSystem* mAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UNiagaraSystem* mCasting;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UNiagaraSystem* mHit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UNiagaraSystem* mProjectile;
};

