// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill_Parent.h"
#include "Skill_SwordSpirit_Range.generated.h"

UCLASS()
class PROJECT_LD_API ASkill_SwordSpirit_Range : public ASkill_Parent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_SwordSpirit_Range();

public:
	void InCreaseCount();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 ChargeCount;
};
