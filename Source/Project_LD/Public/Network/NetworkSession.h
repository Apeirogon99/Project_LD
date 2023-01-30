// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

class FSocket;
class ISocketSubsystem;
class FRecvBuffer;
class FSendBufferQueue;

class FSendBuffer;
class UNetworkService;
class ANetworkController;

using SendBufferPtr = TSharedPtr<class FSendBuffer>;

class PROJECT_LD_API FNetworkSession
{
	enum class Default
	{
		MAX_RECV_BUFFER = 0x400,
		MAX_SEND_QUEUE = 0x400,
		SESSION_IS_SENDING = 1,
		SESSION_IS_RECVING = 1,
		SESSION_IS_FREE = 0,
	};
	
public:
	FNetworkSession();
	virtual ~FNetworkSession();

public:
	void NetworkLoop();
	void Prepare(UNetworkService* service);
	void Shutdown();

	void Possess(ANetworkController* controller);
	void UnPossess();
	bool IsPossess();

	void RegisterConnect(const FString& inAddr, const uint16 inPort);
	void RegisterDisconnect(const FString& inCause);
	void RegisterSend();
	void RegisterRecv();

	void ProcessConnect();
	void ProcessDisconnect();
	void ProcessSend(int32 numOfBytes);
	void ProcessRecv(int32 numOfBytes);

	bool IsCanRecv();
	void Connect(const FString& inAddr, const uint16 inPort);
	void Disconnect(const FString& inCause);
	void Send(SendBufferPtr FSendBuffer);

public:
	bool IsConnected() const;

protected:
	bool GetHasData();

private:

	FSocket*				mSocket;
	ISocketSubsystem*		mSocketSubsystem;
	FRWLock					mLock;

	FRecvBuffer*			mRecvBuffer;
	FSendBufferQueue*		mSendBufferQueue;

	TAtomic<bool>			mIsSending;
	TAtomic<bool>			mIsRecving;
	bool					mIsConnect;

	UNetworkService*		mService;
	ANetworkController*		mController;
};