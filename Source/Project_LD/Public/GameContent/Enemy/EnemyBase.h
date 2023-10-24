// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Struct/Game/EnemyData.h>
#include "Framework/Interface/InteractiveInterface.h"
#include "EnemyBase.generated.h"

class UWidgetComponent;
class UACPointOfInterest;

UCLASS()
class PROJECT_LD_API AEnemyBase : public ACharacter, public IInteractiveInterface
{
	GENERATED_BODY()

public:
	AEnemyBase();
	~AEnemyBase();

public:
	UFUNCTION()
	void UpdateHealthBar();

	UFUNCTION()
	void UpdateMovementSpeed();

public:
	void ChangeState(const EEnemyStateType inStateType, float inStartTime);
	virtual void Interactive(ANC_Game* inPlayer) override; 
	virtual void Init();

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnEnemyHit();
	virtual void OnEnemyHit_Implementation();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;

protected:
	UFUNCTION(BlueprintCallable)
	virtual void SetParticleTemplate(UParticleSystem* InParticleTemplate);

	UFUNCTION(BlueprintCallable)
	virtual void SetParticleLocationAndRotation(const FVector InNewLocation, const FRotator InNewRotation);

	UFUNCTION(BlueprintCallable)
	virtual void SetParticleScale(FVector InNewScale);

	UFUNCTION(BlueprintCallable)
	virtual void HealthBarActive();

	UFUNCTION(BlueprintCallable)
	virtual void HealthBarDeactive();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* mHealthBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* mParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* mSlowParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* mSlowParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UACPointOfInterest* mPOI;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMaterialInstanceDynamic* mHitMaterialInstance;

	bool bSpeedCheck;
};
