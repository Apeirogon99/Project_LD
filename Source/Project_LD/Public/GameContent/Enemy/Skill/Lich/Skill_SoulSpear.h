// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameContent/Enemy/Skill/Lich/LichSkillBase.h"
#include "GameContent/Projectile/LineProjectile.h"
#include "Skill_SoulSpear.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API ASkill_SoulSpear : public ALineProjectile, public ILichSkillBase
{
	GENERATED_BODY()

public:
	ASkill_SoulSpear();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void ActiveSkill() override;
	virtual void DeactiveSkill() override;

protected:
	virtual void OnReady() override;
	virtual void OnStart() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UNiagaraComponent* mTail;
};

