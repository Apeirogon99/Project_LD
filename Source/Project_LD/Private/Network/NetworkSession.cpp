// Fill out your copyright notice in the Description page of Project Settings.

#include "Network/NetworkSession.h"
#include <Interfaces/IPv4/IPv4Address.h>
#include <Sockets.h>
#include <SocketSubsystem.h>
#include <IPAddress.h>
#include <Network/RecvBuffer.h>
#include <Network/SendBuffer.h>
#include <Network/SendBufferQueue.h>
#include <Network/NetworkUtils.h>
#include <Network/NetworkTypes.h>
#include <Network/NetworkService.h>
#include <Network/NetworkController.h>

FNetworkSession::FNetworkSession() : mRecvBuffer(nullptr), mSendBufferQueue(nullptr), mService(nullptr), mController(nullptr)
{
	mRecvBuffer = new FRecvBuffer(static_cast<uint32>(Default::MAX_RECV_BUFFER));
	mSendBufferQueue = new FSendBufferQueue(static_cast<uint32>(Default::MAX_SEND_QUEUE));

	mIsSending = static_cast<bool>(Default::SESSION_IS_FREE);
	mIsRecving = static_cast<bool>(Default::SESSION_IS_FREE);

	mIsConnect = false;
	mSocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	mSocket = mSocketSubsystem->CreateSocket(NAME_Stream, TEXT("NetworkSession"), false);
}

FNetworkSession::~FNetworkSession()
{
	if (true == IsConnected())
	{
		Disconnect("Destructor network session");
	}

	if (nullptr != mRecvBuffer)
	{
		delete mRecvBuffer;
	}

	if (nullptr != mSendBufferQueue)
	{
		delete mSendBufferQueue;
	}

	if (nullptr != mSocket)
	{
		mSocketSubsystem->DestroySocket(mSocket);
		mSocket = nullptr;
	}
}

void FNetworkSession::NetworkLoop()
{
	if (false == mIsConnect)
	{
		return;
	}

	if (false == mController->IsConnectedToSession())
	{
		return;
	}

	bool oldRecving = static_cast<bool>(Default::SESSION_IS_RECVING);
	mIsSending.CompareExchange(oldRecving, static_cast<bool>(Default::SESSION_IS_FREE));

	if (oldRecving == static_cast<LONG>(Default::SESSION_IS_FREE))
	{
		RegisterRecv();
	}
}

void FNetworkSession::Prepare(UNetworkService* service)
{
	mService = service;
}

void FNetworkSession::Shutdown()
{
	
}

void FNetworkSession::Possess(ANetworkController* controller)
{
	UnPossess();

	mController = controller;
	mController->ConnectToSession(this);
}

void FNetworkSession::UnPossess()
{
	if (mController)
	{
		mController->DisconnectToSession();
	}
	mController = nullptr;
}

bool FNetworkSession::IsPossess()
{
	if (mController)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void FNetworkSession::RegisterConnect(const FString& inAddr, const uint16 inPort)
{
	Connect(inAddr, inPort);
}

void FNetworkSession::RegisterDisconnect(const FString& inCause)
{
	Disconnect(inCause);
}

void FNetworkSession::RegisterSend()
{
	if (false == IsConnected())
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::Recv] : is not connected server", ELogLevel::Error);
		return;
	}

	TArray<SendBufferPtr> SendBuffers;
	mSendBufferQueue->PopAll(SendBuffers);

	for (SendBufferPtr buffer : SendBuffers)
	{
		int32 byteSent = 0;
		int32 processLen = 0;
		const int32 bufferSize = static_cast<int32>(buffer->GetAllocatedSize());
		while (processLen < bufferSize)
		{
			bool ret = mSocket->Send(buffer->GetData(), bufferSize - processLen, byteSent);
			if (false == ret)
			{
				Disconnect("failed to send");
				return;
			}

			if (0 >= byteSent)
			{
				Disconnect("send 0");
				return;
			}

			processLen += byteSent;
		}
	}
}

