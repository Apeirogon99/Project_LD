// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Game/Skill/W_Skill.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UW_Skill::NativeConstruct()
{
	Img_Skill = Cast<UImage>(GetWidgetFromName(TEXT("Img_Skill")));
	TB_KeyBind = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_KeyBind")));
}
