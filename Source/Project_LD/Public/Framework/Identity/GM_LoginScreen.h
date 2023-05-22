// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkGameMode.h"
#include "GM_LoginScreen.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AGM_LoginScreen : public ANetworkGameMode
{
	GENERATED_BODY()
	
public:
	AGM_LoginScreen();
	virtual ~AGM_LoginScreen();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void InitNetwork() override;
	virtual void BeginNetwork() override;
};
