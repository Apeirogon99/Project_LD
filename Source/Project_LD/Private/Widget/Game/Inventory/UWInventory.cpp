// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/Inventory/UWInventory.h"
#include "Game/Inventory/StoreInven/UWGridInventory.h"

#include "Blueprint/WidgetTree.h"
#include "Blueprint/DragDropOperation.h"

#include <Widget/Handler/ClientHUD.h>
#include <Widget/Game/Main/W_MainGame.h>
#include <Widget/Game/Equipment/UWEquipmentWindow.h>

#include <Game/PS_Game.h>
#include <Game/GM_Game.h>
#include <Game/PC_Game.h>

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/BackgroundBlur.h"
#include <Component/ACInventoryComponent.h>

#include "Kismet/GameplayStatics.h"

void UUWInventory::NativeConstruct()
{
	Super::NativeConstruct();

	BackgroundBorder = Cast<UBorder>(GetWidgetFromName(TEXT("BackgroundBorder")));
	TB_InvenTitle = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_InvenTitle")));
	Btn_CloseInventory = Cast<UButton>(GetWidgetFromName(TEXT("Btn_CloseInventory")));
	TB_Gold = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Gold")));
	TB_Silver = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Silver")));
	TB_Bronze = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Bronze")));

	if (TB_InvenTitle)
	{
		TB_InvenTitle->SetText(FText::FromString("Inventory"));
	}
	if (Btn_CloseInventory)
	{
		Btn_CloseInventory->OnClicked.AddDynamic(this, &UUWInventory::CloseInventory);
	}
	if (TB_Gold)
	{
		TB_Gold->SetText(FText::FromString("150"));
	}
	if (TB_Silver)
	{
		TB_Silver->SetText(FText::FromString("50"));
	}
	if (TB_Bronze)
	{
		TB_Bronze->SetText(FText::FromString("250"));
	}
}

void UUWInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUWInventory::NativeDestruct()
{
	Super::NativeDestruct();
}

FReply UUWInventory::NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseButtonDown(MyGeometry, MouseEvent);

	return FReply::Handled();
}

bool UUWInventory::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragDropOperation* Operation = Cast<UDragDropOperation>(InOperation);
	UItemObjectData* ItemData = Cast<UItemObjectData>(Operation->Payload);

	//아이템 소환
	mInvenComponent->SetInventoryPacket(ItemData, EInventoryType::Remove);

	return false;
}

void UUWInventory::InitInventory(UACInventoryComponent* InventoryComponent, float TileSize)
{
	mInvenComponent = InventoryComponent;
	mTileSize = TileSize;

	mGridInventory = this->WidgetTree->FindWidget(FName(TEXT("BW_GridInventory")));
	if (mGridInventory != nullptr)
	{
		if (IsValid(mInvenComponent))
		{
			UUWGridInventory* GridInven = Cast<UUWGridInventory>(mGridInventory);
			GridInven->Init(mInvenComponent, mTileSize);
		}
	}

	mEquipmentWindow = this->WidgetTree->FindWidget(FName(TEXT("BW_EquipmentWindow")));
	if (mEquipmentWindow != nullptr)
	{
		if (IsValid(mEquipmentWindow))
		{
			UUWEquipmentWindow* equipmentwindow = Cast<UUWEquipmentWindow>(mEquipmentWindow);
			equipmentwindow->Init(mInvenComponent);
		}
	}
}

void UUWInventory::CloseInventory()
{
	AGM_Game* gamemode = Cast<AGM_Game>(GetWorld()->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}

	APC_Game* playerController = Cast<APC_Game>(gamemode->GetNetworkController());
	if (GetOwningPlayer() != playerController)
	{
		return;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(gamemode->GetClientHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	UW_MainGame* wMainGame = Cast<UW_MainGame>(clientHUD->GetWidgetFromName("MainGame"));

	wMainGame->InventoryOpenRequest();
}

void UUWInventory::RefreshMoney(int32 moneyGold, int32 moneySilver, int32 moneyBronze)
{
	if (TB_Gold)
	{
		TB_Gold->SetText(FText::FromString(FString::FromInt(moneyGold)));
	}
	if (TB_Silver)
	{
		TB_Silver->SetText(FText::FromString(FString::FromInt(moneySilver)));
	}
	if (TB_Bronze)
	{
		TB_Bronze->SetText(FText::FromString(FString::FromInt(moneyBronze)));
	}
}
