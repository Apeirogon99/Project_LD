// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/RecvBuffer.h"
#include <Network/NetworkUtils.h>
#include <Containers/CircularBuffer.h>

FRecvBuffer::FRecvBuffer() : mWritePos(0), mReadPos(0)
{
	mBufferSize = 0x1000;
	mBuffer = new BYTE[mBufferSize];
}

FRecvBuffer::FRecvBuffer(const uint32 inBufferSize) : mWritePos(0), mReadPos(0)
{
	mBufferSize = inBufferSize;
	mBuffer = new BYTE[mBufferSize];
}

FRecvBuffer::~FRecvBuffer()
{

}

BYTE* FRecvBuffer::GetBuffer()
{
	return mBuffer;
}

BYTE* FRecvBuffer::GetReadBuffer()
{
	return &mBuffer[mReadPos];
}

BYTE* FRecvBuffer::GetWriteBuffer()
{
	return &mBuffer[mWritePos];
}

int32 FRecvBuffer::GetMaxReadBytes(const uint32 inPendingDataSize)
{
	const uint32 PrevWritePos = mWritePos;
	const bool IsOverBuffer = (mWritePos + inPendingDataSize) > GetTotalSize() ? true : false;
	if (IsOverBuffer)
	{
		const uint32 OverLen = (PrevWritePos + inPendingDataSize) - GetTotalSize();
		const uint32 LessLen = inPendingDataSize - OverLen;
		return LessLen;
	}
	else
	{
		return inPendingDataSize;
	}

	return inPendingDataSize;
}

void FRecvBuffer::Clear()
{
	::memset(mBuffer, NULL, mBufferSize);
	mWritePos = 0;
	mReadPos = 0;
}

void FRecvBuffer::MoveRear(const uint32 size)
{
	mWritePos = (mWritePos + size) % GetTotalSize();
}

void FRecvBuffer::MoveFront(const uint32 len)
{
	mReadPos = (mReadPos + len) % GetTotalSize();
}

uint32 FRecvBuffer::Enqueue(const BYTE* data, const uint32 size)
{
	if (GetFreeSize() < size)
	{
		return 0;
	}
	
	const uint32 PrevWritePos = mWritePos;
	const int32 IsOverBuffer = (PrevWritePos + size) > GetTotalSize() ? 1 : 0;
	if (IsOverBuffer)
	{
		const uint32 OverLen = (PrevWritePos + size) - GetTotalSize();
		const uint32 LessLen = size - OverLen;

		::memcpy(&mBuffer[PrevWritePos], &data[0], LessLen);
		::memcpy(&mBuffer[0], &data[LessLen], OverLen);
		MoveRear(OverLen + LessLen);
	}
	else
	{
		::memcpy(&mBuffer[PrevWritePos], data, size);
		MoveRear(size);
	}

	return size;
}

uint32 FRecvBuffer::Dequeue(BYTE* dest, const uint32 len)
{
	if (GetUsedSize() < len)
	{
		return 0;
	}

	const uint32 PrevReadPos = mReadPos;
	const int32 IsOverBuffer = (PrevReadPos + len) > GetTotalSize() ? 1 : 0;
	if (IsOverBuffer)
	{
		const uint32 OverLen = (PrevReadPos + len) - GetTotalSize();
		const uint32 LessLen = len - OverLen;

		::memcpy(dest, & mBuffer[PrevReadPos], LessLen);
		::memcpy(&dest[LessLen], &mBuffer[0], OverLen);
		MoveFront(OverLen + LessLen);
	}
	else
	{
		::memcpy(dest, &mBuffer[PrevReadPos], len);
		MoveFront(len);
	}

	return len;
}

uint32 FRecvBuffer::Peek(BYTE* dest, const uint32 len)
{
	if (GetUsedSize() < len)
	{
		return 0;
	}

	const uint32 PrevReadPos = mReadPos;
	const bool IsOverBuffer = (PrevReadPos + len) > GetTotalSize() ? true : false;
	if (IsOverBuffer)
	{
		const uint32 OverLen = (PrevReadPos + len) - GetTotalSize();
		const uint32 LessLen = len - OverLen;

		::memcpy(dest, &mBuffer[PrevReadPos], LessLen);
		::memcpy(&dest[LessLen], &mBuffer[0], OverLen);
	}
	else
	{
		::memcpy(dest, &mBuffer[PrevReadPos], len);
	}

	return len;
}


inline uint32 FRecvBuffer::GetUsedSize() const
{
	if (mWritePos == mReadPos)
	{
		return 0;
	}
	else if (mWritePos > mReadPos)
	{
		return mWritePos - mReadPos;
	}
	else if (mWritePos < mReadPos)
	{
		return GetTotalSize() - (mReadPos - mWritePos);
	}

	wprintf(L"RingBuffer::GetAllocated()");
	return mBufferSize;
}

inline uint32 FRecvBuffer::GetTotalSize() const
{
	return mBufferSize;
}

inline uint32 FRecvBuffer::GetFreeSize() const
{
	return GetTotalSize() - GetUsedSize();
}

void FRecvBuffer::TestPrintLog()
{
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[MAX : %5d] [USE : %5d], [FREE : %5d], [WRITE : %5d], [READ : %5d]"), GetTotalSize() - mWritePos, GetUsedSize(), GetFreeSize(), mWritePos, mReadPos), ELogLevel::Log);
}
