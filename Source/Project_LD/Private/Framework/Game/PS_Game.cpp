// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PS_Game.h"
#include <Handler/ClientHUD.h>
#include <Widget/Game/Inventory/UWInventory.h>
#include <Widget/Game/Item/W_ItemSpace.h>

#include <GM_Game.h>
#include <PC_Game.h>
#include <C_Game.h>
#include <LDGameInstance.h>

APS_Game::APS_Game()
{
	mRemoteID = 0;
}

APS_Game::~APS_Game()
{
}

void APS_Game::InitializeLocalPlayerState()
{

	AGM_Game* gameMode = Cast<AGM_Game>(GetWorld()->GetAuthGameMode());
	if (nullptr == gameMode)
	{
		return;
	}
	
	if (gameMode->GetNetworkController() == GetPawn()->GetController())
	{
		mInventoryComponent = NewObject<UACInventoryComponent>(this,TEXT("Inventory"));
		this->AddOwnedComponent(mInventoryComponent);
		mInventoryComponent->RegisterComponent();

		if (mInventoryComponent == nullptr)
		{
			return;
		}

		mEquipmentComponent = NewObject<UACEquipment>(this, TEXT("Equipment"));
		this->AddOwnedComponent(mEquipmentComponent);
		mEquipmentComponent->RegisterComponent();

		if (mEquipmentComponent == nullptr)
		{
			return;
		}
	}
	APC_Game* playercontroller = Cast<APC_Game>(gameMode->GetNetworkController());
	if (nullptr == playercontroller)
	{
		return;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(playercontroller->GetHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("Inventory")));
	if (nullptr == widget)
	{
		return;
	}

	UUWInventory* inventory = Cast<UUWInventory>(widget);

	inventory->InitInventory(mInventoryComponent, 50.0f, mEquipmentComponent);

	mEquipmentComponent->Init(inventory);
	calculationStatus();
	inventory->UpdateStatus();

	mCharacterStatus.mCurrentStatus = mCharacterStatus.mMaxStatus;
}

void APS_Game::SetRemotePlayerID(const int64 inRemoteID)
{
	mRemoteID = inRemoteID;
}

void APS_Game::SetCharacterData(const FCharacterData& InCharacterDatas)
{
	mCharacterData = InCharacterDatas;
}

void APS_Game::SetCharacterEqipment(const FCharacterEquipment& inCharacterEquipment)
{
	mCharacterData.mEquipment = inCharacterEquipment;
}

void APS_Game::calculationStatus()
{
	TArray<float> Total;
	Total.SetNum(22);

	FCharacterBaseStatus BaseStatus;
	FCharacterGrowStatus GrowStatus;
	FCharacterEquipmentStatus EquipStatus;

	//DataTable에서 데이터를 가져와 배열에 저장
	ULDGameInstance* Instance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	BaseStatus.mBaseStatus = *Instance->GetBaseData(1);
	GrowStatus.mGrowStatus = *Instance->GetGrowthData(1);
	 
	TArray<float> IBase = BaseStatus.FDataToFloat();
	TArray<float> IGrow = GrowStatus.FDataToFloat();
	
	TArray<float> EquipmentIndex;
	EquipmentIndex = mCharacterData.mEquipment.GetAllItemIndex();
	
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

		IGrow[i] *= mCharacterData.mLevel;
		Total[i] = IBase[i] + IGrow[i] + PartData;
	}

	mCharacterStatus.FloatToFData(Total);
}
