// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Skill/Skill_Dash.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

ASkill_Dash::ASkill_Dash()
{
}

void ASkill_Dash::AppearSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration)
{
	UE_LOG(LogTemp, Warning, TEXT("Dash Appear"));
}

void ASkill_Dash::ReactionSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration)
{
	UE_LOG(LogTemp, Warning, TEXT("Dash Reaction"));
	if (UNiagaraSystem* Niagara = LoadObject<UNiagaraSystem>(nullptr, TEXT("NiagaraSystem'/Game/GameContent/Animation/Male/Skill/Dash/NS_Dash_Hu_M.NS_Dash_Hu_M'")))
	{
		FVector Vec = InLocation;
		Vec.Y = InLocation.Y + 40.f;
		Vec.Z = InLocation.Z + 70.f;
		FRotator Rot = InRotation;
		Rot.Yaw = Rot.Yaw;
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara, Vec, Rot, FVector(0.35f, 0.02f, 0.02f));
	}
}

void ASkill_Dash::BeginPlay()
{
}

void ASkill_Dash::Destroyed()
{
}

void ASkill_Dash::Tick(float DeltaTime)
{
}
