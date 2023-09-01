// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameContent/Enemy/Skill/Lich/LichSkillBase.h"
#include "Skill_Rise.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API ASkill_Rise : public AActor, public ILichSkillBase
{
	GENERATED_BODY()
	
public:
	ASkill_Rise();

public:
	virtual void ActiveSkill() override;
	virtual void DeactiveSkill() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
