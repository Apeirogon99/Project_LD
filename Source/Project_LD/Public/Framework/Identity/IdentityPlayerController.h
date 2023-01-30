// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkController.h"
#include "IdentityPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AIdentityPlayerController : public ANetworkController
{
	GENERATED_BODY()

public:
	AIdentityPlayerController();
	virtual ~AIdentityPlayerController();

public:
	virtual void BeginPlay() override;

protected:
	virtual bool	OnRecvPacket(BYTE* buffer, const uint32 len) override;
	virtual bool	OnSend(int32 len) override;
	virtual bool	OnConnect() override;
	virtual bool	OnDisconnect() override;

private:

};

using IdentityPlayerControllerPtr = TSharedPtr<AIdentityPlayerController>;
