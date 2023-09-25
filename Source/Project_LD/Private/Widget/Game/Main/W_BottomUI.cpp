// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Main/W_BottomUI.h"
#include <Widget/Game/Main/W_PlayerBar.h>
#include <Widget/Game/Skill/W_Skill.h>
#include "Blueprint/WidgetTree.h"

#include <Framework/Game/GM_Game.h>
#include <Framework/Game/PC_Game.h>
#include <Framework/Game/PS_Game.h>

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UW_BottomUI::Init()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}

	APC_Game* controller = Cast<APC_Game>(gamemode->GetNetworkController());
	if (nullptr == controller)
	{
		return;
	}

	APS_Game* playerstate = controller->GetPlayerState<APS_Game>();
	if (playerstate == nullptr)
	{
		return;
	}

	playerstate->OnCharacterHealthChanged.AddUFunction(this, FName(TEXT("UpdateHealthBar")));
	playerstate->OnCharacterManaChanged.AddUFunction(this, FName(TEXT("UpdateManaBar")));

	UpdateHealthBar();
	UpdateManaBar();
}

void UW_BottomUI::UpdateHealthBar()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}

	APC_Game* controller = Cast<APC_Game>(gamemode->GetNetworkController());
	if (nullptr == controller)
	{
		return;
	}

	APS_Game* playerstate = controller->GetPlayerState<APS_Game>();
	if (playerstate == nullptr)
	{
		return;
	}

	UW_PlayerBar* playerBar = Cast<UW_PlayerBar>(mPlayerBar);
	if (playerBar == nullptr)
	{
		return;
	}

	float CurrentHealthPercent = playerstate->GetCharacterStats().GetCurrentStats().GetHealth();
	float MaxHealthPercent = playerstate->GetCharacterStats().GetMaxStats().GetHealth();
	float HealthPercent = CurrentHealthPercent / MaxHealthPercent;

	playerBar->HealthBar->SetPercent(HealthPercent);
}

void UW_BottomUI::UpdateManaBar()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	ANetworkGameMode* gamemode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}

	APC_Game* controller = Cast<APC_Game>(gamemode->GetNetworkController());
	if (nullptr == controller)
	{
		return;
	}

	APS_Game* playerstate = controller->GetPlayerState<APS_Game>();
	if (playerstate == nullptr)
	{
		return;
	}

	UW_PlayerBar* playerBar = Cast<UW_PlayerBar>(mPlayerBar);
	if (playerBar == nullptr)
	{
		return;
	}

	float CurrentManaPercent = playerstate->GetCharacterStats().GetCurrentStats().GetMana();
	float MaxManaPercent = playerstate->GetCharacterStats().GetMaxStats().GetMana();
	float ManaPercent = CurrentManaPercent / MaxManaPercent;

	playerBar->ManaBar->SetPercent(ManaPercent);
}

void UW_BottomUI::NativeConstruct()
{

}

