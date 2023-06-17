// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include <Struct/Game/CharacterDatas.h>
#include "NetworkPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API ANetworkPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ANetworkPlayerState();
	~ANetworkPlayerState();
	
public:
	void InitializeCharacterData(const FCharacterData& InCharacterDatas);

public:
	const FCharacterData& GetCharacterData() const { return mCharacterData; }

protected:
	FCharacterData	mCharacterData;
};
