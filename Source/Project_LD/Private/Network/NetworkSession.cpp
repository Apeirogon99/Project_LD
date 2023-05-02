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
#include <Network/NetworkTimeStamp.h>

FNetworkSession::FNetworkSession() : mRecvBuffer(nullptr), mSendBufferQueue(nullptr), mService(nullptr), mController(nullptr), mTimeStamp(nullptr)
{
	mRecvBuffer			= new FRecvBuffer(static_cast<uint32>(Default::MAX_RECV_BUFFER));
	mSendBufferQueue	= new FSendBufferQueue(static_cast<uint32>(Default::MAX_SEND_QUEUE));
	mTimeStamp			= NewObject<UNetworkTimeStamp>();

	mIsSending = static_cast<bool>(Default::SESSION_IS_FREE);
	mIsRecving = static_cast<bool>(Default::SESSION_IS_FREE);
	mIsConnect = static_cast<bool>(Default::SESSION_IS_FREE);
	mIsPossess = static_cast<bool>(Default::SESSION_IS_FREE);

	mSocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	mSocket = mSocketSubsystem->CreateSocket(NAME_Stream, TEXT("NetworkSession"), false);

	mSocket->SetNoDelay(true);
	//mSocket->SetNonBlocking(true);

	int32 newRecvSize = 0;
	mSocket->SetReceiveBufferSize(16384, newRecvSize);
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Socket] Receive buffer size : %d"), newRecvSize), ELogLevel::Warning);

	int32 newSendSize = 0;
	mSocket->SetSendBufferSize(16384, newSendSize);
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Socket] Send buffer size : %d"), newSendSize), ELogLevel::Warning);
	//mSocket->SetLinger()
	
}

FNetworkSession::~FNetworkSession()
{
	if (true == IsConnected())
	{
		RegisterDisconnect("Destructor network session");
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
	FDateTime timeBeginningOfTick = FDateTime::UtcNow();

	if (false == IsConnected())
	{
		return;
	}

	if (false == mController->IsConnectedToSession())
	{
		return;
	}

	bool oldRecving = static_cast<bool>(Default::SESSION_IS_RECVING);
	mIsRecving.CompareExchange(oldRecving, static_cast<bool>(Default::SESSION_IS_FREE));

	if (oldRecving == static_cast<LONG>(Default::SESSION_IS_FREE))
	{
		RegisterRecv();
	}

	FDateTime timeEndOfTick = FDateTime::UtcNow();
	FTimespan tickDuration = timeEndOfTick - timeBeginningOfTick;
	float secondsThisTickTook = tickDuration.GetTotalSeconds();
	float timeToSleep = 0.008f - secondsThisTickTook;
	if (timeToSleep > 0.f)
	{
		FPlatformProcess::Sleep(timeToSleep);
	}
}

void FNetworkSession::Prepare(UNetworkService* service)
{
	mService = service;
}

void FNetworkSession::Shutdown()
{
	
}

void FNetworkSession::PossessToController(ANetworkController* controller, FPossessCallBack inPossessCallback)
{
	if (mController)
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::PossessToController] : Already possess controller", ELogLevel::Error);
		return;
	}

	bool isConnectController;
	mController = controller;
	isConnectController = mController->ConnectToSession(SharedThis(this), inPossessCallback);
	mIsPossess.Store(isConnectController);
}

void FNetworkSession::UnPossessToController(FUnPossessCallBack inUnPossessCallBack)
{
	if (nullptr == mController)
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::UnPossessToController] : Invalid possess controller", ELogLevel::Error);
	}

	bool isDisconnectController;
	isDisconnectController = mController->DisconnectToSession(inUnPossessCallBack);
	mIsPossess.Store(!isDisconnectController);
	mController = nullptr;
}

ANetworkController* FNetworkSession::GetNetworkController()
{
	return mController;
}

bool FNetworkSession::IsPossessController()
{
	if (nullptr == mController)
	{
		return false;
	}

	bool isConnect = mController->IsConnectedToSession();
	bool isPossess = mIsPossess.Load();

	return isConnect && isPossess;
}

