// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ACPartyComponent.h"

#include <Widget/Handler/ClientHUD.h>
#include <Widget/Game/Main/W_MainGame.h>
#include <Widget/Game/Party/W_PartyMain.h>

#include <Game/GM_Game.h>
#include <Game/GS_Game.h>
#include <Game/PS_Game.h>

// Sets default values for this component's properties
UACPartyComponent::UACPartyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UACPartyComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UACPartyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (mPartyPlayers.Num())
	{
		this->UpdatePartyInfos();
	}
}

bool UACPartyComponent::CreateParty()
{
	APS_Game* onwer = StaticCast<APS_Game*>(this->GetOwner());
	if (nullptr == onwer)
	{
		return false;
	}

	const int64& remoteID = onwer->GetRemoteID();
	FCharacterData	characterData = onwer->GetCharacterData();

	FPartyPlayerInfo partyPlayerInfo;
	partyPlayerInfo.SetValid(true);
	partyPlayerInfo.SetLevel(characterData.GetLevel());
	partyPlayerInfo.SetClass(characterData.GetClass());
	partyPlayerInfo.SetName(characterData.GetName());

	mPartyPlayers.Add(remoteID, partyPlayerInfo);
	return true;
}

void UACPartyComponent::EnterParty(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName)
{
	FPartyPlayerInfo partyPlayerInfo;
	partyPlayerInfo.SetLevel(inLevel);
	partyPlayerInfo.SetClass(StaticCast<ECharacterClass>(inClass));
	partyPlayerInfo.SetName(inPlayerName);

	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
	if (nullptr == gameState)
	{
		return;
	}

	AController* controller = gameState->FindPlayerController(inRemoteID);
	partyPlayerInfo.SetValid((controller != nullptr) ? true : false);

	mPartyPlayers.Add(inRemoteID, partyPlayerInfo);

}

void UACPartyComponent::LeaveParty(const int64& inRemoteID)
{
	mPartyPlayers.Remove(inRemoteID);
}

void UACPartyComponent::ClearParty()
{
	mPartyPlayers.Empty();
}

void UACPartyComponent::UpdatePartyInfos()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
	if (nullptr == gameState)
	{
		return;
	}

	for (auto& partyPlayerInfo : mPartyPlayers)
	{

		AController* controller = gameState->FindPlayerController(partyPlayerInfo.Key);
		if (nullptr == controller)
		{
			partyPlayerInfo.Value.SetValid(false);
			continue;
		}

		ANPS_Game* playerState = controller->GetPlayerState<ANPS_Game>();
		if (nullptr == playerState)
		{
			partyPlayerInfo.Value.SetValid(false);
			continue;
		}

		const int64&	remoteID = playerState->GetRemoteID();
		FCharacterData	characterData = playerState->GetCharacterData();

		partyPlayerInfo.Value.SetLevel(characterData.GetLevel());
		partyPlayerInfo.Value.SetClass(characterData.GetClass());
		partyPlayerInfo.Value.SetName(characterData.GetName());
	}
}

bool UACPartyComponent::GetPartyPlayers(TArray<APlayerState*>& outPartyPlayers, TArray<FPartyPlayerInfo>& outPartyPlayerInfos)
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return false;
	}

	AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
	if (nullptr == gameState)
	{
		return false;
	}

	for (const auto& partyPlayerInfo : mPartyPlayers)
	{

		outPartyPlayerInfos.Push(partyPlayerInfo.Value);

		AController* controller = gameState->FindPlayerController(partyPlayerInfo.Key);
		if (nullptr == controller)
		{
			outPartyPlayers.Push(nullptr);
			continue;
		}

		ANPS_Game* playerState =  controller->GetPlayerState<ANPS_Game>();
		if (nullptr == playerState)
		{
			outPartyPlayers.Push(nullptr);
			continue;
		}

		outPartyPlayers.Push(playerState);
	}

	return (outPartyPlayers.Num()) ? true : false;
}

