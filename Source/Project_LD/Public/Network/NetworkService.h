// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Subsystems/GameInstanceSubsystem.h>
#include <Templates/SubclassOf.h>
#include <Tickable.h>
#include "NetworkService.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UNetworkService : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	UNetworkService();
	virtual ~UNetworkService();

public:
	//GameInstanceSubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	//TickableGameObject
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickableInEditor() const override { return false; }
	virtual bool IsTickableWhenPaused() const override { return true; }
	virtual bool IsAllowedToTick() const override final;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;

public:

private:

};
