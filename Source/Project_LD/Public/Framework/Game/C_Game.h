// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/ACInventoryComponent.h"
#include "Framework/Character/AppearanceCharacter.h"
#include "NC_Game.h"
#include "C_Game.generated.h"

/**
 * 
 */
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PROJECT_LD_API AC_Game : public ANC_Game
{
	GENERATED_BODY()

public:
	AC_Game();
	~AC_Game();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Destroyed() override;

public:
	void SetIsZoom(const bool& InIsZoom) { bIsZoom = InIsZoom; }
	void SetIsAttack(const bool& InIsAttack) { bIsAttack = InIsAttack; }
	void SetCanUseSkillQ(const bool& InCanSkillQ) { bCanSkillQ = InCanSkillQ; }
	void SetCanUseSkillW(const bool& InCanSkillW) { bCanSkillW = InCanSkillW; }
	void SetCanUseSkillE(const bool& InCanSkillE) { bCanSkillE = InCanSkillE; }
	void SetCanUseSkillR(const bool& InCanSkillR) { bCanSkillR = InCanSkillR; }

public:
	FORCEINLINE bool GetIsZoom() const { return bIsZoom; }
	FORCEINLINE bool GetIsAttack() const { return bIsAttack; }
	FORCEINLINE bool GetCanUseSkillQ() const { return bCanSkillQ; }
	FORCEINLINE bool GetCanUseSkillW() const { return bCanSkillW; }
	FORCEINLINE bool GetCanUseSkillE() const { return bCanSkillE; }
	FORCEINLINE bool GetCanUseSkillR() const { return bCanSkillR; }

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Camera Control")
	void OnAttackCameraZoomIn();
	virtual void OnAttackCameraZoomIn_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Camera Control")
	void OnAttackCameraZoomOut();
	virtual void OnAttackCameraZoomOut_Implementation();

	void StartQTimer();
	void StartWTimer();
	void StartETimer();
	void StartRTimer();
	void EndQ();
	void EndW();
	void EndE();
	void EndR();

public:
	UCameraComponent* GetCameraComponent() { return mGameCameraComponent; }

protected:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* mGameCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* mCameraBoom;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zoom", meta = (AllowPrivateAccess = "true"))
	bool bIsZoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillTime", meta = (AllowPrivateAccess = "true"))
	bool bCanSkillQ;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillTime", meta = (AllowPrivateAccess = "true"))
	bool bCanSkillW;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillTime", meta = (AllowPrivateAccess = "true"))
	bool bCanSkillE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillTime", meta = (AllowPrivateAccess = "true"))
	bool bCanSkillR;

	FTimerHandle mQTimer;
	FTimerHandle mWTimer;
	FTimerHandle mETimer;
	FTimerHandle mRTimer;

	float mQCoolDown;
	float mWCoolDown;
	float mECoolDown;
	float mRCoolDown;
};
