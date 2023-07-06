// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Containers/CircularBuffer.h>

/**
 * 
 */

class FSendBuffer;
using FSendBufferPtr = TSharedPtr<class FSendBuffer>;

class PROJECT_LD_API FSendBufferQueue
{
	enum class Default
	{
		MAX_QUEUE_SIZE = 0x1000,
	};

public:
	FSendBufferQueue();
	FSendBufferQueue(const uint32 inQueueSize);
	~FSendBufferQueue();

public:
	void		Clear();
	void		Push(FSendBufferPtr FSendBuffer);
	void		PopAll(TArray<FSendBufferPtr>& FSendBuffers);
	bool		IsEmpty();
	bool		IsFull();

private:
	FRWLock		mLock;
	uint32		mHead;
	uint32		mTail;

	TCircularBuffer<FSendBufferPtr> mSendBufferQueue;
};
