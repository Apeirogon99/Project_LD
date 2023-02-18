// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkGameMode.h"
#include "GM_SelectClass.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AGM_SelectClass : public ANetworkGameMode
{
	GENERATED_BODY()
	
public:
	AGM_SelectClass();
	virtual ~AGM_SelectClass();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void BeginNetwork() override;

};
