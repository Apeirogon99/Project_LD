// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameContent/Enemy/Skill/EnemySkillInterface.h>
#include "Skill_BlinkStun.generated.h"

UCLASS()
class PROJECT_LD_API ASkill_BlinkStun : public AActor, public IEnemySkillInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_BlinkStun();

public:
	virtual void ActiveSkill(FVector InLocation, FRotator InRotation) override;
	virtual void ReactionSkill(FVector InLocation, FRotator InRotation) override;
	virtual void DeactiveSkill(FVector InLocation, FRotator InRotation) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void ActiveParticle();

private:
	FVector mLocation;
	FRotator mRotator;
};
