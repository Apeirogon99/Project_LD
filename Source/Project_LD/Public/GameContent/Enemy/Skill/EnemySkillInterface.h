// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/Interface.h"
#include "EnemySkillInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemySkillInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_LD_API IEnemySkillInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	int64 mRemoteID;

public:
	virtual void ActiveSkill(FVector InLocation, FRotator InRotation) {}
	virtual void ReactionSkill(FVector InLocation, FRotator InRotation) {}
	virtual void DeactiveSkill(FVector InLocation, FRotator InRotation) {}
};
