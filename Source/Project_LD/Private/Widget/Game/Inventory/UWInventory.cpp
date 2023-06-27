// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/Inventory/UWInventory.h"
#include "Game/Inventory/StoreInven/UWGridInventory.h"
#include <Widget/Game/Item/W_ItemSpace.h>

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/DragDropOperation.h"

#include <Widget/Handler/ClientHUD.h>
#include <Widget/Game/Main/W_MainGame.h>
#include <Widget/Game/Inventory/UWInvenFrame.h>

#include <Game/GM_Game.h>
#include <Game/PC_Game.h>

#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/BackgroundBlur.h"
#include <Component/ACInventoryComponent.h>

#include "Kismet/GameplayStatics.h"

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

	if (Btn_CloseInventory != nullptr)
	{
		Btn_CloseInventory->OnClicked.AddDynamic(this, &UUWInventory::CloseInventory);
	}
	else
	{
		return;
	}
	if (Btn_DetailStatus != nullptr)
	{
		Btn_DetailStatus->OnClicked.AddDynamic(this, &UUWInventory::ToggleDetailPanel);
	}
	else
	{
		return;
	}

	DetailCanvas->SetVisibility(ESlateVisibility::Hidden);
	BackgroundBorder->SetVisibility(ESlateVisibility::Visible);
}

void UUWInventory::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UUWInventory::NativeDestruct()
{
	Super::NativeDestruct();
	/*
	if (TB_Level->TextDelegate.IsBound())
	{
		TB_Level->TextDelegate.Clear();
	}	
	if (TB_CharacterName->TextDelegate.IsBound())
	{
		TB_CharacterName->TextDelegate.Clear();
	}
	
	if (TB_Power->TextDelegate.IsBound()) 
	{
		TB_Power->TextDelegate.Clear();
	}
	if(TB_Armor->TextDelegate.IsBound())
	{
		TB_Armor->TextDelegate.Clear();
	}
	if(TB_Health->TextDelegate.IsBound())
	{
		TB_Health->TextDelegate.Clear();
	}
	if(TB_Mana->TextDelegate.IsBound())
	{
		TB_Mana->TextDelegate.Clear();
	}

	if(TB_DTAttackDamage->TextDelegate.IsBound())
	{
		TB_DTAttackDamage->TextDelegate.Clear();
	}
	if(TB_DTAttackDamage->TextDelegate.IsBound())
	{
		TB_DTAbilityPower->TextDelegate.Clear();
	}
	if(TB_DTAttackSpeed->TextDelegate.IsBound())
	{
		TB_DTAttackSpeed->TextDelegate.Clear();
	}
	if(TB_DTCriticalStrikeChance->TextDelegate.IsBound())
	{
		TB_DTCriticalStrikeChance->TextDelegate.Clear();
	}
	if(TB_DTCriticalStrikeDamage->TextDelegate.IsBound())
	{
		TB_DTCriticalStrikeDamage->TextDelegate.Clear();
	}
	if(TB_DTArmorPenetration->TextDelegate.IsBound())
	{
		TB_DTArmorPenetration->TextDelegate.Clear();
	}
	if(TB_DTMagePenetration->TextDelegate.IsBound())
	{
		TB_DTMagePenetration->TextDelegate.Clear();
	}
	if(TB_DTAbilityHaste->TextDelegate.IsBound())
	{
		TB_DTAbilityHaste->TextDelegate.Clear();
	}
	if(TB_DTMovementSpeed->TextDelegate.IsBound())
	{
		TB_DTMovementSpeed->TextDelegate.Clear();
	}
	if(TB_DTRange->TextDelegate.IsBound())
	{
		TB_DTRange->TextDelegate.Clear();
	}

	if(TB_DTArmor->TextDelegate.IsBound())
	{
		TB_DTArmor->TextDelegate.Clear();
	}
	if(TB_DTTenacity->TextDelegate.IsBound())
	{
		TB_DTTenacity->TextDelegate.Clear();
	}
	if(TB_DTMagicResistance->TextDelegate.IsBound())
	{
		TB_DTMagicResistance->TextDelegate.Clear();
	}
	if(TB_DTSlowResist->TextDelegate.IsBound())
	{
		TB_DTSlowResist->TextDelegate.Clear();
	}

	if(TB_DTHealth->TextDelegate.IsBound())
	{
		TB_DTHealth->TextDelegate.Clear();
	}
	if(TB_DTHealthReneration->TextDelegate.IsBound())
	{
		TB_DTHealthReneration->TextDelegate.Clear();
	}
	if(TB_DTLifeSteal->TextDelegate.IsBound())
	{
		TB_DTLifeSteal->TextDelegate.Clear();
	}
	if(TB_DTPhysicalVamp->TextDelegate.IsBound())
	{
		TB_DTPhysicalVamp->TextDelegate.Clear();
	}
	if(TB_DTOmnivamp->TextDelegate.IsBound())
	{
		TB_DTOmnivamp->TextDelegate.Clear();
	}
	if(TB_DTHealAndShieldPower->TextDelegate.IsBound())
	{
		TB_DTHealAndShieldPower->TextDelegate.Clear();
	}

	if(TB_DTMana->TextDelegate.IsBound())
	{
		TB_DTMana->TextDelegate.Clear();
	}
	if(TB_DTManaRegeneration->TextDelegate.IsBound())
	{
		TB_DTManaRegeneration->TextDelegate.Clear();
	}
	*/
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
	UItemObjectData* ItemObejctData = Cast<UItemObjectData>(Operation->Payload);

	if (IsValid(ItemObejctData))
	{
		if (ItemObejctData->IsValid())
		{
			if (ItemObejctData->Type == EItemObjectType::Inventory)
			{
				mInvenComponent->SetInventoryPacket(ItemObejctData, EInventoryType::Remove);
			}
			else if (ItemObejctData->Type == EItemObjectType::Equipment)
			{
				int Index = ItemObejctData->ItemData.category_id - 1;

				mEquipmentComponent->GetEquipmentObjectData()[Index] = ItemObejctData;
				mEquipmentComponent->GetEquipmentWidget()[Index]->ReMakeWidget(ItemObejctData);
			}
		}
	}

	mEquipmentComponent->DropItemWidget();

	return true;
}

