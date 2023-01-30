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
	//Templete Tick�� ��������
	mLastTickFrame = INDEX_NONE;
	//Tick���� ���ư��� �ʱ� ���Ѱ�
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
	//�̰� Conditional�� ���ؼ� ƽ�� ����Ұ����� �Ǵ��ϴ� ���ε�
	//���� ������ �Ѵٸ� HasPending�� ���ؼ� ���� ��������
	//Tick�� ���� �ϴ°͵� �������� �ʾƺ���

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
	//���࿡ �̰� �ȵǸ� ���� Ǯ�� �ٽ� �ؾ��ҵ�
	const FString url = inLevel.ToString();
	GetWorld()->ServerTravel(url);
}
