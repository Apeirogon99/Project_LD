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

FStatusBaseData* ULDGameInstance::GetBaseData(int32 inCode)
{
	return mCharacterStatusDataTable->FindRow<FStatusBaseData>(*FString::FromInt(inCode), TEXT(""));
}

FStatusGrowthData* ULDGameInstance::GetGrowthData(int32 inCode)
{
	return mCharacterStatusGrowthDataTable->FindRow<FStatusGrowthData>(*FString::FromInt(inCode), TEXT(""));
}

FEnemyData* ULDGameInstance::GetEnemyData(int32 inCode)
{
	return mEnemyDataTable->FindRow<FEnemyData>(*FString::FromInt(inCode), TEXT(""));
}

FEnemyStatData* ULDGameInstance::GetEnemyStatData(int32 inCode)
{
	return mEnemyStatDataTable->FindRow<FEnemyStatData>(*FString::FromInt(inCode), TEXT(""));
}

FString ULDGameInstance::GetToken()
{
	return mToken;
}

UServerData* ULDGameInstance::GetServerData()
{
	return mServerData;
}
