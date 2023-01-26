// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Containers/CircularBuffer.h>
#include <Network/SendBuffer.h>

/**
 * 
 */
class PROJECT_LD_API USendBufferQueue
{
	//GENERATED_BODY()

public:
	USendBufferQueue(const FObjectInitializer& init);
	USendBufferQueue(const uint32 inQueueSize = 0x400);
	~USendBufferQueue();

public:
	void		Push(SendBufferPtr sendBuffer);
	void		PopAll(TArray<SendBufferPtr>& sendBuffers);
	bool		IsEmpty();
	bool		IsFull();

private:
	FRWLock		mLock;
	uint32		mHead;
	uint32		mTail;

	TCircularBuffer<SendBufferPtr> mSendBufferQueue;
};
