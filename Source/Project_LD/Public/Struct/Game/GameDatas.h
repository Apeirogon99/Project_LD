// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "UObject/Object.h"
#include <Engine/SkeletalMesh.h>
#include "Engine/Texture2D.h"
#include "GameDatas.generated.h"

UENUM()
enum class EItemObjectType
{
	None,
	Inventory,
	Equipment
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FItemData() : category_id(0), character_class_id(0), race_id(0), tier_id (0), name(TEXT("")), description(TEXT(""))
		, cost(0), level(0), size_x(0), size_y(0), icon(nullptr), mesh(nullptr) {}

public:
	void Clear() {
		category_id = 0;
		character_class_id = 0;
		race_id = 0;
		tier_id = 0;
		name = TEXT("");
		description = TEXT("");
		cost = 0;
		level = 0;
		size_x = 0;
		size_y = 0;
		icon = nullptr;
		mesh = nullptr;
	}

public:
	void SetCategoryID(const int32 inCategoryID) { category_id = inCategoryID; }
	void SetCharacterClassID(const int32 inCharacterClassID) { character_class_id = inCharacterClassID; }
	void SetRaceID(const int32 inRaceID) { race_id = inRaceID; }
	void SetTierID(const int32 inTierID) { tier_id = inTierID; }
	void SetName(const FString inName) { name = inName; }
	void SetDescription(const FString inDescription) { description = inDescription; }
	void SetCost(const int32 inCost) { cost = inCost; }
	void SetLevel(const int32 inLevel) { level = inLevel; }
	void SetSizeX(const int32 inSizeX) { size_x = inSizeX; }
	void SetSizeY(const int32 inSizeY) { size_y = inSizeY; }
	void SetIcon(UTexture2D* inIcon) { icon = inIcon; }
	void SetMesh(USkeletalMesh* inMesh) { mesh = inMesh; }

public:
	int32 GetCategoryID() const								{ return category_id; }
	int32 GetCharacterClassID() const					{ return character_class_id; }
	int32 GetRaceID() const										{ return race_id; }
	int32 GetTierID() const										{ return tier_id; }
	FString GetName() const									{ return name; }
	FString GetDescription() const							{ return description; }
	int32 GetCost() const											{ return cost; }
	int32 GetLevel() const										{ return level; }
	int32 GetSizeX() const										{ return size_x; }
	int32 GetSizeY() const										{ return size_y; }
	UTexture2D* GetIcon() const							{ return icon; }
	USkeletalMesh* GetMesh() const						{ return mesh; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32	category_id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32	character_class_id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32	race_id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32	tier_id;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FString	name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FString	description;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32	cost;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32	level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32	size_x;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32	size_y;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	UTexture2D* icon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	USkeletalMesh* mesh;
};

UCLASS(Blueprintable)
class PROJECT_LD_API UItemObjectData : public UObject
{
	GENERATED_BODY()

public:
	UItemObjectData() : ObjectID(0), mItemCode(0), position_x(0), position_y(0), rotation(0), mType(EItemObjectType::None) {}

public:
	UFUNCTION(BlueprintCallable)
		void Rotate();

	UFUNCTION(BlueprintCallable)
		bool IsValid();

	UFUNCTION(BlueprintCallable)
		FVector2D GetSize() const;

	UFUNCTION(BlueprintCallable)
		void SettingObjectData(const FItemData OtheritemData);

	void Clear();

public:
	void SetObjectID(const int64& inObjectID)									{ ObjectID = inObjectID; }
	void SetItemCode(const int32& inItemCode)								{ mItemCode = inItemCode; }
	void SetItemData(const FItemData& inItemData)							{ ItemData = inItemData; }
	void SetPositionX(const int32& inPositionX)								{ position_x = inPositionX; }
	void SetPositionY(const int32& inPositionY)								{ position_y = inPositionY; }
	void SetRotation(const int32& inRotation)									{ rotation = inRotation; }
	void SetType(const EItemObjectType& inObjectType)				{ mType = inObjectType; }

public:
	int64							GetObjectID() const		{ return ObjectID; }
	int32							GetItemCode() const		{ return mItemCode; }
	FItemData					GetItemData() const		{ return ItemData; }
	int32							GetPositionX() const		{ return position_x; }
	int32							GetPositionY() const		{ return position_y; }
	int32							GetRotation() const		{ return rotation; }
	EItemObjectType		GetType() const				{ return mType; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int64 ObjectID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32 mItemCode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	FItemData ItemData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32 position_x;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32 position_y;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	int32 rotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	EItemObjectType mType;
};

UCLASS()
class PROJECT_LD_API ACustomDataTables : public AActor
{
	GENERATED_BODY()
};