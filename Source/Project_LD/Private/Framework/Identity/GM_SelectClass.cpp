// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Identity/GM_SelectClass.h"
#include <Framework/Identity/IdentityPlayerController.h>
#include <Widget/Handler/ClientHUD.h>

AGM_SelectClass::AGM_SelectClass()
{
	this->PlayerControllerClass = AIdentityPlayerController::StaticClass();
}

AGM_SelectClass::~AGM_SelectClass()
{
}

void AGM_SelectClass::BeginPlay()
{
	Super::BeginPlay();

}

void AGM_SelectClass::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGM_SelectClass::InitNetwork()
{
	if (true == IsConnectedServer())
	{
		if (false == RequestKeepConnectServer(TEXT("116.41.116.247"), 9000))
		{
			NetworkGameModeLog(FString(TEXT("failed to requset keep connect server")));
		}
	}
	else
	{
		if (false == RequestConnectServer(TEXT("116.41.116.247"), 9000))
		{
			NetworkGameModeLog(FString(TEXT("failed to requset connect server")));
		}
	}
}

void AGM_SelectClass::BeginNetwork()
{
	Super::BeginNetwork();

	if (false == mClientHUD)
	{
		return;
	}

	mClientHUD->ShowWidgetFromName(TEXT("SelectClass"));
}
