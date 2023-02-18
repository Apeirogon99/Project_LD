// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterDatas.generated.h"

UENUM(BlueprintType)
enum class EClass : uint8
{
	None			UMETA(DisplayName = "None"),
	Warrior 		UMETA(DisplayName = "Warrior"),
	Wizard			UMETA(DisplayName = "Wizard"),
};

UENUM(BlueprintType)
enum class ETribe : uint8
{
	None			UMETA(DisplayName = "None"),
	Man				UMETA(DisplayName = "Man"),
	Woman			UMETA(DisplayName = "Woman"),
	Orc				UMETA(DisplayName = "Orc"),
};

UENUM()
enum class EPart : uint8
{
	None			UMETA(DisplayName = "None"),
	Body			UMETA(DisplayName = "Body"),
	Hair			UMETA(DisplayName = "Hair"),
	Eye				UMETA(DisplayName = "Eye"),
	Eyebrow			UMETA(DisplayName = "Eyebrow"),
};

USTRUCT(Atomic)
struct FCharacterDatas
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString mName;

	UPROPERTY()
	int32 mLevel;

	UPROPERTY()
	int32 mPosition;

	UPROPERTY()
	int32 mClass;

	UPROPERTY()
	int32 mTribe;

	UPROPERTY()
	uint32 mSkin;

	UPROPERTY()
	uint32 mHair;

	UPROPERTY()
	uint32 mEye;

	UPROPERTY()
	uint32 mEyebrow;
};