bool FNetworkSession::RegisterConnect(const FString& inAddr, const uint16 inPort, FConnectCallBack inConnectCallBack, FDisconnectCallBack inDisconnectCallBack)
{
	if (nullptr == mSocket)
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::Connect] : Invalid FSocket", ELogLevel::Error);
		return false;
	}

	ClearBuffer();

	if (inAddr.IsEmpty() || inPort < 0)
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::Connect] : Invalid IP or Port", ELogLevel::Error);
		return false;
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
		return false;
	}

	return true;
}

bool FNetworkSession::RegisterDisconnect(const FString& inCause)
{
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[FNetworkSession::Disconnect] : %s"), *inCause), ELogLevel::Error);

	mSocket->Shutdown(ESocketShutdownMode::ReadWrite);

	mSocket->Close();

	return true;
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
				RegisterDisconnect("failed to send");
				return;
			}

			if (0 >= byteSent)
			{
				RegisterDisconnect("send 0");
				return;
			}

			processLen += byteSent;
		}
	}

	mIsSending.Store(static_cast<bool>(Default::SESSION_IS_FREE));
}

void FNetworkSession::RegisterRecv()
{
	bool ret;
	if (nullptr == mSocket)
	{
		RegisterDisconnect("Invalid Socket");
		return;
	}

	uint32 PendingDataSize = 0;
	mSocket->HasPendingData(PendingDataSize);

	int32 byteRead = 0;
	const int32 maxReadBytes = mRecvBuffer->GetMaxReadBytes(PendingDataSize);
	ret = mSocket->Recv(mRecvBuffer->GetWriteBuffer(), maxReadBytes, byteRead, ESocketReceiveFlags::Type::None);
	if (false == ret)
	{
		RegisterDisconnect("failed to recv");
		return;
	}

	if (0 >= byteRead)
	{
		RegisterDisconnect("read 0");
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
		RegisterDisconnect(L"Recv 0");
		return;
	}

	if (mController)
	{
		bool recvResult = mController->OnRecv(mRecvBuffer, mRecvBuffer->GetUsedSize());
		if (false == recvResult)
		{
			RegisterDisconnect(L"OnRecv Overflow");
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

bool FNetworkSession::CanRecv()
{

	bool IsData		= GetHasData();
	bool IsRecv		= mIsRecving.Load() == static_cast<bool>(Default::SESSION_IS_FREE) ? true : false;
	bool IsPossess	= IsPossessController();

	return IsData && IsRecv && IsPossess;

}

void FNetworkSession::Connect(const FString& inAddr, const uint16 inPort, FConnectCallBack inConnectCallBack, FDisconnectCallBack inDisconnectCallBack)
{
	if (false == inConnectCallBack.IsBound() || false == inDisconnectCallBack.IsBound())
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::Connect] : Invalid CallBack", ELogLevel::Error);
		return;
	}

	mConnectCallBack = inConnectCallBack;
	mDisconnectCallBack = inDisconnectCallBack;

	bool oldConnect = static_cast<bool>(Default::SESSION_IS_CONNECT);
	mIsConnect.CompareExchange(oldConnect, static_cast<bool>(Default::SESSION_IS_FREE));

	if (oldConnect == static_cast<LONG>(Default::SESSION_IS_CONNECT))
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::Connect] : Already Connect", ELogLevel::Error);
		return;
	}

	bool isConnect = RegisterConnect(inAddr, inPort, inConnectCallBack, inDisconnectCallBack);

	mIsConnect.Store(isConnect);
	mConnectCallBack.Execute(isConnect);
}

