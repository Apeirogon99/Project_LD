// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <Struct/Game/CharacterDatas.h>
#include <Engine/AssetManager.h>
#include "LDGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API ULDGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	ULDGameInstance();
	~ULDGameInstance();

protected:
	virtual void Init() override;
	void OnCompleteItemAssetsLoad();

public:

	UPROPERTY(BlueprintReadOnly, Category = "Network")
		FString mTicket;

	UPROPERTY()
	FCharacterDatas mCharacterDatas;

	UPROPERTY()
	FCharacterAppearance mCharacterAppearance;

public:
	//UAssetManager mAssetManager;
	//TArray<USkeletalMesh> mItemPaths;
};
