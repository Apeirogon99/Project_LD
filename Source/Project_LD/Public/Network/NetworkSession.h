﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

DECLARE_DELEGATE_OneParam(FConnectCallBack, bool)
DECLARE_DELEGATE_OneParam(FDisconnectCallBack, bool)
DECLARE_DELEGATE_OneParam(FPossessCallBack, bool)
DECLARE_DELEGATE_OneParam(FUnPossessCallBack, bool)

class FSocket;
class ISocketSubsystem;
class FRecvBuffer;
class FSendBufferQueue;

class FSendBuffer;
class UNetworkService;
class ANetworkController;

class UNetworkTimeStamp;

using SendBufferPtr = TSharedPtr<class FSendBuffer>;

class PROJECT_LD_API FNetworkSession : public TSharedFromThis<FNetworkSession>
{
	enum class Default
	{
		MAX_RECV_BUFFER = 0x1000,
		MAX_SEND_QUEUE = 0x1000,
		SESSION_IS_SENDING = 1,
		SESSION_IS_RECVING = 1,
		SESSION_IS_CONNECT = 1,
		SESSION_IS_POSSESS = 1,
		SESSION_IS_FREE = 0,
	};
	
public:
	FNetworkSession();
	virtual ~FNetworkSession();

public:
	void InitSocket();

	void NetworkLoop();
	void Prepare(UNetworkService* service);
	void Shutdown();

	void PossessToController(ANetworkController* controller, FPossessCallBack inPossessCallback);
	void UnPossessToController(FUnPossessCallBack inUnPossessCallBack);
	ANetworkController* GetNetworkController();
	bool IsPossessController() const;

	bool RegisterConnect(const FString& inAddr, const uint16 inPort, FConnectCallBack inConnectCallBack, FDisconnectCallBack inDisconnectCallBack);
	bool RegisterDisconnect(const FString& inCause);
	void RegisterSend();
	void RegisterRecv();
	void RegisterTick();

	void ProcessConnect();
	void ProcessDisconnect();
	void ProcessSend(int32 numOfBytes);
	void ProcessRecv(int32 numOfBytes);

	bool CanRecv();
	bool CanSend();
	bool CanTick(float inDeltaTime);

	bool CheackDisconnect();
	bool IsServerOpen(const TSharedRef<FInternetAddr>& inIpAddr);
	void Connect(const FString& inAddr, const uint16 inPort, FConnectCallBack inConnectCallBack, FDisconnectCallBack inDisconnectCallBack);
	void KeepConnect(const FString& inAddr, const uint16 inPort, FConnectCallBack inConnectCallBack, FDisconnectCallBack inDisconnectCallBack);
	void Disconnect(const FString& inCause);
	void Send(SendBufferPtr FSendBuffer);

	UNetworkTimeStamp* GetTimeStamp();
	int64 GetPacketTimeStmap() { return mPacketTimeStmap; }

public:
	bool IsConnected() const;
	bool GetHasData();

protected:
	bool ClearBuffer();

private:

	FSocket*				mSocket;
	ISocketSubsystem*		mSocketSubsystem;
	FRWLock					mLock;

	TArray<BYTE>			mTempBuffer;
	FRecvBuffer*			mRecvBuffer;
	FSendBufferQueue*		mSendBufferQueue;

	TAtomic<bool>			mIsSending;
	TAtomic<bool>			mIsRecving;
	TAtomic<bool>			mIsConnect;
	TAtomic<bool>			mIsPossess;

	UNetworkService*		mService;
	ANetworkController*		mController;

	UPROPERTY()
	UNetworkTimeStamp*		mTimeStamp;

	int64					mPacketTimeStmap;

	float					mTickDelayTime;

private:
	FConnectCallBack		mConnectCallBack;
	FDisconnectCallBack		mDisconnectCallBack;
};