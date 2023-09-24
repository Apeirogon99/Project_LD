// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_BossEnemyHealthBar.generated.h"

/**
 * 
 */
class UProgressBar;
class UTextBlock;

UCLASS()
class PROJECT_LD_API UW_BossEnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* mBossHealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* mName;

public:
	void SetNameText(const FString& inName);

	UFUNCTION(BlueprintCallable)
	void SetEnemyId(const int64 inEnemyId);

public:
	UFUNCTION(BlueprintCallable)
	int64 GetEnemyId();

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int64 mEnemyid;
};
