// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkGameMode.h"
#include <Network/NetworkService.h>
#include <Network/NetworkSession.h>
#include <Network/NetworkPlayerState.h>
#include <Network/NetworkCharacter.h>
#include <Network/NetworkController.h>
#include <Network/NetworkGameState.h>
#include <Network/NetworkUtils.h>
#include <Framework/Gameinstance/LDGameInstance.h>
#include <Kismet/GameplayStatics.h>
#include <Widget/Handler/ClientHUD.h>
#include <Widget/Common/W_Notification.h>

ANetworkGameMode::ANetworkGameMode()
{
	bUseSeamlessTravel = true;
	mIsConnect = false;
	mIsPossess = false;
	mIsHUD = false;

	if (mDefaultHUDClass)
	{
		this->HUDClass = mDefaultHUDClass->StaticClass();
	}

}

ANetworkGameMode::~ANetworkGameMode()
{
}

void ANetworkGameMode::BeginPlay()
{
	Super::BeginPlay();

	mConnectCallBack.BindUFunction(this, FName("ProcessConnect"));
	mDisConnectCallBack.BindUFunction(this, FName("ProcessDisconnect"));
	mPossessCallBack.BindUFunction(this, FName("PossessNetwork"));
	mUnPossessCallBack.BindUFunction(this, FName("UnPossessNetwork"));
	mTravel.AddUFunction(this, FName("ProcessOpenLevel"));

	if (mServerLoadingWidgetClass)
	{
		mServerLoadingWidget = CreateWidget<UUserWidget>(GetWorld(), mServerLoadingWidgetClass);
		mServerLoadingWidget->AddToPlayerScreen();
	}

	if (mNetworkNotificationWidgetClass)
	{
		mNetworkNotificationWidget = CreateWidget<UW_Notification>(GetWorld(), mNetworkNotificationWidgetClass);
	}
}

void ANetworkGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	mConnectCallBack.Unbind();
	mDisConnectCallBack.Unbind();
	mPossessCallBack.Unbind();
	mUnPossessCallBack.Unbind();
	mTravel.Clear();
}

bool ANetworkGameMode::RequestConnectServer(const FString& inIpAddr, const int32 inPort)
{
	uint16 port = static_cast<uint16>(inPort);

	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(GetGameInstance());
	if (nullptr == gameInstance)
	{
		return false;
	}

	UNetworkService* networkService = gameInstance->GetSubsystem<UNetworkService>();
	if (nullptr == networkService)
	{
		return false;
	}

	FNetworkSessionPtr networkSession = networkService->GetNetworkSession();
	if (false == networkSession.IsValid())
	{
		return false;
	};

	networkSession->Connect(inIpAddr, inPort, mConnectCallBack, mDisConnectCallBack);

	return true;
}

bool ANetworkGameMode::RequestKeepConnectServer(const FString& inIpAddr, const int32 inPort)
{
	uint16 port = static_cast<uint16>(inPort);

	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(GetGameInstance());
	if (nullptr == gameInstance)
	{
		return false;
	}

	UNetworkService* networkService = gameInstance->GetSubsystem<UNetworkService>();
	if (nullptr == networkService)
	{
		return false;
	}

	FNetworkSessionPtr networkSession = networkService->GetNetworkSession();
	if (false == networkSession.IsValid())
	{
		return false;
	};

	networkSession->KeepConnect(inIpAddr, inPort, mConnectCallBack, mDisConnectCallBack);

	return true;
}

bool ANetworkGameMode::RequestDisconnectServer()
{
	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(GetGameInstance());
	if (nullptr == gameInstance)
	{
		return false;
	}

	UNetworkService* networkService = gameInstance->GetSubsystem<UNetworkService>();
	if (nullptr == networkService)
	{
		return false;
	}

	FNetworkSessionPtr networkSession = networkService->GetNetworkSession();
	if (false == networkSession.IsValid())
	{
		return false;
	}

	networkSession->Disconnect("ANetworkGameMode : DisconnectServer");

	return true;
}

bool ANetworkGameMode::RequestPossessController()
{
	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(GetGameInstance());
	if (nullptr == gameInstance)
	{
		return false;
	}

	UNetworkService* networkService = gameInstance->GetSubsystem<UNetworkService>();
	if (nullptr == networkService)
	{
		return false;
	}

	FNetworkSessionPtr networkSession = networkService->GetNetworkSession();
	if (false == networkSession.IsValid())
	{
		return false;
	}

	APlayerController* firstPlayerController = GetWorld()->GetFirstPlayerController();
	ANetworkController* networkPlayerController = Cast<ANetworkController>(firstPlayerController);
	
	networkSession->PossessToController(networkPlayerController, mPossessCallBack);

	return true;
}

bool ANetworkGameMode::RequestUnPossessController()
{
	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(GetGameInstance());
	if (nullptr == gameInstance)
	{
		return false;
	}

	UNetworkService* networkService = gameInstance->GetSubsystem<UNetworkService>();
	if (nullptr == networkService)
	{
		return false;
	}

	FNetworkSessionPtr networkSession = networkService->GetNetworkSession();
	if (false == networkSession.IsValid())
	{
		return false;
	}

	networkSession->UnPossessToController(mUnPossessCallBack);

	return true;
}