void UW_BottomUI::NativePreConstruct()
{
	UTexture2D* T_SKILL_Q = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/GameContent/WidgetAssets/T_Skill_Q.T_Skill_Q'")));
	if (T_SKILL_Q)
	{
		mSkillTextureArray.Add(T_SKILL_Q);
	}
	UTexture2D* T_SKILL_W = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/GameContent/WidgetAssets/T_Skill_W.T_Skill_W'")));
	if (T_SKILL_W)
	{
		mSkillTextureArray.Add(T_SKILL_W);
	}
	UTexture2D* T_SKILL_E = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/GameContent/WidgetAssets/T_Skill_E.T_Skill_E'")));
	if (T_SKILL_E)
	{
		mSkillTextureArray.Add(T_SKILL_E);
	}
	UTexture2D* T_SKILL_R = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/GameContent/WidgetAssets/T_Skill_R.T_Skill_R'")));
	if (T_SKILL_R)
	{
		mSkillTextureArray.Add(T_SKILL_R);
	}
	UTexture2D* T_SKILL_Dash = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/NhanceRPGSpells/NhanceRPGSpells/Textures/T_Icon_Nature_206.T_Icon_Nature_206'")));
	if (T_SKILL_Dash)
	{
		mSkillTextureArray.Add(T_SKILL_Dash);
	}
	UTexture2D* T_ItemPotion1 = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/CraftResourcesIcons/Textures/Tex_reagent_12_b.Tex_reagent_12_b'")));
	if (T_ItemPotion1)
	{
		mSkillTextureArray.Add(T_ItemPotion1);
	}
	UTexture2D* T_ItemPotion2 = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/CraftResourcesIcons/Textures/Tex_reagent_06_b.Tex_reagent_06_b'")));
	if (T_ItemPotion2)
	{
		mSkillTextureArray.Add(T_ItemPotion2);
	}

	mPlayerBar = this->WidgetTree->FindWidget(FName(TEXT("BW_PlayerBar")));
	if (mPlayerBar == nullptr)
	{
		return;
	}

	mSkill_Q = this->WidgetTree->FindWidget(FName(TEXT("BW_Skill_Q")));
	if (mSkill_Q == nullptr)
	{
		return;
	}

	mSkill_W = this->WidgetTree->FindWidget(FName(TEXT("BW_Skill_W")));
	if (mSkill_W == nullptr)
	{
		return;
	}

	mSkill_E = this->WidgetTree->FindWidget(FName(TEXT("BW_Skill_E")));
	if (mSkill_E == nullptr)
	{
		return;
	}

	mSkill_R = this->WidgetTree->FindWidget(FName(TEXT("BW_Skill_R")));
	if (mSkill_R == nullptr)
	{
		return;
	}

	mSkill_BasicAttack = this->WidgetTree->FindWidget(FName(TEXT("BW_Skill_BasicAttack")));
	if (mSkill_BasicAttack == nullptr)
	{
		return;
	}

	mSkill_UseItem1 = this->WidgetTree->FindWidget(FName(TEXT("BW_UseItem1")));
	if (mSkill_UseItem1 == nullptr)
	{
		return;
	}

	mSkill_UseItem2 = this->WidgetTree->FindWidget(FName(TEXT("BW_UseItem2")));
	if (mSkill_UseItem2 == nullptr)
	{
		return;
	}

	Cast<UW_Skill>(mSkill_Q)->TB_KeyBind->SetText(FText::FromString(TEXT("Q")));
	Cast<UW_Skill>(mSkill_W)->TB_KeyBind->SetText(FText::FromString(TEXT("W")));
	Cast<UW_Skill>(mSkill_E)->TB_KeyBind->SetText(FText::FromString(TEXT("E")));
	Cast<UW_Skill>(mSkill_R)->TB_KeyBind->SetText(FText::FromString(TEXT("R")));
	Cast<UW_Skill>(mSkill_BasicAttack)->TB_KeyBind->SetText(FText::FromString(TEXT("Ctrl")));
	Cast<UW_Skill>(mSkill_UseItem1)->TB_KeyBind->SetText(FText::FromString(TEXT("1")));
	Cast<UW_Skill>(mSkill_UseItem2)->TB_KeyBind->SetText(FText::FromString(TEXT("2")));

	Cast<UW_Skill>(mSkill_Q)->Img_Skill->SetBrushFromTexture(mSkillTextureArray[0]);
	Cast<UW_Skill>(mSkill_W)->Img_Skill->SetBrushFromTexture(mSkillTextureArray[1]);
	Cast<UW_Skill>(mSkill_E)->Img_Skill->SetBrushFromTexture(mSkillTextureArray[2]);
	Cast<UW_Skill>(mSkill_R)->Img_Skill->SetBrushFromTexture(mSkillTextureArray[3]);
	Cast<UW_Skill>(mSkill_BasicAttack)->Img_Skill->SetBrushFromTexture(mSkillTextureArray[4]);
	Cast<UW_Skill>(mSkill_UseItem1)->Img_Skill->SetBrushFromTexture(mSkillTextureArray[5]);
	Cast<UW_Skill>(mSkill_UseItem2)->Img_Skill->SetBrushFromTexture(mSkillTextureArray[6]);
}

void UW_BottomUI::NativeDestruct()
{
	mSkillTextureArray.Empty();
}
