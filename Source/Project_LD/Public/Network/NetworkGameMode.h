// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NetworkGameMode.generated.h"

/**
 * 
 */

class ANetworkController;
using NetworkControllerPtr = TSharedPtr<class ANetworkController>;

UCLASS(Abstract)
class PROJECT_LD_API ANetworkGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ANetworkGameMode();
	virtual ~ANetworkGameMode();

public:
	UFUNCTION(BlueprintCallable, Category = "Network")
	bool RequestConnectServer(const FString& inIpAddr, const int32 inPort);

	UFUNCTION(BlueprintCallable, Category = "Network")
	bool RequestKeepConnect();

	UFUNCTION(BlueprintCallable, Category = "Network")
	bool IsConnected();

	UFUNCTION(BlueprintCallable, Category = "Network")
	void RequestTravelLevel(const FString& inLevel);

	UFUNCTION(BlueprintCallable, Category = "Network")
	bool RequestExitGame(const bool inForce = false);

public:
	UFUNCTION(BlueprintCallable, Category = "Callback")
	void ProcessConnect();

	UFUNCTION(BlueprintCallable, Category = "Callback")
	void ProcessDisconnect();

public:
	virtual NetworkControllerPtr CreateDefaultPlayerController() { return nullptr; };
};
