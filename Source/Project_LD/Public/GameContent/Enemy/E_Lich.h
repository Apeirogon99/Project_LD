// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameContent/Enemy/EnemyBase.h"
#include "E_Lich.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AE_Lich : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	AE_Lich();
	~AE_Lich();

public:
	void PlayLichAnim(int32 Index);
	void ActiveMultiCastParticle();

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* mRightMultiCastParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* mLeftMultiCastParticle;
};
