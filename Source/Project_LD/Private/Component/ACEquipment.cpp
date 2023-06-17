// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ACEquipment.h"
#include "Components/Widget.h"
#include "Framework/Gameinstance/LDGameInstance.h"
#include <Widget/Game/Inventory/UWInventory.h>
#include <Widget/Game/Item/W_ItemSpace.h>
#include <Struct/Game/GameDatas.h>
#include "Blueprint/WidgetTree.h"

// Sets default values for this component's properties
UACEquipment::UACEquipment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UACEquipment::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UACEquipment::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UACEquipment::Init(UUWInventory* inventory)
{
	UWidget* ISHelmet = inventory->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceHelmet")));
	UWidget* ISShoulders = inventory->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceShoulders")));
	UWidget* ISChest = inventory->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceChest	")));
	UWidget* ISBracers = inventory->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceBracers")));
	UWidget* ISHands = inventory->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceHands")));
	UWidget* ISPants = inventory->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpacePants")));
	UWidget* ISBoots = inventory->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceBoots")));
	UWidget* ISLeftWeapon = inventory->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceLeftWeapon")));
	UWidget* ISRightWeapon = inventory->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceRightWeapon")));

	mEquipmentWidget.Add(Cast<UW_ItemSpace>(ISHelmet));
	mEquipmentWidget.Add(Cast<UW_ItemSpace>(ISShoulders));
	mEquipmentWidget.Add(Cast<UW_ItemSpace>(ISChest));
	mEquipmentWidget.Add(Cast<UW_ItemSpace>(ISBracers));
	mEquipmentWidget.Add(Cast<UW_ItemSpace>(ISHands));
	mEquipmentWidget.Add(Cast<UW_ItemSpace>(ISPants));
	mEquipmentWidget.Add(Cast<UW_ItemSpace>(ISBoots));
	mEquipmentWidget.Add(Cast<UW_ItemSpace>(ISLeftWeapon));
	mEquipmentWidget.Add(Cast<UW_ItemSpace>(ISRightWeapon));

	mEquipmentData.SetNum(mEquipmentWidget.Num());
	for (int i = 0; i < mEquipmentWidget.Num(); i++)
	{
		mEquipmentData[i] = NewObject<UItemObjectData>();
	}
}

void UACEquipment::ClearEquipment()
{
	for (int i = 0; i < mEquipmentData.Num(); i++)
	{
		mEquipmentData[i]->Clear();
	}
}

void UACEquipment::LoadEquipment(int64 ObjectID, int32 ItemCode, int32 PartCode)
{
	ULDGameInstance* Instance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	FItemData* ItemTable = Instance->GetItemData(ItemCode);
	
	mEquipmentData[PartCode - 1]->ItemData = *ItemTable;
	mEquipmentData[PartCode - 1]->ObjectID = ObjectID;
	mEquipmentData[PartCode - 1]->mItemCode = ItemCode;

	ChangedItemSpace(PartCode,mEquipmentData[PartCode-1]);
}

void UACEquipment::ChangedItemSpace(int32 PartID, UItemObjectData* ItemData)
{
	mEquipmentWidget[PartID - 1]->Refresh(ItemData);
}