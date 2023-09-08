// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameContent/Enemy/Skill/EnemySkillInterface.h>
#include "Skill_SoulSpark.generated.h"

class UNiagaraComponent;

UCLASS()
class PROJECT_LD_API ASkill_SoulSpark : public AActor, public IEnemySkillInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_SoulSpark();

public:
	virtual void ActiveSkill(FVector InLocation, FRotator InRotation) override;
	virtual void ReactionSkill(FVector InLocation, FRotator InRotation) override;
	virtual void DeactiveSkill(FVector InLocation, FRotator InRotation) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* mActiveNiagara;
};
