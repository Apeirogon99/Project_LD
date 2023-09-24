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
class AEnemyBase;

UCLASS()
class PROJECT_LD_API UW_BossEnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init(AEnemyBase* InEnemy);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* mBossHealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* mName;

public:
	void SetNameText(const FString& inName);
	void SetEnemy(AEnemyBase* inEnemy);

public:
	UFUNCTION(BlueprintCallable)
	AEnemyBase* GetEnemy() { return mEnemy; }

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	AEnemyBase* mEnemy;
};
