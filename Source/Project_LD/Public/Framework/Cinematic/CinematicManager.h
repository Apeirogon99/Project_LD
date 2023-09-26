// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CinematicManager.generated.h"

/**
 * 
 */
class ULevelSequencePlayer;
class ALevelSequenceActor;

UCLASS()
class PROJECT_LD_API UCinematicManager : public UObject
{
	GENERATED_BODY()
	
public:
	UCinematicManager();
	~UCinematicManager();

public:
	void Play(int32 InCinematicNumber, UWorld* InWorld);
	void End();

private:
	UPROPERTY()
	ULevelSequencePlayer* LevelSequencePlayer;

	UPROPERTY()
	ALevelSequenceActor* LevelSequenceActor;
};
