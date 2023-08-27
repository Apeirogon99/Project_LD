// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Struct/Game/CharacterDatas.h>
#include "ACPartyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_LD_API UACPartyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UACPartyComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	bool CreateParty();
	void EnterParty(const int64& inRemoteID, const int32& inLevel, const int32& inClass, const FString& inPlayerName);
	void LeaveParty(const int64& inRemoteID);
	void ClearParty();
	void UpdatePartyInfos();

public:
	bool GetPartyPlayers(TArray<APlayerState*>& outPartyPlayers, TArray<FPartyPlayerInfo>& outPartyPlayerInfos);
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data", meta = (AllowPrivateAccess = "true"))
	TMap<int64, FPartyPlayerInfo> mPartyPlayers;
};
