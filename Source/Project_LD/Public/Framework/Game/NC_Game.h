// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Character/AppearanceCharacter.h"
#include <Components/WidgetComponent.h>
#include "NC_Game.generated.h"

/**
 * 
 */

UCLASS()
class PROJECT_LD_API ANC_Game : public AAppearanceCharacter
{
	GENERATED_BODY()
	
public:
	ANC_Game();
	~ANC_Game();

public:
	void SetIsAttack(const bool& InIsAttack) { bIsAttack = InIsAttack; }

public:
	FORCEINLINE bool GetIsAttack() const { return bIsAttack; }

public:
	void ShowWorldChat(const FString& inPlayerName, const FString& inMessage, const float& inDuration);
	void ShowLevelUpParticle();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationStats", meta = (AllowPrivateAccess = "true"))
	bool bIsAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* mChatWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* mLevelUpParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* mLevelUpParticle;
};