void FNetworkSession::RegisterRecv()
{
	bool ret;
	if (nullptr == mSocket)
	{
		Disconnect("Invalid Socket");
		return;
	}

	uint32 PendingDataSize = 0;
	mSocket->HasPendingData(PendingDataSize);

	int32 byteRead = 0;
	const int32 maxReadBytes = mRecvBuffer->GetMaxReadBytes(PendingDataSize);
	ret = mSocket->Recv(mRecvBuffer->GetWriteBuffer(), maxReadBytes, byteRead, ESocketReceiveFlags::Type::None);
	if (false == ret)
	{
		Disconnect("failed to recv");
		return;
	}

	if (0 >= byteRead)
	{
		Disconnect("read 0");
		return;
	}

	mRecvBuffer->MoveRear(static_cast<uint32>(byteRead));

	ProcessRecv(byteRead);
}

void FNetworkSession::ProcessConnect()
{
	if (mController)
	{
		mController->OnConnect();
	}
}

void FNetworkSession::ProcessDisconnect()
{
	if (mController)
	{
		mController->OnDisconnect();
	}
}

void FNetworkSession::ProcessSend(int32 numOfBytes)
{
	if (mController)
	{
		mController->OnSend(numOfBytes);
	}
}

void FNetworkSession::ProcessRecv(int32 numOfBytes)
{
	if (numOfBytes == 0)
	{
		Disconnect(L"Recv 0");
		return;
	}

	if (mController)
	{
		bool recvResult = mController->OnRecv(mRecvBuffer, mRecvBuffer->GetUsedSize());
		if (false == recvResult)
		{
			Disconnect(L"OnRecv Overflow");
			return;
		}
	}

	if (false == GetHasData())
	{
		mIsRecving.Store(static_cast<bool>(Default::SESSION_IS_FREE));
	}
	else
	{
		RegisterRecv();
	}
}

bool FNetworkSession::IsCanRecv()
{
	bool HasData = GetHasData();
	bool CanRecv = mIsRecving.Load() == static_cast<bool>(Default::SESSION_IS_FREE) ? true : false;

	return HasData && CanRecv;
}

void FNetworkSession::Connect(const FString& inAddr, const uint16 inPort)
{
	if (true == IsConnected())
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::Connect] : Already Connect", ELogLevel::Error);
		return;
	}

	if (nullptr == mSocket)
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::Connect] : Invalid FSocket", ELogLevel::Error);
		return;
	}

	FIPv4Address pareIp;
	FIPv4Address::Parse(inAddr, pareIp);
	
	TSharedRef<FInternetAddr> newIpAddr = mSocketSubsystem->CreateInternetAddr();
	newIpAddr->SetIp(pareIp.Value);
	newIpAddr->SetPort(inPort);

	bool connRet = mSocket->Connect(newIpAddr.Get());
	if (false == connRet)
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::Connect] : Failed Connect", ELogLevel::Error);
		return;
	}

	mIsConnect = true;
	
}

void FNetworkSession::Disconnect(const FString& inCause)
{
	mIsConnect = false;

	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[FNetworkSession::Disconnect] : %s"), *inCause), ELogLevel::Error);
	mSocket->Shutdown(ESocketShutdownMode::Read);
	mSocket->Close();

	//Disconnected call back
}

void FNetworkSession::Send(SendBufferPtr FSendBuffer)
{
	if (false == IsConnected())
	{
		return;
	}

	bool oldSending = static_cast<bool>(Default::SESSION_IS_SENDING);
	mIsSending.CompareExchange(oldSending, static_cast<bool>(Default::SESSION_IS_FREE));

	mSendBufferQueue->Push(FSendBuffer);

	if (oldSending == static_cast<LONG>(Default::SESSION_IS_FREE))
	{
		RegisterSend();
	}

}

bool FNetworkSession::IsConnected() const
{
	return mIsConnect == true ? true : false;
}

bool FNetworkSession::GetHasData()
{
	uint32 pendingDataSize = 0;
	bool hasData = mSocket->HasPendingData(pendingDataSize);
	return hasData;
}
