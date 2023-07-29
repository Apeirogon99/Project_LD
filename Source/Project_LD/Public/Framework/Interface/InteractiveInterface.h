// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include <Game/C_Game.h>
#include "InteractiveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractiveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_LD_API IInteractiveInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	virtual void Interactive(ANC_Game* Player) = 0;


};