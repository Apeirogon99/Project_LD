// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryFrame.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECT_LD_API FLine
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") FVector2D Start;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line") FVector2D End;
};

USTRUCT(BlueprintType)
struct PROJECT_LD_API FTile
{
	GENERATED_USTRUCT_BODY()

	FTile() : X(0), Y(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile") int32 X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile") int32 Y;
};

UCLASS()
class PROJECT_LD_API UInventoryFrame : public UObject
{
	GENERATED_BODY()
	
};
