// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LichSkillBase.h"
#include "Skill_OnslaughtOfShadows.generated.h"

UCLASS()
class PROJECT_LD_API ASkill_OnslaughtOfShadows : public AActor, public ILichSkillBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_OnslaughtOfShadows();

public:
	virtual void ActiveSkill(FVector InLocation, FRotator InRotation) override;
	virtual void ReactionSkill(FVector InLocation, FRotator InRotation) override;
	virtual void DeactiveSkill() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
