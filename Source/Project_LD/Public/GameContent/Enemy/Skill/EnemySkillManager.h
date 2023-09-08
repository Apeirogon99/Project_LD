// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemySkillManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UEnemySkillManager : public UObject
{
	GENERATED_BODY()

public:
	UEnemySkillManager();
	~UEnemySkillManager();

public:
	void Init();
	void InputActiveSkillData(UWorld* InWorld, AActor* InActor, const int32 InSkillID, FVector InLocation, FRotator InRotator, const int64 InobjectID);
	void InputReactionSkillData(UWorld* InWorld, AActor* InActor, const int32 InSkillID, FVector InLocation, FRotator InRotator, const int64 InobjectID);
	void InputDeactiveSkillData(UWorld* InWorld, AActor* InActor, const int32 InSkillID, FVector InLocation, FRotator InRotator, const int64 InobjectID);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LichSkillClass", meta = (AllowPrivateAccess = "true"))
	TArray<UClass*> mLichSkillClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DarkKnightSkillClass", meta = (AllowPrivateAccess = "true"))
	TArray<UClass*> mDarkKnightSkillClass;
};
