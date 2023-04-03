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

	CreateNewDummyCharacter(StaticCast<int32>(ERace::Male));

	UW_CustomCharacter* customWidget = Cast<UW_CustomCharacter>(mClientHUD->GetWidgetFromName(TEXT("CustomCharacter")));
	customWidget->SetClassText(gameinstance->mCharacterAppearance.mCharacterClass);
	mClientHUD->ShowWidgetFromName(TEXT("CustomCharacter"));
}

void AGM_CustomCharacter::CreateNewDummyCharacter(int32 InRace)
{
	ULDGameInstance* gameinstance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	if (nullptr == gameinstance)
	{
		return;
	}
	gameinstance->mCharacterAppearance.mRace = InRace;

	ANetworkCharacter* NewDummyCharacter = nullptr;
	TSubclassOf<ANetworkCharacter> raceClass = mDummyCharacterClass[InRace];
	if (raceClass)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector CharacterLocation(100.0f, 0.0f, 520.0f);
		FRotator CharacterRotation(0.0f, -180.0f, 0.0f);

		NewDummyCharacter = GetWorld()->SpawnActor<ANetworkCharacter>(raceClass, CharacterLocation, CharacterRotation, spawnParams);
		NewDummyCharacter->mCharacterAppearance = gameinstance->mCharacterAppearance;
		NewDummyCharacter->UpdateCharacterEquipment(FCharacterEquipment());
		//NewDummyCharacter->UpdateCharacterAppearnce(characterAppearance);
		//NewDummyCharacter->ConstructCharacter();
	}

	if (mDummyCharacter)
	{
		mDummyCharacter->Destroy();
	}

	mDummyCharacter = NewDummyCharacter;

}
