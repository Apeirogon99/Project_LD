// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <Struct/Game/CharacterDatas.h>
#include <Struct/Game/CharacterStatusData.h>
#include <Struct/Game/EnemyData.h>
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
	void SetServerData(const int32 inServerID, const FString& inServerName, const FString& inServerIP, const int32 inServerPort);

public:
	FItemData*						GetItemData(int32 inCode);
	FEquipmentItemData*				GetEquipmentItemData(int32 inCode);
	FStatusBaseData*				GetBaseData(int32 inCode);
	FStatusGrowthData*				GetGrowthData(int32 inCode);
	FEnemyData*						GetEnemyData(int32 inCode);
	FEnemyStatData*					GetEnemyStatData(int32 inCode);
	FString							GetToken();
	UServerData*					GetServerData();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mGameItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mEquipmentDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mCharacterStatusDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mCharacterStatusGrowthDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mEnemyDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mEnemyStatDataTable;

private:
	UPROPERTY()
	FString mToken;

	UPROPERTY()
	UServerData* mServerData;
};
