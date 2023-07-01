// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/NPS_Game.h"

#include <LDGameInstance.h>

ANPS_Game::ANPS_Game()
{
}

ANPS_Game::~ANPS_Game()
{
}

void ANPS_Game::SetRemotePlayerID(const int64 inRemoteID)
{
	mRemoteID = inRemoteID;
}

void ANPS_Game::SetCharacterData(const FCharacterData& InCharacterDatas)
{
	mCharacterData = InCharacterDatas;
}

void ANPS_Game::SetCharacterEqipment(const FCharacterEquipment& inCharacterEquipment)
{
	mCharacterData.SetEquipment(inCharacterEquipment);
}

void ANPS_Game::calculationStatus()
{
	TArray<float> Total;
	Total.SetNum(22);

	FCharacterBaseStatus BaseStatus;
	FCharacterGrowStatus GrowStatus;
	FCharacterEquipmentStatus EquipStatus;

	//DataTable에서 데이터를 가져와 배열에 저장
	ULDGameInstance* Instance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	BaseStatus.SetStatusBaseData(*Instance->GetBaseData(1));
	GrowStatus.SetStatusGrowData(*Instance->GetGrowthData(1));

	TArray<float> IBase = BaseStatus.FDataToFloat();
	TArray<float> IGrow = GrowStatus.FDataToFloat();

	TArray<float> EquipmentIndex;
	EquipmentIndex = mCharacterData.GetEquipment().GetAllItemIndex();

	/*
	TArray<TArray<float>> IEquipment;
	for (int i = 0; i < EquipmentIndex.Num(); i++)
	{
		EquipStatus.mEquipmentStatus = *Instance->GetEquipmentItemData(EquipmentIndex[i]);
		IEquipment.Add(EquipStatus.FDataToFloat());
	}
	*/
	//해당하는 전체 스텟값 저장
	for (int i = 0; i < IBase.Num(); i++)
	{
		int32 PartData = 0;
		/*
		for (int j = 0; j < EquipmentIndex.Num(); j++)
		{
			PartData += IEquipment[j][i];
		}*/

		IGrow[i] *= mCharacterData.GetLevel();
		Total[i] = IBase[i] + IGrow[i] + PartData;
	}

	mCharacterStatus.FloatToFData(Total);
}
