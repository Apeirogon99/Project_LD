// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Character/AppearanceCharacter.h"
#include "Framework/Interface/InteractiveInterface.h"
#include "NCI_Game.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API ANCI_Game : public AAppearanceCharacter, public IInteractiveInterface
{
	GENERATED_BODY()
	
public:
	virtual void Interactive(ANC_Game* Player) override;
};
