// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LichSkillBase.h"
#include <GameContent/Enemy/Skill/EnemySkillInterface.h>
#include "Skill_LifeVessel.generated.h"

UCLASS()
class PROJECT_LD_API ASkill_LifeVessel : public AActor, public IEnemySkillInterface
{
	GENERATED_BODY()
	
public:	
	ASkill_LifeVessel();

public:
	virtual void ActiveSkill(FVector InLocation, FRotator InRotation) override;
	virtual void ReactionSkill(FVector InLocation, FRotator InRotation) override;
	virtual void DeactiveSkill(FVector InLocation, FRotator InRotation) override;

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
