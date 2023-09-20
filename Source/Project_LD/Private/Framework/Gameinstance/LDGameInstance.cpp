// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Gameinstance/LDGameInstance.h"
#include <Struct/Game/GameDatas.h>
#include <Struct/Identity/ServerData.h>
#include <Engine/StreamableManager.h>

#define NETWORK_LOCAL 1

ULDGameInstance::ULDGameInstance()
{
	mServerData = nullptr;


#if NETWORK_LOCAL
	mToken = TEXT("LOCAL_TEST");
#else
	mToken = TEXT("LOCAL_TEST");
#endif

}

ULDGameInstance::~ULDGameInstance()
{
}

void ULDGameInstance::SetToken(const FString& inToken)
{
	mToken = inToken;
}

void ULDGameInstance::SetDungeonID(const int32& inDungeonID)
{
	mDungeonID = inDungeonID;
}

void ULDGameInstance::SetServerData(const int32 inServerID, const FString& inServerName, const FString& inServerIP, const int32 inServerPort)
{
	if (nullptr == mServerData)
	{
		mServerData = NewObject<UServerData>();
	}

	mServerData->SetServerID(inServerID);
	mServerData->SetServerName(inServerName);
	mServerData->SetServerIP(inServerIP);
	mServerData->SetServerPort(inServerPort);
}

FItemData* ULDGameInstance::GetItemData(int32 inCode)
{
	return mGameItemDataTable->FindRow<FItemData>(*FString::FromInt(inCode), TEXT(""));
}

FEquipmentItemData* ULDGameInstance::GetEquipmentItemData(int32 inCode)
{
	return mEquipmentDataTable->FindRow<FEquipmentItemData>(*FString::FromInt(inCode), TEXT(""));
}

FStatsBaseData* ULDGameInstance::GetBaseData(int32 inCode)
{
	return mCharacterStatsDataTable->FindRow<FStatsBaseData>(*FString::FromInt(inCode), TEXT(""));
}

FStatsGrowthData* ULDGameInstance::GetGrowthData(int32 inCode)
{
	return mCharacterStatsGrowthDataTable->FindRow<FStatsGrowthData>(*FString::FromInt(inCode), TEXT(""));
}

FEnemyData* ULDGameInstance::GetEnemyData(int32 inCode)
{
	return mEnemyDataTable->FindRow<FEnemyData>(*FString::FromInt(inCode), TEXT(""));
}

FEnemyStatData* ULDGameInstance::GetEnemyStatData(int32 inCode)
{
	return mEnemyStatDataTable->FindRow<FEnemyStatData>(*FString::FromInt(inCode), TEXT(""));
}

FLevelDataTable* ULDGameInstance::GetLevelDataTable(int32 inLevel)
{
	return mLevelDataTable->FindRow<FLevelDataTable>(*FString::FromInt(inLevel), TEXT(""));
}

FBuffData* ULDGameInstance::GetBuffData(int32 inCode)
{
	return mBuffidDataTable->FindRow<FBuffData>(*FString::FromInt(inCode), TEXT(""));
}

FObstructionData* ULDGameInstance::GetObstructionData(int32 inObstructionType)
{
	return mObstructionTable->FindRow<FObstructionData>(*FString::FromInt(inObstructionType), TEXT(""));
}

FString ULDGameInstance::GetToken()
{
	return mToken;
}

UServerData* ULDGameInstance::GetServerData()
{
	return mServerData;
}
