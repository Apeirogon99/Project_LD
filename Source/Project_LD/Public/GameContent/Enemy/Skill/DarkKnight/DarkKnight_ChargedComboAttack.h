// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DarkKnightSkillBase.h"
#include "DarkKnight_ChargedComboAttack.generated.h"

UCLASS()
class PROJECT_LD_API ADarkKnight_ChargedComboAttack : public AActor, public IDarkKnightSkillBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADarkKnight_ChargedComboAttack();

public:
	virtual void ActiveSkill() override;
	virtual void ReactionSkill() override;
	virtual void DeactiveSkill() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
