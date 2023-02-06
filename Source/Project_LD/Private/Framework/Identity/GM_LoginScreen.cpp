// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Identity/GM_LoginScreen.h"
#include <Framework/Identity/IdentityPlayerController.h>
#include <Widget/Handler/ClientHUD.h>

AGM_LoginScreen::AGM_LoginScreen()
{
	this->PlayerControllerClass = AIdentityPlayerController::StaticClass();

	if (mDefaultHUDClass)
	{
		this->HUDClass = mDefaultHUDClass->StaticClass();
	}
}

AGM_LoginScreen::~AGM_LoginScreen()
{
}

void AGM_LoginScreen::BeginPlay()
{
	Super::BeginPlay();

	if (false == RequestConnectServer(TEXT("127.0.0.1"), 9000))
	{

	}
}

void AGM_LoginScreen::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGM_LoginScreen::BeginNetwork()
{
	Super::BeginNetwork();

	if (false == mClientHUD)
	{
		return;
	}

	mClientHUD->ShowWidgetFromName(TEXT("LoginScreen"));
	mClientHUD->ShowWidgetFromName(TEXT("Singin"));

}
