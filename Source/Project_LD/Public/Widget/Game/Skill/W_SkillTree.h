// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SkillTree.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;

UCLASS()
class PROJECT_LD_API UW_SkillTree : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_Reset;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_Apply;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* Btn_Exit;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TB_SkillPoints;

protected:
	void NativeConstruct() override;
	void NativeDestruct() override;
};