void FNetworkSession::KeepConnect(const FString& inAddr, const uint16 inPort, FConnectCallBack inConnectCallBack, FDisconnectCallBack inDisconnectCallBack)
{
	if (false == inConnectCallBack.IsBound() || false == inDisconnectCallBack.IsBound())
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::KeepConnect] : Invalid CallBack", ELogLevel::Error);
		return;
	}

	mConnectCallBack = inConnectCallBack;
	mDisconnectCallBack = inDisconnectCallBack;

	bool oldConnect = static_cast<bool>(Default::SESSION_IS_CONNECT);
	mIsConnect.CompareExchange(oldConnect, static_cast<bool>(Default::SESSION_IS_FREE));

	if (oldConnect == static_cast<LONG>(Default::SESSION_IS_FREE))
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::KeepConnect] : No connection", ELogLevel::Error);
		return;
	}

	ClearBuffer();

	TSharedRef<FInternetAddr> CurrentAddr = mSocketSubsystem->CreateInternetAddr();
	mSocket->GetPeerAddress(*CurrentAddr);

	FIPv4Address pareIp;
	FIPv4Address::Parse(inAddr, pareIp);
	TSharedRef<FInternetAddr> newIpAddr = mSocketSubsystem->CreateInternetAddr();
	newIpAddr->SetIp(pareIp.Value);
	newIpAddr->SetPort(inPort);

	bool isEqualEndPoint = CurrentAddr->CompareEndpoints(*newIpAddr);
	if (false == isEqualEndPoint)
	{
		uint32 curIp, newIp = 0;
		int32 curPort, newPort = 0;
		CurrentAddr->GetIp(curIp);
		CurrentAddr->GetPort(curPort);
		newIpAddr->GetIp(newIp);
		newIpAddr->GetPort(newPort);

		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::KeepConnect] : Diffrent connection info", ELogLevel::Error);
		UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[Current] : %ld, %d"), curIp, curPort), ELogLevel::Error);
		UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[  New  ] : %ld, %d"), newIp, newPort), ELogLevel::Error);
	}

	mIsConnect.Store(isEqualEndPoint);
	mConnectCallBack.Execute(isEqualEndPoint);
}

void FNetworkSession::Disconnect(const FString& inCause)
{
	bool oldDisconnect= static_cast<bool>(Default::SESSION_IS_FREE);
	mIsConnect.CompareExchange(oldDisconnect, static_cast<bool>(Default::SESSION_IS_CONNECT));

	if (oldDisconnect == static_cast<LONG>(Default::SESSION_IS_FREE))
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::Disconnect] : Already Disconnect", ELogLevel::Error);
		return;
	}

	bool isDisconnect = RegisterDisconnect(inCause);
	mIsConnect.Store(!isDisconnect);

	if (false == mDisconnectCallBack.IsBound())
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::Disconnect] : Invalid Disconnect call back", ELogLevel::Error);
		return;
	}

	mDisconnectCallBack.Execute(isDisconnect);
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

const int64 FNetworkSession::GetServerTimeStamp()
{
	return mTimeStamp->GetClientTimeStamp();
}

void FNetworkSession::SetTimeStamp(const int64 inTimeStamp)
{
	mTimeStamp->SetClientTimeStamp(inTimeStamp);
}

bool FNetworkSession::IsConnected() const
{
	bool isConnect = mIsConnect.Load();
	return isConnect == true ? true : false;
}

bool FNetworkSession::GetHasData()
{
	uint32 pendingDataSize = 0;
	bool hasData = mSocket->HasPendingData(pendingDataSize);
	return hasData;
}

bool FNetworkSession::ClearBuffer()
{
	if (nullptr == mRecvBuffer || nullptr == mSendBufferQueue)
	{
		UNetworkUtils::NetworkConsoleLog("[FNetworkSession::Connect] : Invalid Buffer", ELogLevel::Error);
		return false;
	}

	if (true == GetHasData())
	{
		uint32 PendingDataSize = 0;
		mSocket->HasPendingData(PendingDataSize);

		int32 byteRead = 0;
		const int32 maxReadBytes = mRecvBuffer->GetMaxReadBytes(PendingDataSize);
		mSocket->Recv(mRecvBuffer->GetWriteBuffer(), maxReadBytes, byteRead, ESocketReceiveFlags::Type::None);
	}

	mRecvBuffer->Clear();
	mSendBufferQueue->Clear();

	return true;
}
