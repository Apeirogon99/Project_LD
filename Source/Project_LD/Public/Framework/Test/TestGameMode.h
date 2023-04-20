// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkGameMode.h"
#include "TestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API ATestGameMode : public ANetworkGameMode
{
	GENERATED_BODY()
	
public:
	ATestGameMode();
	virtual ~ATestGameMode();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void BeginNetwork() override;
};
