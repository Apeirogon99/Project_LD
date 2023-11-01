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

	TB_Money = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Money")));

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
		Btn_CloseInventory->OnClicked.AddUniqueDynamic(this, &UUWInventory::CloseInventory);
	}
	else
	{
		return;
	}
	if (Btn_DetailStatus != nullptr)
	{
		Btn_DetailStatus->OnClicked.AddUniqueDynamic(this, &UUWInventory::ToggleDetailPanel);
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
	
	UE_LOG(LogTemp, Warning, TEXT("Widget Destruct Called"));

	if (Btn_CloseInventory->OnClicked.IsBound())
	{
		Btn_CloseInventory->OnClicked.Clear();
	}

	if (Btn_DetailStatus->OnClicked.IsBound())
	{
		Btn_DetailStatus->OnClicked.Clear();
	}

	if (mInvenComponent == nullptr)
	{
		return;
	}

	if (mInvenComponent->OnMoneyChanged.IsBound())
	{
		mInvenComponent->OnMoneyChanged.Unbind();
		mInvenComponent = nullptr;
	}
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
			if (ItemObejctData->GetType() == EItemObjectType::Inventory)
			{
				mInvenComponent->SetInventoryPacket(ItemObejctData, EInventoryType::Remove);
			}
			else if (ItemObejctData->GetType() == EItemObjectType::Equipment)
			{
				int Index = ItemObejctData->GetItemData().GetCategoryID() - 1;

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

	InventoryComponent->OnMoneyChanged.BindUFunction(this, FName("UpdateMoney"));

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

	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}

	APC_Game* playerController = Cast<APC_Game>(gamemode->GetNetworkController());
	if (GetOwningPlayer() != playerController)
	{
		return;
	}

	//APS_Game* playerState = playerController->GetPlayerState<APS_Game>();
	//if (playerState == nullptr)
	//{
	//	return;
	//}
	//mPlayerState = playerState;

	//mPlayerState = playerController->GetPlayerState<APS_Game>();
	//if (mPlayerState == nullptr)
	//{
	//	return;
	//}
}

void UUWInventory::CloseInventory()
{
	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(GetWorld()->GetAuthGameMode());
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

void UUWInventory::UpdateMoney()
{
	if (mInvenComponent == nullptr)
	{
		return;
	}

	TB_Money->SetText(FText::FromString(FString::FromInt(mInvenComponent->GetMoney())));
}