// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PointOfInterest.generated.h"

/**
 * 
 */
class UUserWidget;
class ACharacter;

UCLASS()
class PROJECT_LD_API UW_PointOfInterest : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UFUNCTION(BlueprintCallable)
	void GetMinMapWidget(UUserWidget*& InWidget);

	UFUNCTION(BlueprintCallable)
	ACharacter* GetLocalPlayerCharacter();
};
