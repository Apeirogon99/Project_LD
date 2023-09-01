// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LichSkillBase.h"
#include "Skill_SoulShackles.generated.h"

UCLASS()
class PROJECT_LD_API ASkill_SoulShackles : public ALichSkillBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_SoulShackles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
