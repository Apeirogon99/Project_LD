// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Identity/GM_CustomCharacter.h"
#include <Framework/Identity/IdentityPlayerController.h>
#include <Framework/Gameinstance/LDGameInstance.h>
#include <Network/NetworkCharacter.h>
#include <Widget/Handler/ClientHUD.h>
#include <Widget/Identity/W_CustomCharacter.h>

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

	CreateNewDummyCharacter(StaticCast<int32>(ETribe::Man));

	UW_CustomCharacter* customWidget = Cast<UW_CustomCharacter>(mClientHUD->GetWidgetFromName(TEXT("CustomCharacter")));
	customWidget->SetClassText(gameinstance->mCharacterDatas.mClass);
	mClientHUD->ShowWidgetFromName(TEXT("CustomCharacter"));
}

void AGM_CustomCharacter::CreateNewDummyCharacter(int32 InTribe)
{
	ULDGameInstance* gameinstance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	if (nullptr == gameinstance)
	{
		return;
	}
	FCharacterDatas characterDatas = gameinstance->mCharacterDatas;
	characterDatas.mTribe = InTribe;

	ANetworkCharacter* NewDummyCharacter = nullptr;
	TSubclassOf<ANetworkCharacter> dummyTribe = mDummyCharacterClass[InTribe];
	if (dummyTribe)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector CharacterLocation(100.0f, 0.0f, 520.0f);
		FRotator CharacterRotation(0.0f, -180.0f, 0.0f);

		NewDummyCharacter = GetWorld()->SpawnActor<ANetworkCharacter>(dummyTribe, CharacterLocation, CharacterRotation, spawnParams);
		NewDummyCharacter->UpdateCharacterData(characterDatas);
	}

	if (mDummyCharacter)
	{
		mDummyCharacter->Destroy();
	}

	mDummyCharacter = NewDummyCharacter;

}
