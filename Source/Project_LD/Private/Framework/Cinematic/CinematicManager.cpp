// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Cinematic/CinematicManager.h"
#include <LevelSequence/Public/LevelSequenceActor.h>
#include <LevelSequence/Public/LevelSequencePlayer.h>
#include <LDGameInstance.h>
#include <Kismet/GameplayStatics.h>

UCinematicManager::UCinematicManager()
{
	LevelSequencePlayer = nullptr;
	LevelSequenceActor = nullptr;
}

UCinematicManager::~UCinematicManager()
{
}

void UCinematicManager::Play(int32 InCinematicNumber, UWorld* InWorld)
{
	if ((0 < InCinematicNumber) && (InCinematicNumber < 5))
	{
		ULDGameInstance* Instance = Cast<ULDGameInstance>(InWorld->GetGameInstance());
		FLevelSequenceDataTable data = *Instance->GetLevelSequenceData(InCinematicNumber);
		ULevelSequence* mSequence = LoadObject<ULevelSequence>(nullptr, *data.GetLevelSequencePath());
		if (mSequence)
		{
			mCurrentWorld = InWorld;
			SceneSpawnActor(InCinematicNumber, InWorld);
			LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(InWorld, mSequence,FMovieSceneSequencePlaybackSettings(),LevelSequenceActor);
			LevelSequencePlayer->Play();
		}
	}
}

void UCinematicManager::End()
{
	if (LevelSequenceActor && LevelSequencePlayer)
	{
		LevelSequencePlayer->Stop();

		DestorySpawnActor();
		LevelSequenceActor = nullptr;
		LevelSequencePlayer = nullptr;
	}
}

void UCinematicManager::SceneSpawnActor(int32 InCinematicNumber, UWorld* InWorld)
{
	UBlueprint* BlueprintObj = nullptr;
	UBlueprint* SmokeObj = nullptr;
	UClass* ActorClass;

	switch (InCinematicNumber)
	{
	case 1:
		BlueprintObj = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, TEXT("Blueprint'/Game/Blueprint/GameContent/CutSceneActor/Scene1Actor.Scene1Actor'")));
		break;
	case 2:
		BlueprintObj = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, TEXT("Blueprint'/Game/Blueprint/GameContent/CutSceneActor/Scene2Actor.Scene2Actor'")));
		break;
	case 3:
		BlueprintObj = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, TEXT("Blueprint'/Game/Blueprint/GameContent/CutSceneActor/Scene3Actor.Scene3Actor'")));
		SmokeObj = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, TEXT("Blueprint'/Game/GameContent/Actor/Smoke/BA_Smoke_Sequence.BA_Smoke_Sequence'")));
		break;
	case 4:
		BlueprintObj = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, TEXT("Blueprint'/Game/Blueprint/GameContent/CutSceneActor/Scene4Actor.Scene4Actor'")));
		break;
	}
	if (BlueprintObj)
	{
		ActorClass = BlueprintObj->GeneratedClass;
		if (nullptr == ActorClass)
		{
			return;
		}
		mSpawnActor = InWorld->SpawnActor<AActor>(ActorClass, FVector(10050, 10050, 201), FRotator(0, 0, 0));
	}
	if (SmokeObj)
	{
		ActorClass = SmokeObj->GeneratedClass;
		if (nullptr == ActorClass)
		{
			return;
		}
		mSmokeActor = InWorld->SpawnActor<AActor>(ActorClass, FVector(10050, 10050, 201), FRotator(0, 0, 0));
	}
}

void UCinematicManager::DestorySpawnActor()
{
	if (mSpawnActor)
	{
		mSpawnActor->Destroy();
		mSpawnActor = nullptr;
	}
	if (mSmokeActor)
	{
		FTimerHandle smokeTimerHandle;
		mCurrentWorld->GetTimerManager().SetTimer(smokeTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			// 코드 구현
			mSmokeActor->Destroy();
			mSmokeActor = nullptr;

			// TimerHandle 초기화
			mCurrentWorld->GetTimerManager().ClearTimer(smokeTimerHandle);
		}), 0.8f, false);
	}
}
