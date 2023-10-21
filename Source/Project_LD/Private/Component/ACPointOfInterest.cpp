// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ACPointOfInterest.h"
#include <Widget/Handler/ClientHUD.h>
#include <GM_Game.h>
#include <Game/MiniMap/W_MiniMap.h>

// Sets default values for this component's properties
UACPointOfInterest::UACPointOfInterest()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	IsStatic = false;
	IconImage = nullptr;
}


// Called when the game starts
void UACPointOfInterest::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FTimerHandle BeginTimer;
	GetWorld()->GetTimerManager().SetTimer(BeginTimer, this, &UACPointOfInterest::Init, 0.2f, false);
}


// Called every frame
void UACPointOfInterest::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UACPointOfInterest::Init()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
	if (nullptr == gameMode)
	{
		return;
	}

	AClientHUD* clientHUD = Cast<AClientHUD>(gameMode->GetClientHUD());
	if (nullptr == clientHUD)
	{
		return;
	}

	UUserWidget* widget = clientHUD->GetWidgetFromName(TEXT("MiniMap"));
	if (nullptr == widget)
	{
		return;
	}

	UW_MiniMap* mapWidget = Cast<UW_MiniMap>(widget);
	if (nullptr == mapWidget)
	{
		return;
	}

	mapWidget->AddPOI(GetOwner());
}

