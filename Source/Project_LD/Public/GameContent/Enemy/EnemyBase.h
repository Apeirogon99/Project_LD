// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Struct/Game/EnemyData.h>
#include "Framework/Interface/InteractiveInterface.h"
#include "EnemyBase.generated.h"


UCLASS()
class PROJECT_LD_API AEnemyBase : public ACharacter, public IInteractiveInterface
{
	GENERATED_BODY()

public:
	AEnemyBase();
	~AEnemyBase();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Destroyed() override;

public:
	void ChangeState(const EEnemyStateType inStateType, float inStartTime);
	
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Interactive(AC_Game* inPlayer) override;

};
