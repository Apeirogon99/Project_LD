// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Gameinstance/LDGameInstance.h"
#include <Struct/Game/GameDatas.h>
#include <Struct/Identity/ServerData.h>
#include <Engine/StreamableManager.h>

ULDGameInstance::ULDGameInstance()
{
	mServerData = nullptr;
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

FString ULDGameInstance::GetToken()
{
	return mToken;
}

UServerData* ULDGameInstance::GetServerData()
{
	return mServerData;
}
