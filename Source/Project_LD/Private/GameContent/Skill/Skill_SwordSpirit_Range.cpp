// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Skill/Skill_SwordSpirit_Range.h"

// Sets default values
ASkill_SwordSpirit_Range::ASkill_SwordSpirit_Range()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ChargeCount = 0;
}

void ASkill_SwordSpirit_Range::InCreaseCount()
{
	if (ChargeCount <= 2)
	{
		ChargeCount++;
	}
}

// Called every frame
void ASkill_SwordSpirit_Range::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void ASkill_SwordSpirit_Range::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle ChargeTimer;

	GetWorldTimerManager().SetTimer(ChargeTimer, this, &ASkill_SwordSpirit_Range::InCreaseCount, 1.f, true);
}


