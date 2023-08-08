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

	AGM_Game* gamemode = Cast<AGM_Game>(world->GetAuthGameMode());
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

	AGM_Game* gamemode = Cast<AGM_Game>(world->GetAuthGameMode());
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

	playerBar->HealthBar->SetPercent(playerstate->GetHealthBarPercent());
}

void UW_BottomUI::UpdateManaBar()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	AGM_Game* gamemode = Cast<AGM_Game>(world->GetAuthGameMode());
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

	playerBar->ManaBar->SetPercent(playerstate->GetManaBarPercent());
}

void UW_BottomUI::NativeConstruct()
{

}

void UW_BottomUI::NativePreConstruct()
{
	UTexture2D* T_SKILL_Q = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Test/T_Icon_Gold_145.T_Icon_Gold_145'")));
	if (T_SKILL_Q)
	{
		mSkillTextureArray.Add(T_SKILL_Q);
	}
	UTexture2D* T_SKILL_W = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Test/Fantasy_Game_Skills_Icon_2_-_Tornado_Slash_level_2.Fantasy_Game_Skills_Icon_2_-_Tornado_Slash_level_2'")));
	if (T_SKILL_W)
	{
		mSkillTextureArray.Add(T_SKILL_W);
	}
	UTexture2D* T_SKILL_E = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Test/T_Icon_Gold_147.T_Icon_Gold_147'")));
	if (T_SKILL_E)
	{
		mSkillTextureArray.Add(T_SKILL_E);
	}
	UTexture2D* T_SKILL_R = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("Texture2D'/Game/Test/Fantasy_Game_Skills_Icon_2_-_Side_Slash_level_3.Fantasy_Game_Skills_Icon_2_-_Side_Slash_level_3'")));
	if (T_SKILL_R)
	{
		mSkillTextureArray.Add(T_SKILL_R);
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
	Cast<UW_Skill>(mSkill_BasicAttack)->TB_KeyBind->SetText(FText::FromString(TEXT("0")));
	Cast<UW_Skill>(mSkill_UseItem1)->TB_KeyBind->SetText(FText::FromString(TEXT("1")));
	Cast<UW_Skill>(mSkill_UseItem2)->TB_KeyBind->SetText(FText::FromString(TEXT("2")));

	Cast<UW_Skill>(mSkill_Q)->Img_Skill->SetBrushFromTexture(mSkillTextureArray[0]);
	Cast<UW_Skill>(mSkill_W)->Img_Skill->SetBrushFromTexture(mSkillTextureArray[1]);
	Cast<UW_Skill>(mSkill_E)->Img_Skill->SetBrushFromTexture(mSkillTextureArray[2]);
	Cast<UW_Skill>(mSkill_R)->Img_Skill->SetBrushFromTexture(mSkillTextureArray[3]);
	Cast<UW_Skill>(mSkill_BasicAttack)->Img_Skill->SetBrushFromTexture(mSkillTextureArray[0]);
	Cast<UW_Skill>(mSkill_UseItem1)->Img_Skill->SetBrushFromTexture(mSkillTextureArray[1]);
	Cast<UW_Skill>(mSkill_UseItem2)->Img_Skill->SetBrushFromTexture(mSkillTextureArray[2]);
}

void UW_BottomUI::NativeDestruct()
{
	mSkillTextureArray.Empty();
}
