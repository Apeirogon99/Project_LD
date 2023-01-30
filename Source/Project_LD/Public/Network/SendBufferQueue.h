// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Containers/CircularBuffer.h>

/**
 * 
 */

class FSendBuffer;
using SendBufferPtr = TSharedPtr<class FSendBuffer>;

class PROJECT_LD_API FSendBufferQueue
{
	enum class Default
	{
		MAX_QUEUE_SIZE = 0x400,
	};

public:
	FSendBufferQueue();
	FSendBufferQueue(const uint32 inQueueSize);
	~FSendBufferQueue();

public:
	void		Push(SendBufferPtr FSendBuffer);
	void		PopAll(TArray<SendBufferPtr>& FSendBuffers);
	bool		IsEmpty();
	bool		IsFull();

private:
	FRWLock		mLock;
	uint32		mHead;
	uint32		mTail;

	TCircularBuffer<SendBufferPtr> mSendBufferQueue;
};
