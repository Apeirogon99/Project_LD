// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Skill/Skill_Parent.h"

// Sets default values
ASkill_Parent::ASkill_Parent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

}

void ASkill_Parent::AppearSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration)
{
}

void ASkill_Parent::ReactionSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration)
{
}

// Called when the game starts or when spawned
void ASkill_Parent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

