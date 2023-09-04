// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "UObject/Interface.h"
#include "LichSkillBase.generated.h"


UINTERFACE(MinimalAPI)
class ULichSkillBase : public UInterface
{
	GENERATED_BODY()
};

class PROJECT_LD_API ILichSkillBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ILichSkillBase();

public:
	virtual void ActiveSkill(FVector InLocation, FRotator InRotation) {}
	virtual void ReactionSkill(FVector InLocation, FRotator InRotation) {}
	virtual void DeactiveSkill() {}

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//	UParticleSystem* mMainParticle;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//	UParticleSystemComponent* mSpawnedParticle;
};
