// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include <Engine/SkeletalMesh.h>
#include "GameDatas.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemData() : name(TEXT("")), cost(0), minimum_level(0), max(1), size_x(0), size_y(0), mesh(nullptr) {}

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	//	int32	id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32	category_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString	name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32	cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32	minimum_level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32	max;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32	size_x;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32	size_y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		USkeletalMesh* mesh;
};

UCLASS()
class PROJECT_LD_API ACustomDataTables : public AActor
{
	GENERATED_BODY()
};