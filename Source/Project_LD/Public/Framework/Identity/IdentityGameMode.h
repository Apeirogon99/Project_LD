// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkGameMode.h"
#include "IdentityGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AIdentityGameMode : public ANetworkGameMode
{
	GENERATED_BODY()

public:
	AIdentityGameMode();
	virtual ~AIdentityGameMode();
	
public:
	virtual NetworkControllerPtr CreateDefaultPlayerController() override;

};
