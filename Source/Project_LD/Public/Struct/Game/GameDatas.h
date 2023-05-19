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
	GENERATED_USTRUCT_BODY()

public:
	FItemData() : category_id(0), character_class_id(0), race_id(0), tier_id(0), name(TEXT("")), position_x(-1),position_y(-1), description(TEXT(""))
		, cost(0), level(0), rate(1), size_x(0), size_y(0),rotation(0), icon(nullptr), mesh(nullptr) {}

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	//int32	id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32	category_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32	character_class_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32	race_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32	tier_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString	name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 position_x;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 position_y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString	description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32	cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32	level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32	rate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32	size_x;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32	size_y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32	rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UTexture2D* icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	USkeletalMesh* mesh;

	bool IsValid() const
	{
		if (category_id == 0)
			return false;
		if (position_x == -1)
			return false;
		if (position_y == -1)
			return false;
		if (size_x == 0)
			return false;
		if (size_y == 0)
			return false;
		return true;
	}

	bool operator==(const FItemData& Other) const
	{
		return this==&Other;
	}

	friend uint32 GetTypeHash(const FItemData& ItemData);
};

UCLASS()
class PROJECT_LD_API ACustomDataTables : public AActor
{
	GENERATED_BODY()
};