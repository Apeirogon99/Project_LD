// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "UObject/Object.h"
#include <Engine/SkeletalMesh.h>
#include "Engine/Texture2D.h"
#include "GameDatas.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FItemData() : category_id(0), character_class_id(0), race_id(0), tier_id (0), name(TEXT("")), description(TEXT(""))
		, cost(0), level(0), size_x(0), size_y(0), icon(nullptr), mesh(nullptr) {}

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
	FString	description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32	cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32	level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32	size_x;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32	size_y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UTexture2D* icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	USkeletalMesh* mesh;

	void Clear() {
		category_id=0;
		character_class_id = 0;
		race_id = 0;
		tier_id = 0;
		name=TEXT("");
		description=TEXT("");
		cost = 0;
		level = 0;
		size_x = 0;
		size_y = 0; 
		icon=nullptr; 
		mesh=nullptr;
	}
};

UCLASS(Blueprintable)
class PROJECT_LD_API UItemObjectData : public UObject
{
	GENERATED_BODY()

public:
	UItemObjectData() : ObjectID(-1), position_x(-1), position_y(-1), rotation(0) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int64 ObjectID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FItemData ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 position_x;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 position_y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 rotation;

public:
	UFUNCTION(BlueprintCallable)
	void Rotate();

	UFUNCTION(BlueprintCallable)
	bool IsValid();

	UFUNCTION(BlueprintCallable)
	FVector2D GetSize() const;

	UFUNCTION(BlueprintCallable)
	void SettingObjectData(FItemData OtheritemData);

	void Clear();
};

UCLASS()
class PROJECT_LD_API ACustomDataTables : public AActor
{
	GENERATED_BODY()
};