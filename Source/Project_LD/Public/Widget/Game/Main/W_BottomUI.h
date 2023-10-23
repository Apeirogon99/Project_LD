// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_BottomUI.generated.h"

/**
 * 
 */
class UTexture2D;

UCLASS()
class PROJECT_LD_API UW_BottomUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init();

public:
	UFUNCTION()
	void UpdateHealthBar();

	UFUNCTION()
	void UpdateManaBar();

	void SetWidgetCoolTime(const TArray<int32>& inSkillID, const TArray<int64>& inSkillDuration);

public:
	UPROPERTY()
	UWidget* mPlayerBar;

	UPROPERTY()
	UWidget* mSkill_Q;

	UPROPERTY()
	UWidget* mSkill_W;

	UPROPERTY()
	UWidget* mSkill_E;

	UPROPERTY()
	UWidget* mSkill_R;

	UPROPERTY()
	UWidget* mSkill_BasicAttack;

	UPROPERTY()
	UWidget* mSkill_UseItem1;

	UPROPERTY()
	UWidget* mSkill_UseItem2;

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY()
	TArray<UTexture2D*> mSkillTextureArray;
};
