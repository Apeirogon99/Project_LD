// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameContent/Enemy/EnemyBase.h"
#include "E_DarkKnight.generated.h"

/**
 * 
 */
class UNiagaraComponent;

UCLASS()
class PROJECT_LD_API AE_DarkKnight : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	AE_DarkKnight();
	~AE_DarkKnight();

	void PlayDarkKnightAnim(int32 Index);
	void ActiveBerserk();

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DarkKnightBladeParticleActive();
	virtual void DarkKnightBladeParticleActive_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DarkKnightBladeParticleDeactive();
	virtual void DarkKnightBladeParticleDeactive_Implementation();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* mBerserkNiagara;
};
