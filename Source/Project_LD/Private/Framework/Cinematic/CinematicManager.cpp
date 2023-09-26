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
			LevelSequenceActor;
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

		LevelSequenceActor = nullptr;
		LevelSequencePlayer = nullptr;
	}
}
