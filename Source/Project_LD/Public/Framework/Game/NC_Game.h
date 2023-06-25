// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Character/AppearanceCharacter.h"
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

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;

public:

private:

};
