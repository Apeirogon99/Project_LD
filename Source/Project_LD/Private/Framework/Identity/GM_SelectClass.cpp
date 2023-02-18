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

	if (true == IsConnectedServer())
	{
		if (false == RequestKeepConnectServer(TEXT("127.0.0.1"), 9000))
		{

		}
	}
	else
	{
		if (false == RequestConnectServer(TEXT("127.0.0.1"), 9000))
		{

		}
	}
}

void AGM_SelectClass::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
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
