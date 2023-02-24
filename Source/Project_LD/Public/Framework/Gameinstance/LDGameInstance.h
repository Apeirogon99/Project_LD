// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <Struct/Game/CharacterDatas.h>
#include "LDGameInstance.generated.h"

class UDataTable;
struct FItemData;

/**
 * 
 */
UCLASS()
class PROJECT_LD_API ULDGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	ULDGameInstance();
	~ULDGameInstance();

public:

	UPROPERTY(BlueprintReadOnly, Category = "Network")
		FString mTicket;

	UPROPERTY()
	FCharacterDatas mCharacterDatas;

	UPROPERTY()
	FCharacterAppearance mCharacterAppearance;

public:
	FItemData* GetItemData(int32 inCode);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* mGameItemDataTable;
};
