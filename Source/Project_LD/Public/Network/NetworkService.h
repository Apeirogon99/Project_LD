﻿// Fill out your copyright notice in the Description page of Project Settings.

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

using FNetworkSessionPtr = TSharedPtr<class FNetworkSession>;

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
	virtual bool IsTickableWhenPaused() const override;
	virtual bool IsTickableInEditor() const override;
	virtual UWorld* GetTickableGameObjectWorld() const override;

	virtual void				Tick(float DeltaTime) override;
	virtual ETickableTickType	GetTickableTickType() const override;
	virtual bool				IsTickable() const override;
	virtual bool				IsAllowedToTick() const override final;
	virtual TStatId				GetStatId() const override;

public:
	FNetworkSessionPtr			GetNetworkSession();

private:
	FNetworkSessionPtr	mNetworkSession;
	bool				mbIsCreateOnRunning;
	uint32				mLastTickFrame;
};