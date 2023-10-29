
// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/NPS_Game.h"

#include <LDGameInstance.h>
#include <Component/ACPartyComponent.h>

ANPS_Game::ANPS_Game()
{
}

ANPS_Game::~ANPS_Game()
{

}

void ANPS_Game::UpdateCurrentStatsBar()
{
	UpdateHealthBar();
	UpdateManaBar();
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

void ANPS_Game::calculationStats()
{
	TArray<float> Total;
	Total.SetNum(22);

	FCharacterBaseStats BaseStats;
	FCharacterGrowStats GrowStats;
	FCharacterEquipmentStats EquipStats;

	//DataTable에서 데이터를 가져와 배열에 저장
	ULDGameInstance* Instance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	BaseStats.SetStatsBaseData(*Instance->GetBaseData(1)); //남 전사
	GrowStats.SetStatsGrowData(*Instance->GetGrowthData(1)); //남 전사

	TArray<float> IBase = BaseStats.FDataToFloat();
	TArray<float> IGrow = GrowStats.FDataToFloat();

	TArray<float> EquipmentIndex;
	EquipmentIndex = mCharacterData.GetEquipment().GetAllItemIndex();
	

	TArray<TArray<float>> IEquipment;
	TArray<float> EquipmentData;
	for (int i = 0; i < EquipmentIndex.Num(); i++)
	{
		FEquipmentItemData equip = *Instance->GetEquipmentItemData(EquipmentIndex[i]);
		EquipStats.SetStatsData(equip);
		IEquipment.Add(EquipStats.FDataToFloat());
	}
	
	//해당하는 전체 스텟값 저장
	for (int i = 0; i < IBase.Num(); i++)
	{
		int32 PartData = 0;
		
		for (int j = 0; j < EquipmentIndex.Num(); j++)
		{
			PartData += IEquipment[j][i];
		}

		IGrow[i] *= mCharacterData.GetLevel();
		Total[i] = IBase[i] + IGrow[i] + PartData;
	}

	mCharacterStats.MaxFloatToFData(Total);
}

void ANPS_Game::UpdateHealthBar()
{
	if (OnCharacterHealthChanged.IsBound())
	{
		OnCharacterHealthChanged.Broadcast();
	}
}

void ANPS_Game::UpdateManaBar()
{
	if (OnCharacterManaChanged.IsBound())
	{
		OnCharacterManaChanged.Broadcast();
	}
}

void ANPS_Game::DetectChangeCurrentStats(FCharacterEquipment oldData, FCharacterEquipment newData)
{
	TArray<float> oldIndex = oldData.GetAllItemIndex();
	TArray<float> newIndex = newData.GetAllItemIndex();
	
	for (int i = 0; i < oldIndex.Num(); i++)
	{
		if (oldIndex[i] != newIndex[i])
		{
			if (oldIndex[i] != 0)
			{
				TakeOffEquipment(oldIndex[i]);
			}
			if (newIndex[i] != 0)
			{
				PutOnEquipment(newIndex[i]);
			}
		}
	}
}

void ANPS_Game::PutOnEquipment(const int32 InIndex)
{
	ULDGameInstance* Instance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	Instance->GetEquipmentItemData(InIndex);
	mCharacterStats.PutOnEquipment(*Instance->GetEquipmentItemData(InIndex));
}

void ANPS_Game::TakeOffEquipment(const int32 InIndex)
{
	ULDGameInstance* Instance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	mCharacterStats.TakeOffEquipment(*Instance->GetEquipmentItemData(InIndex));
}

void ANPS_Game::InitCurrentStats()
{
	mCharacterStats.SetCurrentStats(mCharacterStats.GetMaxStats());
}

void ANPS_Game::InitCurrentEquipmentStats()
{
	TArray<float> dataIndexs = mCharacterData.GetEquipment().GetAllItemIndex();
	for (float index : dataIndexs)
	{
		if (index == 0)
		{
			continue;
		}
		PutOnEquipment(index);
	}
}

void ANPS_Game::InitPartySetting()
{
	mPartyComponent = NewObject<UACPartyComponent>(this, TEXT("Party"));
	if (mPartyComponent == nullptr)
	{
		return;
	}
	this->AddOwnedComponent(mPartyComponent);
	mPartyComponent->RegisterComponent();
}

UACPartyComponent* ANPS_Game::GetPartyComponent()
{
	return mPartyComponent;
}

void ANPS_Game::Destroyed()
{
	Super::Destroyed();

	//mPartyComponent->ClearParty();
}
