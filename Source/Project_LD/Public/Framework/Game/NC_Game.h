// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Character/AppearanceCharacter.h"
#include <Components/WidgetComponent.h>
#include "NC_Game.generated.h"

/**
 * 
 */
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class PROJECT_LD_API ANC_Game : public AAppearanceCharacter
{
	GENERATED_BODY()
	
public:
	ANC_Game();
	~ANC_Game();

public:
	void SetCanUseSkillQ(const bool& InCanSkillQ) { bCanSkillQ = InCanSkillQ; }
	void SetCanUseSkillW(const bool& InCanSkillW) { bCanSkillW = InCanSkillW; }
	void SetCanUseSkillE(const bool& InCanSkillE) { bCanSkillE = InCanSkillE; }
	void SetCanUseSkillR(const bool& InCanSkillR) { bCanSkillR = InCanSkillR; }
	void SetCanUseDash(const bool& InCanSkillDash) { bCanDash = InCanSkillDash; }

	UFUNCTION(BlueprintCallable)
	void SetUsingSkill(const bool& InUsingSkill) { bUsingSkill = InUsingSkill; }

	UFUNCTION(BlueprintCallable)
	void SetCanMove(const bool& InCanMove) { bCanMove = InCanMove; }

public:
	FORCEINLINE bool GetUsingSkill()			const { return bUsingSkill; }
	FORCEINLINE bool GetCanUseSkillQ()	const { return bCanSkillQ; }
	FORCEINLINE bool GetCanUseSkillW()	const { return bCanSkillW; }
	FORCEINLINE bool GetCanUseSkillE()	const { return bCanSkillE; }
	FORCEINLINE bool GetCanUseSkillR()	const { return bCanSkillR; }
	FORCEINLINE bool GetCanUseDash()		const { return bCanDash; }
	FORCEINLINE bool GetCanMove()			const { return bCanMove; }

public:
	void ShowWorldChat(const FString& inPlayerName, const FString& inMessage, const float& inDuration);
	void ShowLevelUpParticle();
	void ActiveBuffParticle();
	void DeActiveBuffParticle();
	void StopMovement();

	void EndQ();
	void EndW();
	void EndE();
	void EndR();
	void EndDash();
	
	void ManageSkill(int32 InSkillCode);

public:
	bool IsAttack;
	bool RCharage;

public:
	UFUNCTION(BlueprintCallable)
	void ActiveMovement();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReplaceIconParty();
	virtual void ReplaceIconParty_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReplaceIconOtherPlayer();
	virtual void ReplaceIconOtherPlayer_Implementation();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;

public:
	void DoAppearSkill(const FVector& inLocation, const FRotator& inRotation, const int64& inRemoteID, const int64& inGameOjbectID, const int32& inSkillID, const float& inDuration);
	void DoActionSkill(const FVector& inLocation, const FRotator& inRotation, const int64& inRemoteID, const int64& inGameOjbectID, const int32& inSkillID, const float& inDuration);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* mChatWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* mApplyBuffParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* mApplyBuffStore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* mLevelUpParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* mLevelUpParticle;

protected:
	bool bBuffActive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillTime", meta = (AllowPrivateAccess = "true"))
	bool bUsingSkill;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillTime", meta = (AllowPrivateAccess = "true"))
	bool bCanSkillQ;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillTime", meta = (AllowPrivateAccess = "true"))
	bool bCanSkillW;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillTime", meta = (AllowPrivateAccess = "true"))
	bool bCanSkillE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillTime", meta = (AllowPrivateAccess = "true"))
	bool bCanSkillR;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillTime", meta = (AllowPrivateAccess = "true"))
	bool bCanDash;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkillTime", meta = (AllowPrivateAccess = "true"))
	bool bCanMove;
};
