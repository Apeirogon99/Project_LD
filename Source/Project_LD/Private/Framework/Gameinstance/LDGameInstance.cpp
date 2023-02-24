// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Gameinstance/LDGameInstance.h"
#include <Struct/Game/GameDatas.h>
#include <Engine/StreamableManager.h>

ULDGameInstance::ULDGameInstance()
{
}

ULDGameInstance::~ULDGameInstance()
{
}

FItemData* ULDGameInstance::GetItemData(int32 inCode)
{
	return mGameItemDataTable->FindRow<FItemData>(*FString::FromInt(inCode), TEXT(""));
}
