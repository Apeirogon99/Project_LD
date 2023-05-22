// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/SendBufferQueue.h"
#include <Network/SendBuffer.h>

FSendBufferQueue::FSendBufferQueue() : mSendBufferQueue(static_cast<uint32>(Default::MAX_QUEUE_SIZE))
{
	mHead = 0;
	mTail = 0;
}

FSendBufferQueue::FSendBufferQueue(const uint32 inQueueSize) : mSendBufferQueue(inQueueSize)
{
	mHead = 0;
	mTail = 0;
}

FSendBufferQueue::~FSendBufferQueue()
{
}

void FSendBufferQueue::Clear()
{
	FRWScopeLock lock(mLock, SLT_Write);
	while (mHead != mTail)
	{
		mSendBufferQueue[mTail].Reset();
		mTail = mSendBufferQueue.GetNextIndex(mTail);
	}
}

void FSendBufferQueue::Push(FSendBufferPtr inSendBuffer)
{
	FRWScopeLock lock(mLock, SLT_Write);
	if (true == IsFull())
	{
		return;
	}

	mSendBufferQueue[mHead] = MoveTemp(inSendBuffer);
	mHead = mSendBufferQueue.GetNextIndex(mHead);
}

void FSendBufferQueue::PopAll(TArray<FSendBufferPtr>& FSendBuffers)
{
	FRWScopeLock lock(mLock, SLT_Write);
	while (false == IsEmpty())
	{
		FSendBufferPtr OutFSendBuffer = MoveTemp(mSendBufferQueue[mTail]);
		mTail = mSendBufferQueue.GetNextIndex(mTail);
		FSendBuffers.Emplace(OutFSendBuffer);
	}

}

bool FSendBufferQueue::IsEmpty()
{
	return (mHead == mTail);
}

bool FSendBufferQueue::IsFull()
{
	const uint32 NextHead = mSendBufferQueue.GetNextIndex(mHead);
	return (NextHead == mTail);
}
