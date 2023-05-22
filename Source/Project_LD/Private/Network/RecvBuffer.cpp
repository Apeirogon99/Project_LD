// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/RecvBuffer.h"
#include <Network/NetworkUtils.h>
#include <Containers/CircularBuffer.h>

FRecvBuffer::FRecvBuffer() : mWritePos(0), mReadPos(0)
{
	InitBuffer(0x1000);
}

FRecvBuffer::FRecvBuffer(const int32 inCapcity) : mWritePos(0), mReadPos(0)
{
	InitBuffer(inCapcity);
}

FRecvBuffer::~FRecvBuffer()
{

}

void FRecvBuffer::InitBuffer(const int32 inCapcity)
{
	if (inCapcity > UINT16_MAX)
	{
		UNetworkUtils::NetworkConsoleLog("[FRecvBuffer::InitBuffer] : It's too big to make", ELogLevel::Error);
		return;
	}

	int32 newCapcity = 0;
	if (!((inCapcity & (inCapcity - 1)) == 0))
	{
		newCapcity = static_cast<int32>(pow(2, floor(log2(inCapcity)) + 1));
	}
	else
	{
		newCapcity = static_cast<int32>(inCapcity);
	}


	mCapcity = newCapcity;
	mIndexMask = newCapcity - 1;
	mBuffer = new BYTE[newCapcity]();
	Clear();
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

int32 FRecvBuffer::GetMaxReadBytes(const int32 inPendingDataSize)
{
	const int32 PrevWritePos = mWritePos;
	const bool IsOverBuffer = (mWritePos + inPendingDataSize) > GetTotalSize() ? true : false;
	if (IsOverBuffer)
	{
		const int32 OverLen = (PrevWritePos + inPendingDataSize) - GetTotalSize();
		const int32 LessLen = inPendingDataSize - OverLen;
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
	::memset(mBuffer, NULL, mCapcity);
	mWritePos = 0;
	mReadPos = 0;
}

void FRecvBuffer::MoveRear(const int32 size)
{
	mWritePos = (mWritePos + size) % GetTotalSize();
}

void FRecvBuffer::MoveFront(const int32 len)
{
	mReadPos = (mReadPos + len) % GetTotalSize();
}

int32 FRecvBuffer::Enqueue(const BYTE* data, const int32 size)
{
	if (GetFreeSize() < size)
	{
		return 0;
	}
	
	const int32 PrevWritePos = mWritePos;
	const int32 IsOverBuffer = (PrevWritePos + size) > GetTotalSize() ? 1 : 0;
	if (IsOverBuffer)
	{
		const int32 OverLen = (PrevWritePos + size) - GetTotalSize();
		const int32 LessLen = size - OverLen;

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

int32 FRecvBuffer::Dequeue(BYTE* dest, const int32 len)
{
	if (GetUsedSize() < len)
	{
		return 0;
	}

	const int32 PrevReadPos = mReadPos;
	const int32 IsOverBuffer = (PrevReadPos + len) > GetTotalSize() ? 1 : 0;
	if (IsOverBuffer)
	{
		const int32 OverLen = (PrevReadPos + len) - GetTotalSize();
		const int32 LessLen = len - OverLen;

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

int32 FRecvBuffer::Peek(BYTE* dest, const int32 len)
{
	if (GetUsedSize() < len)
	{
		return 0;
	}

	const int32 PrevReadPos = mReadPos;
	const bool IsOverBuffer = (PrevReadPos + len) > GetTotalSize() ? true : false;
	if (IsOverBuffer)
	{
		const int32 OverLen = (PrevReadPos + len) - GetTotalSize();
		const int32 LessLen = len - OverLen;

		::memcpy(dest, &mBuffer[PrevReadPos], LessLen);
		::memcpy(&dest[LessLen], &mBuffer[0], OverLen);
	}
	else
	{
		::memcpy(dest, &mBuffer[PrevReadPos], len);
	}

	return len;
}


inline int32 FRecvBuffer::GetUsedSize() const
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
	return mCapcity;
}

inline int32 FRecvBuffer::GetTotalSize() const
{
	return mCapcity;
}

inline int32 FRecvBuffer::GetFreeSize() const
{
	return GetTotalSize() - GetUsedSize();
}

void FRecvBuffer::TestPrintLog()
{
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[MAX : %5d] [USE : %5d], [FREE : %5d], [WRITE : %5d], [READ : %5d]"), GetTotalSize() - mWritePos, GetUsedSize(), GetFreeSize(), mWritePos, mReadPos), ELogLevel::Log);
}
