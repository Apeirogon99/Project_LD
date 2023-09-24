// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Cinematic/CinematicManager.h"
#include <LevelSequence/Public/LevelSequenceActor.h>
#include <LevelSequence/Public/LevelSequencePlayer.h>
#include <Kismet/GameplayStatics.h>

UCinematicManager::UCinematicManager()
{
	mCurrentNum = -1;
}

UCinematicManager::~UCinematicManager()
{
}

void UCinematicManager::Init()
{
	TArray<AActor*> Cinematicas;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelSequenceActor::StaticClass(), Cinematicas);

	for (AActor* Actor : Cinematicas)
	{
		mCinematica.Push(Cast<ALevelSequenceActor>(Actor));
	}
}

void UCinematicManager::Play(int32 InCinematicNumber)
{
	// 1, 2, 3, 4
	mCurrentNum = InCinematicNumber;
	mCinematica[InCinematicNumber]->SequencePlayer->Play();
}

void UCinematicManager::End()
{
	if (mCurrentNum == -1)
	{
		return;
	}

	mCinematica[mCurrentNum]->GetSequencePlayer()->Stop();
	mCurrentNum = -1;
}
