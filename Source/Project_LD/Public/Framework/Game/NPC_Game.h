// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPC_Game.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API ANPC_Game : public AAIController
{
	GENERATED_BODY()
	
public:
	ANPC_Game();
	~ANPC_Game();

public:
	void NPCMoveDestination(const FVector inOldMovementLocation, const FVector inNewMovementLocation, const int64 inTime);
	void MoveCorrection(const float inDeltaTime);


private:
	bool IsCorrection;

	FVector mTargetLoction;
};
