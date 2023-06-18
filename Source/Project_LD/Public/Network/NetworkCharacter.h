// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Struct/Game/CharacterDatas.h>
#include "NetworkCharacter.generated.h"

UCLASS()
class PROJECT_LD_API ANetworkCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANetworkCharacter();
	virtual ~ANetworkCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
