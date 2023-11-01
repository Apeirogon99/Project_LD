// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Skill/W_SkillTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UW_SkillTree::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Reset = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Reset")));
	Btn_Apply = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Apply")));
	Btn_Exit = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Exit")));

	TB_SkillPoints = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_SkillPoints")));
}

void UW_SkillTree::NativeDestruct()
{
	Super::NativeDestruct();
}
