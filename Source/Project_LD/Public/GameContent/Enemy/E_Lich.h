// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameContent/Enemy/EnemyBase.h"
#include "E_Lich.generated.h"

/**
 * 
 */
class UBoxComponent;

UCLASS()
class PROJECT_LD_API AE_Lich : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	AE_Lich();
	~AE_Lich();

public:
	FORCEINLINE UBoxComponent* GetLichCheckCollider() const { return mLichCheckCollider; }

public:
	void PlayLichAnim(int32 Index);
	void ActiveMultiCastParticle();

	UFUNCTION(BlueprintNativeEvent)
	void OnDisappear();
	virtual void OnDisappear_Implementation();
	
	UFUNCTION(BlueprintNativeEvent)
	void OnAppear();
	virtual void OnAppear_Implementation();

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* mLichCheckCollider;

private:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
