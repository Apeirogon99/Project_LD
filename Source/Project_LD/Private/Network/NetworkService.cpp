// Fill out your copyright notice in the Description page of Project Settings.

#include "Network/NetworkService.h"
#include <Network/NetworkUtils.h>
#include <Network/NetworkSession.h>
#include <Network/NetworkController.h>
#include <Network/NetworkGameMode.h>
#include <Protobuf/Handler/FClientPacketHandler.h>

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

	FClientPacketHandler::Init();

	mNetworkSession = MakeShared<FNetworkSession>();
	mNetworkSession->Prepare(this);
}

void UNetworkService::Deinitialize()
{
	UNetworkUtils::NetworkConsoleLog("Deinitialize network service", ELogLevel::Warning);


	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("NetworkSession count : %d"), mNetworkSession.GetSharedReferenceCount()), ELogLevel::Warning);
}

void UNetworkService::Tick(float DeltaTime)
{
	if (mLastTickFrame == GFrameCounter)
	{
		return;
	}

	if (mNetworkSession)
	{
		if (mNetworkSession->CanRecv())
		{
			mNetworkSession->NetworkLoop();
		}

		if (mNetworkSession->CanSend())
		{
			mNetworkSession->RegisterSend();
		}

		if (mNetworkSession->CanTick(DeltaTime))
		{
			mNetworkSession->RegisterTick();
		}

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
	if (false == mNetworkSession.IsValid())
	{
		return false;
	}

	return mbIsCreateOnRunning;
}

FNetworkSessionPtr UNetworkService::GetNetworkSession()
{
	return mNetworkSession;
}