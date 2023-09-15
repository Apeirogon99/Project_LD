// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill_Parent.h"
#include "Skill_Dash.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API ASkill_Dash : public ASkill_Parent
{
	GENERATED_BODY()
	
public:
	ASkill_Dash();

public:
	virtual void AppearSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration) override;
	virtual void ReactionSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
