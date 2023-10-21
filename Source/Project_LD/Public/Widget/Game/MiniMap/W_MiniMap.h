// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_MiniMap.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_MiniMap : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AddPOI(AActor* Actor);
	virtual void AddPOI_Implementation(AActor* Actor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MainMapSetting();
	virtual void MainMapSetting_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InstanceMapSetting();
	virtual void InstanceMapSetting_Implementation();
};