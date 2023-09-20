// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <Struct/Game/GameDatas.h>
#include <Struct/Game/CharacterDatas.h>
#include <Struct/Game/CharacterStatusData.h>
#include <Struct/Game/EnemyData.h>
#include <Struct/Game/LevelDataTablle.h>
#include <Struct/Game/ObstructionData.h>
#include "LDGameInstance.generated.h"

class UDataTable;
class UServerData;
struct FItemData;

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

public:
	UPROPERTY()
	FCharacterData mCharacterData;

public:
	void SetToken(const FString& inToken);
	void SetDungeonID(const int32& inDungeonID);
	void SetServerData(const int32 inServerID, const FString& inServerName, const FString& inServerIP, const int32 inServerPort);

public:
	FItemData*						GetItemData(int32 inCode);
	FEquipmentItemData*				GetEquipmentItemData(int32 inCode);
	FStatsBaseData*				GetBaseData(int32 inCode);
	FStatsGrowthData*				GetGrowthData(int32 inCode);
	FEnemyData*						GetEnemyData(int32 inCode);
	FEnemyStatData*					GetEnemyStatData(int32 inCode);
	FLevelDataTable*				GetLevelDataTable(int32 inLevel);
	FBuffData*						GetBuffData(int32 inCode);
	FObstructionData*				GetObstructionData(int32 inObstructionType);
	FString							GetToken();
	UServerData*					GetServerData();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mGameItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mEquipmentDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mCharacterStatsDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mCharacterStatsGrowthDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mEnemyDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mEnemyStatDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mBuffidDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mLevelDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mObstructionTable;

private:
	UPROPERTY()
	FString mToken;

	UPROPERTY()
	int32 mDungeonID;

	UPROPERTY()
	UServerData* mServerData;
};
