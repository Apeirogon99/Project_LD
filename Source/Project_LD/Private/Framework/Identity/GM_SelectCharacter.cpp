// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Identity/GM_SelectCharacter.h"
#include <Framework/Identity/IdentityPlayerController.h>
#include <Widget/Handler/ClientHUD.h>

#include <Widget/Identity/W_SelectCharacter.h>
#include <Widget/Identity/W_SelectCharacterButton.h>

AGM_SelectCharacter::AGM_SelectCharacter()
{
	this->PlayerControllerClass = AIdentityPlayerController::StaticClass();
}

AGM_SelectCharacter::~AGM_SelectCharacter()
{
}

void AGM_SelectCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (false == RequestKeepConnectServer(TEXT("127.0.0.1"), 9000))
	{

	}
}

void AGM_SelectCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGM_SelectCharacter::BeginNetwork()
{
	Super::BeginNetwork();

	if (false == mClientHUD)
	{
		return;
	}

	APlayerController* playerControll = GetWorld()->GetFirstPlayerController();
	AClientHUD* clientHUD = Cast<AClientHUD>(playerControll->GetHUD());
	UW_SelectCharacter* sewidget = Cast<UW_SelectCharacter>(clientHUD->GetWidgetFromName(TEXT("SelectCharacter")));
	sewidget->LoadCharacterInfo(0, TEXT("32"), TEXT("테스트1"));
	sewidget->LoadCharacterInfo(1, TEXT("1"), TEXT("테스트2"));
	sewidget->LoadCharacterInfo(2, TEXT("50"), TEXT("테스트3"));
	sewidget->LoadCharacterInfo(3, TEXT("100"), TEXT("테스트4"));
	mClientHUD->ShowWidgetFromName(TEXT("SelectCharacter"));
}
