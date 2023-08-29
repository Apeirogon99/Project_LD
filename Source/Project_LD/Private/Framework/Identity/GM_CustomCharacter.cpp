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
	UUserWidget* outWidget = mClientHUD->GetWidgetFromName(TEXT("CustomCharacter"));
	if (outWidget == nullptr)
	{
		return;
	}

	widget = Cast<UW_CustomCharacter>(outWidget);
	if (widget == nullptr)
	{
		return;
	}

	widget->SetClassText(gameinstance->mCharacterData.GetClass());
	mClientHUD->ShowWidgetFromName(TEXT("CustomCharacter"));

	this->GetNetworkController()->OnTick();

}

void AGM_CustomCharacter::InitNetwork()
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

void AGM_CustomCharacter::CreateNewDummyCharacter(const ECharacterRace InRace)
{
	this->mClientHUD->FadeIn();

	ULDGameInstance* gameinstance = Cast<ULDGameInstance>(GetWorld()->GetGameInstance());
	if (nullptr == gameinstance)
	{
		return;
	}
	gameinstance->mCharacterData.GetAppearance().SetRace(InRace);

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
		NewDummyCharacter->InitCharacterVisual(gameinstance->mCharacterData.GetAppearance(), gameinstance->mCharacterData.GetEquipment());
		//NewDummyCharacter->InitializeAppearance();
	}

	if (mDummyCharacter)
	{
		mDummyCharacter->Destroy();
	}

	mDummyCharacter = NewDummyCharacter;


	UW_CustomCharacter* widget = nullptr;
	UUserWidget* outWidget = mClientHUD->GetWidgetFromName(TEXT("CustomCharacter"));
	if (outWidget == nullptr)
	{
		return;
	}

	widget = Cast<UW_CustomCharacter>(outWidget);
	if (widget == nullptr)
	{
		return;
	}

	widget->SetDummyCharacter(mDummyCharacter);

	this->mClientHUD->FadeOut();
}
