// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Controller/MovementController.h"
#include "PC_Game.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API APC_Game : public AMovementController
{
	GENERATED_BODY()

public:
	APC_Game();
	~APC_Game();

public:
	virtual void BeginPlay() override;
	
public:
	virtual bool	OnRecvPacket(BYTE* buffer, const uint32 len) override;
	virtual bool	OnSend(int32 len) override;
	virtual bool	OnConnect() override;
	virtual bool	OnDisconnect() override;

};
