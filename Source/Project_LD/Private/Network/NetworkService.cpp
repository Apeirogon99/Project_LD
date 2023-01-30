// Fill out your copyright notice in the Description page of Project Settings.

#include "Network/NetworkService.h"
#include <Network/NetworkUtils.h>
#include <Network/NetworkSession.h>
#include <Network/NetworkController.h>
#include <Network/NetworkGameMode.h>
#include <Protobuf/Handler/IdentityClientPacketHandler.h>

using NetworkControllerPtr = TSharedPtr<class ANetworkController>;

UNetworkService::UNetworkService() : mNetworkSession(nullptr)
{
	//Templete Tick을 막기위함
	mLastTickFrame = INDEX_NONE;
	//Tick먼저 돌아가지 않기 위한것
	mbIsCreateOnRunning = GIsRunning;
}

UNetworkService::~UNetworkService()
{
}

void UNetworkService::Initialize(FSubsystemCollectionBase& Collection)
{
	UNetworkUtils::NetworkConsoleLog("Initialize network service",ELogLevel::Warning);

	FIdentityClientPacketHandler::Init();

	mNetworkSession = new FNetworkSession();
	mNetworkSession->Prepare(this);
}

void UNetworkService::Deinitialize()
{
	UNetworkUtils::NetworkConsoleLog("Deinitialize network service", ELogLevel::Warning);

	if (nullptr != mNetworkSession)
	{
		delete mNetworkSession;
	}
}

void UNetworkService::Tick(float DeltaTime)
{
	if (mLastTickFrame == GFrameCounter)
	{
		return;
	}

	if (mNetworkSession)
	{
		mNetworkSession->NetworkLoop();
	}
	
	mLastTickFrame = GFrameCounter;
}

bool UNetworkService::IsTickableInEditor() const
{
	return false;
}

UWorld* UNetworkService::GetTickableGameObjectWorld() const
{
	return nullptr;
}

bool UNetworkService::IsTickableWhenPaused() const
{
	return true;
}

bool UNetworkService::IsAllowedToTick() const
{
	return !IsTemplate();
}

ETickableTickType UNetworkService::GetTickableTickType() const
{
	return ETickableTickType::Conditional;
}

TStatId UNetworkService::GetStatId() const
{
	return UObject::GetStatID();
}

bool UNetworkService::IsTickable() const
{
	//이게 Conditional을 통해서 틱을 사용할것인지 판단하는 것인데
	//좀더 응용을 한다면 HasPending을 통해서 값이 있을때만
	//Tick이 돌게 하는것도 나쁘지는 않아보임

	if (nullptr == mNetworkSession)
	{
		return false;
	}

	return mbIsCreateOnRunning && mNetworkSession->IsCanRecv();
}

void UNetworkService::Connect(const FString& inAddr, const uint16 inPort)
{
	if (nullptr == mNetworkSession)
	{
		return;
	}

	mNetworkSession->RegisterConnect(inAddr, inPort);

	ANetworkController* localController = Cast<ANetworkController>(GetWorld()->GetFirstPlayerController());
	mNetworkSession->Possess(localController);

}

void UNetworkService::KeepConnect()
{
	if (nullptr == mNetworkSession)
	{
		return;
	}

	mNetworkSession->UnPossess();

	ANetworkController* localController = Cast<ANetworkController>(GetWorld()->GetFirstPlayerController());
	mNetworkSession->Possess(localController);
}

bool UNetworkService::IsConnected()
{
	if (nullptr == mNetworkSession)
	{
		return false;
	}

	bool isPoccess = mNetworkSession->IsPossess();
	if (false == isPoccess)
	{
		return false;
	}

	bool isConnected = mNetworkSession->IsConnected();
	if (false == isConnected)
	{
		return false;
	}

	return true;
}

void UNetworkService::Disconnect(const FString& cause)
{
	if (nullptr == mNetworkSession)
	{
		return;
	}

	mNetworkSession->RegisterDisconnect(cause);

	mNetworkSession->UnPossess();
}

void UNetworkService::NetworkLevelTravel(const FName& inLevel)
{
	//만약에 이게 안되면 빙의 풀고 다시 해야할듯
	const FString url = inLevel.ToString();
	GetWorld()->ServerTravel(url);
}
