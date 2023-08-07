// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LevelDataTablle.generated.h"

USTRUCT(Atomic, BlueprintType)
struct PROJECT_LD_API FLevelDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:	
	FLevelDataTable();

public:
	UPROPERTY()
		int32 level;

	UPROPERTY()
		int32 next_experience;
};
