// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameContent/Item/ItemParent.h"
#include "Test_SubItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API ATest_SubItem : public AItemParent
{
	GENERATED_BODY()
	
public:
	ATest_SubItem();

	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;
};
