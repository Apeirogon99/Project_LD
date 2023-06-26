// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_ItemName.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UW_ItemName : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* mName;

public:
	void SetNameText(const FString& inName);

protected:
	virtual void NativeConstruct() override;
};
