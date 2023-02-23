// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkGameMode.h"
#include "GM_CustomCharacter.generated.h"

class ANetworkCharacter;
/**
 * 
 */
UCLASS()
class PROJECT_LD_API AGM_CustomCharacter : public ANetworkGameMode
{
	GENERATED_BODY()
		
public:
	AGM_CustomCharacter();
	virtual ~AGM_CustomCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void BeginNetwork() override;

public:
	UFUNCTION(BlueprintCallable)
	void CreateNewDummyCharacter(int32 InTribe);
	
public:
	UPROPERTY(EditAnywhere, Category = "DummyClass")
	TArray<TSubclassOf<ANetworkCharacter>> mDummyCharacterClass;

	ANetworkCharacter* mDummyCharacter;
};
