// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACPointOfInterest.generated.h"

class UTexture2D;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class PROJECT_LD_API UACPointOfInterest : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACPointOfInterest();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStatic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconImage;

private:
	void Init();
};
