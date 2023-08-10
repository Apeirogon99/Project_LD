// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/PS_Game.h"
#include <Handler/ClientHUD.h>
#include <Widget/Game/Inventory/UWInventory.h>
#include <Widget/Game/Item/W_ItemSpace.h>
#include <Widget/Game/Main/W_MainGame.h>

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

float APS_Game::GetHealthBarPercent() const
{
	return mHealthBarPercent;
}

float APS_Game::GetManaBarPercent() const
{
	return mManaBarPercent;
}

float APS_Game::GetExpBarPercent() const
{
	return mExpBarPercent;
}

void APS_Game::UpdateCurrentStats()
{
	//UpdateStats

	UpdateHealthBar();
	UpdateManaBar();
}

void APS_Game::UpdateExpValue(int InExp)
{
	mCurrentExp = StaticCast<float>(InExp);
	UpdateExpBar();
}

void APS_Game::IncreaseExp(float InExp)
{
	mCurrentExp = mCurrentExp + InExp;
	UpdateExpBar();
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
	calculationStats();

	mCharacterStats.SetCurrentStats(mCharacterStats.GetMaxStats());

	UpdateCurrentStats();
}

void APS_Game::InitializeLocalPlayerData()
{
	AGM_Game* gameMode = Cast<AGM_Game>(GetWorld()->GetAuthGameMode());
	if (nullptr == gameMode)
	{
		return;
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

	auto maingame = clientHUD->GetWidgetFromName(TEXT("MainGame"));
	Cast<UW_MainGame>(maingame)->Init();
}

void APS_Game::UpdateHealthBar()
{
	mHealthBarPercent = mCharacterStats.GetCurrentStats().GetHealth() / mCharacterStats.GetMaxStats().GetHealth();
	if (OnCharacterHealthChanged.IsBound())
	{
		OnCharacterHealthChanged.Broadcast();
	}
}

void APS_Game::UpdateManaBar()
{
	mManaBarPercent = mCharacterStats.GetCurrentStats().GetMana() / mCharacterStats.GetMaxStats().GetMana();
	if (OnCharacterManaChanged.IsBound())
	{
		OnCharacterManaChanged.Broadcast();
	}
}

void APS_Game::UpdateExpBar()
{
	ULDGameInstance* Instance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	FLevelDataTable* leveldata = Instance->GetLevelDataTable(mCharacterData.GetLevel() + 1);
	//기본 레벨이 0으로 되있어서 +2 -> +1로 변경예정
	float nextlevelExp = leveldata->next_experience;

	//mExpBarPercent = 55.f / nextlevelExp;
	mExpBarPercent = mCurrentExp / nextlevelExp;
	if (OnCharacterExpChanged.IsBound())
	{
		OnCharacterExpChanged.Broadcast();
	}
}

//void APS_Game::UpdateInventory()
//{
//	AGM_Game* gameMode = Cast<AGM_Game>(GetWorld()->GetAuthGameMode());
//	if (nullptr == gameMode)
//	{
//		return;
//	}
//
//	APC_Game* playercontroller = Cast<APC_Game>(gameMode->GetNetworkController());
//	if (nullptr == playercontroller)
//	{
//		return;
//	}
//
//	AClientHUD* clientHUD = Cast<AClientHUD>(playercontroller->GetHUD());
//	if (nullptr == clientHUD)
//	{
//		return;
//	}
//
//	UUserWidget* widget = clientHUD->GetWidgetFromName(FString(TEXT("Inventory")));
//	if (nullptr == widget)
//	{
//		return;
//	}
//
//	UUWInventory* inventory = Cast<UUWInventory>(widget);
//
//	inventory->UpdateStatus();
//	//GetTBLevel();
//	//GetTBName();
//	//GetTBPower();
//	//GetTBArmor();
//	//GetTBHealth();
//	//GetTBMana();
//	//GetTBDTAttackDamage();
//	//GetTBDTAbilityPower();
//	//GetTBDTAttackSpeed();
//	//GetTBDTCriticalStrikeChance();
//	//GetTBDTCriticalStrikeDamage();
//	//GetTBDTArmorPenetration();
//	//GetTBDTMagePenetration();
//	//GetTBDTAbilityHaste();
//	//GetTBDTMovementSpeed();
//	//GetTBDTRange();
//	//GetTBDTArmor();
//	//GetTBDTTenacity();
//	//GetTBDTMagicResistance();
//	//GetTBDTSlowResist();
//	//GetTBDTHealth();
//	//GetTBDTHealthReneration();
//	//GetTBDTLifeSteal();
//	//GetTBDTPhysicalVamp();
//	//GetTBDTOmnivamp();
//	//GetTBDTHealAndShieldPower();
//	//GetTBDTMana();
//	//GetTBDTManaRegeneration();
//}