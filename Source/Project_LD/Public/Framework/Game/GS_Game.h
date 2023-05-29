// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkGameState.h"
#include "GS_Game.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AGS_Game : public ANetworkGameState
{
	GENERATED_BODY()

public:
	AGS_Game();
	~AGS_Game();

public:
	AActor*		CreateGameObject(UClass* inUClass, FVector inLocation, FRotator inRotator, const int64 inGameObjectID);
	AActor*		FindGameObject(const int64 inGameObject);
	int32		RemoveGameObject(const int64 inGameObjectID);

	AController*	FindPlayerController(const int64 inRemoteID);
	
private:
	TMap<int64, AActor*> mGameObjects;
};
