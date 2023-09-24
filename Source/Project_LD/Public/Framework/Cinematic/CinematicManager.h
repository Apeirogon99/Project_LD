// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CinematicManager.generated.h"

/**
 * 
 */
class ALevelSequenceActor;

UCLASS()
class PROJECT_LD_API UCinematicManager : public UObject
{
	GENERATED_BODY()
	
public:
	UCinematicManager();
	~UCinematicManager();

public:
	void Init();
	void Play(int32 InCinematicNumber);
	void End();

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<ALevelSequenceActor*> mCinematica;

private:
	UPROPERTY()
	int32 mCurrentNum;
};
