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

DECLARE_DELEGATE_OneParam(FPossessCallBack, bool)
DECLARE_DELEGATE_OneParam(FUnPossessCallBack, bool)

class FRecvBuffer;
class FSendBuffer;
class FNetworkSession;

using SendBufferPtr = TSharedPtr<FSendBuffer>;
using FNetworkSessionPtr = TSharedPtr<class FNetworkSession>;

UCLASS(Abstract)
class PROJECT_LD_API ANetworkController : public APlayerController
{
	GENERATED_BODY()

public:
	ANetworkController();
	virtual ~ANetworkController();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	bool IsConnectedToSession();
	bool ConnectToSession(FNetworkSessionPtr session, FPossessCallBack inPossessCallBack);
	bool DisconnectToSession(FUnPossessCallBack inUnPossessCallback);

public:
	bool IsClientController();

	class UNetworkTimeStamp* GetTimeStamp();
	const int64 GetServerTimeStamp();
	const int64 GetClientTimeStamp();

	FNetworkSessionPtr GetNetworkSession() { return mNetworkSession; }
	void Send(SendBufferPtr FSendBuffer);

public:
	//Use NetworkSession Callback
	virtual bool	OnRecv(FRecvBuffer* buffer, int32 len) sealed;
	virtual bool	OnRecvPacket(BYTE* buffer, const uint32 len) { return true; }
	virtual bool	OnSend(int32 len) { return true; }
	virtual bool	OnConnect() { return true; }
	virtual bool	OnDisconnect() { return true; }
	virtual bool	OnTick() { return true; }

public:
	void ExecutePossessCallBack(const bool inResult);
	void ExecuteUnPossessCallBack(const bool inResult);

private:
	FNetworkSessionPtr	mNetworkSession;
	FPossessCallBack	mPossessCallBack;
	FUnPossessCallBack	mUnPossessCallBack;

private:
	TArray<BYTE>		mTempPacketBuffer;
	//BYTE				mPacketBuffer[1024];
};