void ANetworkGameMode::RequestTravelLevel(const FString& inLevel)
{
	mServerLoadingWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	mTravelLevel = inLevel;
	RequestUnPossessController();
}

void ANetworkGameMode::RequestTravelServer(const FString& inLevel)
{
	mTravelLevel = inLevel;
	RequestDisconnectServer();
}

bool ANetworkGameMode::RequestExitGame()
{
	FGenericPlatformMisc::RequestExit(false);
	return true;
}

bool ANetworkGameMode::IsNetworkInit()
{
	if (!(mIsConnect && mIsPossess && mIsHUD))
	{
		return false;
	}

	mServerLoadingWidget->SetVisibility(ESlateVisibility::Collapsed);

	BeginNetwork();

	return true;
}

bool ANetworkGameMode::IsConnectedServer()
{
	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(GetGameInstance());
	if (nullptr == gameInstance)
	{
		return false;
	}

	UNetworkService* networkService = gameInstance->GetSubsystem<UNetworkService>();
	if (nullptr == networkService)
	{
		return false;
	}

	FNetworkSessionPtr networkSession = networkService->GetNetworkSession();
	if (false == networkSession.IsValid())
	{
		return false;
	}

	bool connect = networkSession->IsConnected();

	return connect;
}

ANetworkController* ANetworkGameMode::GetNetworkController()
{
	ULDGameInstance* gameInstance = Cast<ULDGameInstance>(GetGameInstance());
	if (nullptr == gameInstance)
	{
		return nullptr;
	}

	UNetworkService* networkService = gameInstance->GetSubsystem<UNetworkService>();
	if (nullptr == networkService)
	{
		return nullptr;
	}

	FNetworkSessionPtr networkSession = networkService->GetNetworkSession();
	if (false == networkSession.IsValid())
	{
		return nullptr;
	}

	if (false == networkSession->IsPossessController())
	{
		return nullptr;
	}

	ANetworkController* controller = networkSession->GetNetworkController();

	return controller;
}

void ANetworkGameMode::BeginNetwork()
{
	
}

void ANetworkGameMode::ProcessClientHUD(bool inInitHUD)
{
	mIsHUD = inInitHUD;

	if (false == mIsHUD)
	{
		ShowNetworkNotification(TEXT("사용자 위젯 초기화에 실패하였습니다"));
		return;
	}

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	mClientHUD = Cast<AClientHUD>(playerController->GetHUD());
	IsNetworkInit();
}

void ANetworkGameMode::ProcessConnect(bool inIsConnect)
{
	mIsConnect = inIsConnect;

	if (false == mIsConnect)
	{
		ShowNetworkNotification(TEXT("서버 연결에 실패하였습니다"));
		return;
	}

	RequestPossessController();
}

void ANetworkGameMode::ProcessDisconnect(bool inIsDisConnect)
{
	mIsConnect = !inIsDisConnect;

	if (true == mIsConnect)
	{
		ShowNetworkNotification(TEXT("서버 연결종료에 실패하였습니다"));
		return;
	}

	RequestUnPossessController();
}

void ANetworkGameMode::PossessNetwork(bool inIsPossess)
{
	mIsPossess = inIsPossess;

	if (false == mIsConnect)
	{
		ShowNetworkNotification(TEXT("플레이어 동기화 연결에 실패하였습니다"));
		return;
	}

	IsNetworkInit();
}

void ANetworkGameMode::UnPossessNetwork(bool inIsUnPossess)
{
	mIsPossess = !inIsUnPossess;

	if (true == mIsPossess)
	{
		ShowNetworkNotification(TEXT("플레이어 동기화 연결종료에 실패하였습니다"));
		return;
	}

	ProcessOpenLevel(mTravelLevel);
}

void ANetworkGameMode::ProcessOpenLevel(const FString& inLevel)
{
	FString currentLevelName;
	GetWorld()->GetCurrentLevel()->GetName(currentLevelName);

	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("Open Level [%s]->[%s]"), *currentLevelName, *inLevel), ELogLevel::Warning);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*inLevel));
}

void ANetworkGameMode::ShowNetworkNotification(const FString& inNotification)
{
	if (false == mNetworkNotificationWidget->IsInViewport())
	{
		mNetworkNotificationWidget->SetTitle(TEXT("에러"));
		mNetworkNotificationWidget->SetNotification(inNotification);
		mNetworkNotificationWidget->SetButtonText(TEXT("종료하기"));
		mNetworkNotificationWidget->mNotificationDelegate.BindUFunction(this, FName("RequestExitGame"));
		mNetworkNotificationWidget->AddToPlayerScreen();
	}

	if (true == mServerLoadingWidget->IsInViewport())
	{
		mServerLoadingWidget->RemoveFromParent();
	}
}
