// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill_Parent.generated.h"

UCLASS()
class PROJECT_LD_API ASkill_Parent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_Parent();

public:
	void SetRemoteID(const int64& InRemoteID)	{ mRemoteID = InRemoteID; }
	void SetObjectID(const int64& InObjectID)		{ mObjectID = InObjectID; }
	void SetSkillID(const int32& InSkillID)			{ mSkillID = InSkillID; }

public:
	int64 GetRemoteID()const		{ return mRemoteID; }
	int64 GetObjectID() const		{ return mObjectID; }
	int32 GetSkillID() const			{ return mSkillID; }

public:
	virtual void AppearSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration);
	virtual void ReactionSkill(const int64 InRemoteID, const int64 InObjectID, const int32 InSkillID, const FVector InLocation, const FRotator InRotation, const float InDuration);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int64 mRemoteID;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int64 mObjectID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 mSkillID;
};
