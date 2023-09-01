// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkGameState.h"
#include "PS_Game.h"
#include "GS_Game.generated.h"

class AAppearanceCharacter;
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
	AActor*		CreateNPCCharacter(FVector inLocation, FRotator inRotator, FCharacterData& inCharacterData, const int64 inRemoteID);
	AActor*		CreateEnemyCharacter(const int32 inEnemyID, FVector inLocation, FRotator inRotator, const int64 inGameObjectID);
	AActor*		CreateGameObject(UClass* inUClass, FVector inLocation, FRotator inRotator, const int64 inGameObjectID);
	AActor*		CreateDarkKnightSkill(const int64 inLichSkillID, FVector inLocation, FRotator inRotator, const int64 inGameObjectID);
	AActor*		CreateLichSkill(const int64 inLichSkillID, FVector inLocation, FRotator inRotator, const int64 inGameObjectID);
	AActor*		FindGameObject(const int64 inGameObject);
	bool				RemoveGameObject(const int64 inGameObjectID);

	UFUNCTION(BlueprintCallable, Category = "NetworkGameState")
	AController*			FindPlayerController(const int64 inRemoteID);

	AAppearanceCharacter*	GetPreviewCharacter();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameState", meta = (AllowPrivateAccess = "true"))
	TMap<int64, AActor*> mGameObjects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LichSkillClass", meta = (AllowPrivateAccess = "true"))
	TArray<UClass*> mLichSkillClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LichSkillClass", meta = (AllowPrivateAccess = "true"))
	TArray<UClass*> mDarkKnightSkillClass;
};
