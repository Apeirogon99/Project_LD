// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Identity/GM_CustomCharacter.h"
#include <Framework/Identity/IdentityPlayerController.h>
#include <Framework/Gameinstance/LDGameInstance.h>
#include <Framework/Identity/C_Dummy.h>
#include <Widget/Handler/ClientHUD.h>

AGM_CustomCharacter::AGM_CustomCharacter()
{
	this->PlayerControllerClass = AIdentityPlayerController::StaticClass();
}

AGM_CustomCharacter::~AGM_CustomCharacter()
{
}

void AGM_CustomCharacter::BeginPlay()
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

void AGM_CustomCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGM_CustomCharacter::BeginNetwork()
{
	Super::BeginNetwork();

	if (false == mClientHUD)
	{
		return;
	}

	ULDGameInstance* gameinstance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	if (nullptr == gameinstance)
	{
		return;
	}

	FCharacterDatas& datas = gameinstance->mCharacterDatas;

	TSubclassOf<AC_Dummy> dummyClass = mDummyCharacterClass[datas.mClass];
	if (dummyClass)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector CharacterLocation(100.0f, 0.0f, 505.0f);
		FRotator CharacterRotation(0.0f, -180.0f, 0.0f);

		mDummyCharacter = GetWorld()->SpawnActor<AC_Dummy>(dummyClass, CharacterLocation, CharacterRotation, spawnParams);
	}

	mClientHUD->ShowWidgetFromName(TEXT("CustomCharacter"));
}
