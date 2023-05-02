// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network/NetworkController.h"
#include "GameCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API AGameCharacterController : public ANetworkController
{
	GENERATED_BODY()
	
public:
	AGameCharacterController();
	virtual ~AGameCharacterController();

protected:
	uint32 bMoveToMouseCursor : 1;

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	//마우스 위치 추적(Tick)
	void MoveToMouseCursor();

	void SetNewMoveDestination(const FVector DestLocation);
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
};
