// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Identity/GM_CustomCharacter.h"
#include <Framework/Identity/IdentityPlayerController.h>
#include <Framework/Gameinstance/LDGameInstance.h>

#include <Network/NetworkCharacter.h>
#include <Framework/Character/AppearanceCharacter.h>

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

	CreateNewDummyCharacter(ECharacterRace::Male);

	UW_CustomCharacter* widget = nullptr;
	UUserWidget* outWidget = mClientHUD->GetWidgetFromName(TEXT("Test"));
	if (outWidget == nullptr)
	{
		return;
	}

	widget = Cast<UW_CustomCharacter>(outWidget);
	if (widget == nullptr)
	{
		return;
	}

	widget->SetClassText(gameinstance->mCharacterData.mClass);
	mClientHUD->ShowWidgetFromName(TEXT("CustomCharacter"));
}

void AGM_CustomCharacter::CreateNewDummyCharacter(const ECharacterRace InRace)
{
	ULDGameInstance* gameinstance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	if (nullptr == gameinstance)
	{
		return;
	}
	gameinstance->mCharacterData.mRace = InRace;

	AAppearanceCharacter* NewDummyCharacter = nullptr;
	TSubclassOf<AAppearanceCharacter> raceClass = mDummyCharacterClass[StaticCast<int32>(InRace)];
	if (raceClass)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector CharacterLocation(100.0f, 0.0f, 520.0f);
		FRotator CharacterRotation(0.0f, -180.0f, 0.0f);

		NewDummyCharacter = GetWorld()->SpawnActor<AAppearanceCharacter>(raceClass, CharacterLocation, CharacterRotation, spawnParams);
		NewDummyCharacter->InitializeCharacter(gameinstance->mCharacterData);
		NewDummyCharacter->InitializeAppearance();
	}

	if (mDummyCharacter)
	{
		mDummyCharacter->Destroy();
	}

	mDummyCharacter = NewDummyCharacter;

}