bool UUWInventory::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);

	UDragDropOperation* Operation = Cast<UDragDropOperation>(InOperation);
	UItemObjectData* ItemObjectData = Cast<UItemObjectData>(Operation->Payload);

	if (IsValid(ItemObjectData))
	{
		if(ItemObjectData->IsValid())
		{
			mEquipmentComponent->CanItemDropWidgetCheck(ItemObjectData);
		}
	}

	return true;
}

void UUWInventory::InitInventory(UACInventoryComponent* InventoryComponent, float TileSize, UACEquipment* EquipmentComponent)
{
	mInvenComponent = InventoryComponent;
	mTileSize = TileSize;
	mEquipmentComponent = EquipmentComponent;

	if (mInvenComponent == nullptr)
	{
		return;
	}
	if (mEquipmentComponent == nullptr)
	{
		return;
	}
	if (mTileSize <= 0)
	{
		return;
	}

	mGridInventory = this->WidgetTree->FindWidget(FName(TEXT("BW_GridInventory")));
	if (mGridInventory != nullptr)
	{
		if (IsValid(mInvenComponent))
		{
			UUWGridInventory* GridInven = Cast<UUWGridInventory>(mGridInventory);
			GridInven->Init(mInvenComponent, mTileSize, mEquipmentComponent);
		}
	}

	mInvenFrame = this->WidgetTree->FindWidget(FName(TEXT("BW_InvenFrame")));
	if (mInvenFrame != nullptr)
	{
		if (IsValid(mInvenFrame))
		{
			UUWInvenFrame* InventoryFrame = Cast<UUWInvenFrame>(mInvenFrame);
			InventoryFrame->Init(mInvenComponent, mEquipmentComponent);
		}
	}

	mEquipHelmet = this->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceHelmet")));
	if (mEquipHelmet != nullptr)
	{
		if (IsValid(mEquipHelmet))
		{
			UW_ItemSpace* EquipHelmet = Cast<UW_ItemSpace>(mEquipHelmet);
			EquipHelmet->Init(mInvenComponent, mEquipmentComponent);
		}
	}

	mEquipShoulders = this->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceShoulders")));
	if (mEquipShoulders != nullptr)
	{
		if (IsValid(mEquipShoulders))
		{
			UW_ItemSpace* EquipShoudler = Cast<UW_ItemSpace>(mEquipShoulders);
			EquipShoudler->Init(mInvenComponent, mEquipmentComponent);
		}
	}

	mEquipChest = this->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceChest")));
	if (mEquipChest != nullptr)
	{
		if (IsValid(mEquipChest))
		{
			UW_ItemSpace* EquipChest = Cast<UW_ItemSpace>(mEquipChest);
			EquipChest->Init(mInvenComponent, mEquipmentComponent);
		}
	}

	mEquipBracers = this->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceBracers")));
	if (mEquipBracers != nullptr)
	{
		if (IsValid(mEquipBracers))
		{
			UW_ItemSpace* EquipBracers = Cast<UW_ItemSpace>(mEquipBracers);
			EquipBracers->Init(mInvenComponent, mEquipmentComponent);
		}
	}

	mEquipHands = this->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceHands")));
	if (mEquipHands != nullptr)
	{
		if (IsValid(mEquipHands))
		{
			UW_ItemSpace* EquipHands = Cast<UW_ItemSpace>(mEquipHands);
			EquipHands->Init(mInvenComponent, mEquipmentComponent);
		}
	}

	mEquipPants = this->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpacePants")));
	if (mEquipPants != nullptr)
	{
		if (IsValid(mEquipPants))
		{
			UW_ItemSpace* EquipPants = Cast<UW_ItemSpace>(mEquipPants);
			EquipPants->Init(mInvenComponent, mEquipmentComponent);
		}
	}

	mEquipBoots = this->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceBoots")));
	if (mEquipBoots != nullptr)
	{
		if (IsValid(mEquipBoots))
		{
			UW_ItemSpace* EquipBoots = Cast<UW_ItemSpace>(mEquipBoots);
			EquipBoots->Init(mInvenComponent, mEquipmentComponent);
		}
	}

	mEquipLeftWeapon = this->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceLeftWeapon")));
	if (mEquipLeftWeapon != nullptr)
	{
		if (IsValid(mEquipLeftWeapon))
		{
			UW_ItemSpace* EquipLeftWeapon = Cast<UW_ItemSpace>(mEquipLeftWeapon);
			EquipLeftWeapon->Init(mInvenComponent, mEquipmentComponent);
		}
	}

	mEquipRightWeapon = this->WidgetTree->FindWidget(FName(TEXT("BW_ItemSpaceRightWeapon")));
	if (mEquipRightWeapon != nullptr)
	{
		if (IsValid(mEquipRightWeapon))
		{
			UW_ItemSpace* EquipRightWeapon = Cast<UW_ItemSpace>(mEquipRightWeapon);
			EquipRightWeapon->Init(mInvenComponent, mEquipmentComponent);
		}
	}

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

	mPlayerState = playerController->GetPlayerState<APS_Game>();
	if (mPlayerState == nullptr)
	{
		return;
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
	if (wMainGame)
	{
		wMainGame->InventoryOpenRequest();
	}
}

void UUWInventory::ToggleDetailPanel()
{
	if (DetailCanvas)
	{
		if (DetailCanvas->IsVisible())
		{
			DetailCanvas->SetVisibility(ESlateVisibility::Hidden);
			UCanvasPanelSlot* FrameCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(mInvenFrame);
			if (FrameCanvasSlot)
			{
				FrameCanvasSlot->SetSize(FVector2D(680.f, 0.f));
			}
		}
		else
		{
			DetailCanvas->SetVisibility(ESlateVisibility::Visible);
			UCanvasPanelSlot* FrameCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(mInvenFrame);
			if (FrameCanvasSlot)
			{
				FrameCanvasSlot->SetSize(FVector2D(1000.f, 0.f));
			}
		}
	}
}

/*
void UUWInventory::UpdateStatus()
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

	APS_Game* playerstate = playerController->GetPlayerState<APS_Game>();
	if (nullptr == playerstate)
	{
		return;
	}

	const FCharacterData characterData = playerstate->GetCharacterData();
	const FCharacterStats characterStats = playerstate->GetCharacterStatus();
	const FStatusData Stats = characterStats.mMaxStatus;

	TB_Level->SetText(FText::FromString(FString::FromInt(characterData.mLevel)));
	TB_CharacterName->SetText(FText::FromString(characterData.mName));

	TB_Power->SetText(FText::FromString(FString::SanitizeFloat(Stats.ability_power)));
	TB_Armor->SetText(FText::FromString(FString::SanitizeFloat(Stats.armor)));
	TB_Health->SetText(FText::FromString(FString::SanitizeFloat(Stats.health)));
	TB_Mana->SetText(FText::FromString(FString::SanitizeFloat(Stats.mana)));

	TB_DTAttackDamage->SetText(FText::FromString(FString::SanitizeFloat(Stats.attack_damage)));
	TB_DTAbilityPower->SetText(FText::FromString(FString::SanitizeFloat(Stats.ability_power)));
	TB_DTAttackSpeed->SetText(FText::FromString(FString::SanitizeFloat(Stats.attack_speed)));
	TB_DTCriticalStrikeChance->SetText(FText::FromString(FString::SanitizeFloat(Stats.critical_strike_chance)));
	TB_DTCriticalStrikeDamage->SetText(FText::FromString(FString::SanitizeFloat(Stats.cirtical_strike_damage)));
	TB_DTArmorPenetration->SetText(FText::FromString(FString::SanitizeFloat(Stats.armor_penetration)));
	TB_DTMagePenetration->SetText(FText::FromString(FString::SanitizeFloat(Stats.mage_penetration)));
	TB_DTAbilityHaste->SetText(FText::FromString(FString::SanitizeFloat(Stats.ability_haste)));
	TB_DTMovementSpeed->SetText(FText::FromString(FString::SanitizeFloat(Stats.movement_speed)));
	TB_DTRange->SetText(FText::FromString(FString::SanitizeFloat(Stats.range)));

	TB_DTArmor->SetText(FText::FromString(FString::SanitizeFloat(Stats.armor)));
	TB_DTTenacity->SetText(FText::FromString(FString::SanitizeFloat(Stats.tenacity)));
	TB_DTMagicResistance->SetText(FText::FromString(FString::SanitizeFloat(Stats.magic_resistance)));
	TB_DTSlowResist->SetText(FText::FromString(FString::SanitizeFloat(Stats.slow_resist)));

	TB_DTHealth->SetText(FText::FromString(FString::SanitizeFloat(Stats.health)));
	TB_DTHealthReneration->SetText(FText::FromString(FString::SanitizeFloat(Stats.health_regeneration)));
	TB_DTLifeSteal->SetText(FText::FromString(FString::SanitizeFloat(Stats.life_steal)));
	TB_DTPhysicalVamp->SetText(FText::FromString(FString::SanitizeFloat(Stats.physical_vamp)));
	TB_DTOmnivamp->SetText(FText::FromString(FString::SanitizeFloat(Stats.omnivamp)));
	TB_DTHealAndShieldPower->SetText(FText::FromString(FString::SanitizeFloat(Stats.heal_and_shield_power)));

	TB_DTMana->SetText(FText::FromString(FString::SanitizeFloat(Stats.mana)));
	TB_DTManaRegeneration->SetText(FText::FromString(FString::SanitizeFloat(Stats.mana_regeneration)));
}

void UUWInventory::UpdateStatus()
{
	if (TB_Level->TextDelegate.IsBound())
	{
		TB_Level->TextDelegate.Execute();
	}
	if (TB_CharacterName->TextDelegate.IsBound())
	{
		TB_CharacterName->TextDelegate.Execute();
	}

	if (TB_Power->TextDelegate.IsBound())
	{
		TB_Power->TextDelegate.Execute();
	}
	if (TB_Armor->TextDelegate.IsBound())
	{
		TB_Armor->TextDelegate.Execute();
	}
	if (TB_Health->TextDelegate.IsBound())
	{
		TB_Health->TextDelegate.Execute();
	}
	if (TB_Mana->TextDelegate.IsBound())
	{
		TB_Mana->TextDelegate.Execute();
	}

	if (TB_DTAttackDamage->TextDelegate.IsBound())
	{
		TB_DTAttackDamage->TextDelegate.Execute();
	}
	if (TB_DTAttackDamage->TextDelegate.IsBound())
	{
		TB_DTAbilityPower->TextDelegate.Execute();
	}
	if (TB_DTAttackSpeed->TextDelegate.IsBound())
	{
		TB_DTAttackSpeed->TextDelegate.Execute();
	}
	if (TB_DTCriticalStrikeChance->TextDelegate.IsBound())
	{
		TB_DTCriticalStrikeChance->TextDelegate.Execute();
	}
	if (TB_DTCriticalStrikeDamage->TextDelegate.IsBound())
	{
		TB_DTCriticalStrikeDamage->TextDelegate.Execute();
	}
	if (TB_DTArmorPenetration->TextDelegate.IsBound())
	{
		TB_DTArmorPenetration->TextDelegate.Execute();
	}
	if (TB_DTMagePenetration->TextDelegate.IsBound())
	{
		TB_DTMagePenetration->TextDelegate.Execute();
	}
	if (TB_DTAbilityHaste->TextDelegate.IsBound())
	{
		TB_DTAbilityHaste->TextDelegate.Execute();
	}
	if (TB_DTMovementSpeed->TextDelegate.IsBound())
	{
		TB_DTMovementSpeed->TextDelegate.Execute();
	}
	if (TB_DTRange->TextDelegate.IsBound())
	{
		TB_DTRange->TextDelegate.Execute();
	}

	if (TB_DTArmor->TextDelegate.IsBound())
	{
		TB_DTArmor->TextDelegate.Execute();
	}
	if (TB_DTTenacity->TextDelegate.IsBound())
	{
		TB_DTTenacity->TextDelegate.Execute();
	}
	if (TB_DTMagicResistance->TextDelegate.IsBound())
	{
		TB_DTMagicResistance->TextDelegate.Execute();
	}
	if (TB_DTSlowResist->TextDelegate.IsBound())
	{
		TB_DTSlowResist->TextDelegate.Execute();
	}

	if (TB_DTHealth->TextDelegate.IsBound())
	{
		TB_DTHealth->TextDelegate.Execute();
	}
	if (TB_DTHealthReneration->TextDelegate.IsBound())
	{
		TB_DTHealthReneration->TextDelegate.Execute();
	}
	if (TB_DTLifeSteal->TextDelegate.IsBound())
	{
		TB_DTLifeSteal->TextDelegate.Execute();
	}
	if (TB_DTPhysicalVamp->TextDelegate.IsBound())
	{
		TB_DTPhysicalVamp->TextDelegate.Execute();
	}
	if (TB_DTOmnivamp->TextDelegate.IsBound())
	{
		TB_DTOmnivamp->TextDelegate.Execute();
	}
	if (TB_DTHealAndShieldPower->TextDelegate.IsBound())
	{
		TB_DTHealAndShieldPower->TextDelegate.Execute();
	}

	if (TB_DTMana->TextDelegate.IsBound())
	{
		TB_DTMana->TextDelegate.Execute();
	}
	if (TB_DTManaRegeneration->TextDelegate.IsBound())
	{
		TB_DTManaRegeneration->TextDelegate.Execute();
	}
}

void UUWInventory::InitStatus()
{
	TB_Level->TextDelegate.BindUFunction(this, "GetTBLevel");
	TB_CharacterName->TextDelegate.BindUFunction(this, "GetTBName");

	TB_Power->TextDelegate.BindUFunction(this,"GetTBPower");
	TB_Armor->TextDelegate.BindUFunction(this,"GetTBArmor");
	TB_Health->TextDelegate.BindUFunction(this,"GetTBHealth");
	TB_Mana->TextDelegate.BindUFunction(this,"GetTBMana");

	TB_DTAttackDamage->TextDelegate.BindUFunction(this,"GetTBDTAttackDamage");
	TB_DTAbilityPower->TextDelegate.BindUFunction(this,"GetTBDTAbilityPower");
	TB_DTAttackSpeed->TextDelegate.BindUFunction(this,"GetTBDTAttackSpeed");
	TB_DTCriticalStrikeChance->TextDelegate.BindUFunction(this,"GetTBDTCriticalStrikeChance");
	TB_DTCriticalStrikeDamage->TextDelegate.BindUFunction(this,"GetTBDTCriticalStrikeDamage");
	TB_DTArmorPenetration->TextDelegate.BindUFunction(this,"GetTBDTArmorPenetration");
	TB_DTMagePenetration->TextDelegate.BindUFunction(this, "GetTBDTMagePenetration");
	TB_DTAbilityHaste->TextDelegate.BindUFunction(this,"GetTBDTAbilityHaste");
	TB_DTMovementSpeed->TextDelegate.BindUFunction(this,"GetTBDTMovementSpeed");
	TB_DTRange->TextDelegate.BindUFunction(this,"GetTBDTRange");

	TB_DTArmor->TextDelegate.BindUFunction(this,"GetTBDTArmor");
	TB_DTTenacity->TextDelegate.BindUFunction(this,"GetTBDTTenacity");
	TB_DTMagicResistance->TextDelegate.BindUFunction(this,"GetTBDTMagicResistance");
	TB_DTSlowResist->TextDelegate.BindUFunction(this,"GetTBDTSlowResist");

	TB_DTHealth->TextDelegate.BindUFunction(this,"GetTBDTHealth");
	TB_DTHealthReneration->TextDelegate.BindUFunction(this,"GetTBDTHealthReneration");
	TB_DTLifeSteal->TextDelegate.BindUFunction(this,"GetTBDTLifeSteal");
	TB_DTPhysicalVamp->TextDelegate.BindUFunction(this,"GetTBDTPhysicalVamp");
	TB_DTOmnivamp->TextDelegate.BindUFunction(this,"GetTBDTOmnivamp");
	TB_DTHealAndShieldPower->TextDelegate.BindUFunction(this,"GetTBDTHealAndShieldPower");

	TB_DTMana->TextDelegate.BindUFunction(this,"GetTBDTMana");
	TB_DTManaRegeneration->TextDelegate.BindUFunction(this,"GetTBDTManaRegeneration");
}
*/

void UUWInventory::RefreshMoney(int32 money)
{

}