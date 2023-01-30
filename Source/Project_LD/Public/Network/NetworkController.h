// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NetworkController.generated.h"

struct PacketHeader
{
	uint16 size;
	uint16 id;
};

/**
 * 
 */

class FRecvBuffer;
class FSendBuffer;
class FNetworkSession;

using SendBufferPtr = TSharedPtr<FSendBuffer>;

UCLASS(Abstract)
class PROJECT_LD_API ANetworkController : public APlayerController
{
	GENERATED_BODY()

public:
	ANetworkController();
	virtual ~ANetworkController();

public:
	bool IsConnectedToSession();
	void ConnectToSession(FNetworkSession* session);
	void DisconnectToSession();

public:
	FNetworkSession* GetNetworkSession() { return mNetworkSession; }
	void Send(SendBufferPtr FSendBuffer);

public:
	//Use NetworkSession Callback
	virtual bool	OnRecv(FRecvBuffer* buffer, int32 len) sealed;
	virtual bool	OnRecvPacket(BYTE* buffer, const uint32 len) { return true; };
	virtual bool	OnSend(int32 len) { return true; };
	virtual bool	OnConnect() { return true; };
	virtual bool	OnDisconnect() { return true; };

private:
	FNetworkSession* mNetworkSession;
};
