// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/Inventory/UWInventory.h"
#include "Game/Inventory/StoreInven/UWGridInventory.h"

#include "Blueprint/WidgetTree.h"
#include "Blueprint/DragDropOperation.h"

#include <Widget/Handler/ClientHUD.h>
#include <Widget/Game/Main/W_MainGame.h>
#include <Widget/Game/Inventory/UWInvenFrame.h>

#include <Game/PS_Game.h>
#include <Game/GM_Game.h>
#include <Game/PC_Game.h>

#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/BackgroundBlur.h"
#include <Component/ACInventoryComponent.h>

#include "Kismet/GameplayStatics.h"

/*
void UUWInventory::NativeConstruct()
{
	Super::NativeConstruct();

	DetailCanvas = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("DetailCanvas")));

	BackgroundBorder = Cast<UBorder>(GetWidgetFromName(TEXT("BackgroundBorder")));
	
	Btn_CloseInventory = Cast<UButton>(GetWidgetFromName(TEXT("Btn_CloseInventory")));
	Btn_DetailStatus = Cast<UButton>(GetWidgetFromName(TEXT("Btn_DetailStatus")));

	TB_Level = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Level")));
	TB_CharacterName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_CharacterName")));
	TB_Power = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Power")));
	TB_Armor = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Armor")));
	TB_Health = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Health")));
	TB_Mana = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Mana")));

	Img_Power = Cast<UImage>(GetWidgetFromName(TEXT("Img_Power")));
	Img_Armor = Cast<UImage>(GetWidgetFromName(TEXT("Img_Armor")));
	Img_Health = Cast<UImage>(GetWidgetFromName(TEXT("Img_Health")));
	Img_Mana = Cast<UImage>(GetWidgetFromName(TEXT("Img_Mana")));

	TB_DTAttackDamage = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTAttackDamage")));
	TB_DTAbilityPower = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTAbilityPower")));
	TB_DTAttackSpeed = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTAttackSpeed")));
	TB_DTCriticalStrikeChance = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTCriticalStrikeChance")));
	TB_DTCriticalStrikeDamage = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTCriticalStrikeDamage")));
	TB_DTArmorPenetration = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTArmorPenetration")));
	TB_DTMagePenetration = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTMagePenetration")));
	TB_DTAbilityHaste = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTAbilityHaste")));
	TB_DTMovementSpeed = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTMovementSpeed")));
	TB_DTRange = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTRange")));
	TB_DTArmor = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTArmor")));
	TB_DTTenacity = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTTenacity")));
	TB_DTMagicResistance = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTMagicResistance")));
	TB_DTSlowResist = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTSlowResist")));
	TB_DTHealth = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTHealth")));
	TB_DTHealthReneration = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTHealthReneration")));
	TB_DTLifeSteal = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTLifeSteal")));
	TB_DTPhysicalVamp = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTPhysicalVamp")));
	TB_DTOmnivamp = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTOmnivamp")));
	TB_DTHealAndShieldPower = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTHealAndShieldPower")));
	TB_DTMana = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTMana")));
	TB_DTManaRegeneration = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_DTManaRegeneration")));

	if (Btn_CloseInventory)
	{
		Btn_CloseInventory->OnClicked.AddDynamic(this, &UUWInventory::CloseInventory);
	}
	if (Btn_DetailStatus)
	{
		Btn_DetailStatus->OnClicked.AddDynamic(this, &UUWInventory::ToggleDetailPanel);
	}

	DetailCanvas->SetVisibility(ESlateVisibility::Hidden);
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
*/
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

	/*
	mInvenFrame = this->WidgetTree->FindWidget(FName(TEXT("BW_InvenFrame")));
	if (mInvenFrame != nullptr)
	{
		if (IsValid(mInvenFrame))
		{
			UUWInvenFrame* InventoryFrame = Cast<UUWInvenFrame>(mInvenFrame);
			InventoryFrame->Init(mInvenComponent);
		}
	}
	*/
}
/*
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

void UUWInventory::ToggleDetailPanel()
{
	if (DetailCanvas->IsVisible())
	{
		DetailCanvas->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		DetailCanvas->SetVisibility(ESlateVisibility::Visible);
	}
}

void UUWInventory::RefreshMoney(int32 money)
{

}

*/