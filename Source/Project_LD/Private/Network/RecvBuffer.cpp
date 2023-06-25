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

int32 FRecvBuffer::GetWritePos() const
{
	return mWritePos;
}

int32 FRecvBuffer::GetReadPos() const
{
	return mReadPos;
}

int32 FRecvBuffer::GetMaxReadBytes(const int32 inPendingDataSize)
{
	return ((GetWritePos() + inPendingDataSize) > GetTotalSize()) ? GetTotalSize() - GetWritePos() : inPendingDataSize;
}

void FRecvBuffer::Clear()
{
	::memset(mBuffer, NULL, mCapcity);
	mWritePos = 0;
	mReadPos = 0;
}

void FRecvBuffer::MoveRear(const int32 size)
{
	mWritePos = (mWritePos + size) & mIndexMask;
}

void FRecvBuffer::MoveFront(const int32 len)
{
	mReadPos = (mReadPos + len) & mIndexMask;
}

int32 FRecvBuffer::Enqueue(const BYTE* data, const int32 size)
{
	int32 processSize = 0;
	if (GetFreeSize() < size)
	{
		return processSize;
	}
	
	const int32 PrevWritePos = GetWritePos();
	const int32 IsOverBuffer = (PrevWritePos + size) > GetTotalSize() ? 1 : 0;
	if (IsOverBuffer)
	{
		const int32 OverLen = (PrevWritePos + size) - GetTotalSize();
		const int32 LessLen = size - OverLen;
		const int32 UsedLen = OverLen + LessLen;

		::memcpy(&GetBuffer()[PrevWritePos], &data[0], LessLen);
		::memcpy(&GetBuffer()[0], &data[LessLen], OverLen);
		MoveRear(UsedLen);
		processSize += UsedLen;
	}
	else
	{
		::memcpy(&GetBuffer()[PrevWritePos], data, size);
		MoveRear(size);
		processSize += size;
	}

	return processSize;
}

int32 FRecvBuffer::Dequeue(BYTE* dest, const int32 len)
{
	int32 processSize = 0;
	if (GetUsedSize() < len)
	{
		return processSize;
	}

	const int32 PrevReadPos = GetReadPos();
	const int32 IsOverBuffer = (PrevReadPos + len) > GetTotalSize() ? 1 : 0;
	if (IsOverBuffer)
	{
		const int32 OverLen = (PrevReadPos + len) - GetTotalSize();
		const int32 LessLen = len - OverLen;
		const int32 UsedLen = OverLen + LessLen;

		::memcpy(dest, &GetBuffer()[PrevReadPos], LessLen);
		::memcpy(&dest[LessLen], &GetBuffer()[0], OverLen);
		MoveFront(OverLen + LessLen);
		processSize += UsedLen;
	}
	else
	{
		::memcpy(dest, &GetBuffer()[PrevReadPos], len);
		MoveFront(len);
		processSize += len;
	}

	return processSize;
}

int32 FRecvBuffer::Peek(BYTE* dest, const int32 len)
{
	int32 processSize = 0;
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
		const int32 UsedLen = OverLen + LessLen;

		::memcpy(dest, &GetBuffer()[PrevReadPos], LessLen);
		::memcpy(&dest[LessLen], &GetBuffer()[0], OverLen);
		processSize += UsedLen;
	}
	else
	{
		::memcpy(dest, &mBuffer[PrevReadPos], len);
		processSize += len;
	}

	return processSize;
}


inline int32 FRecvBuffer::GetUsedSize() const
{
	int32 usedSize = 0;
	if (GetWritePos() == GetReadPos())
	{
		usedSize = 0;
	}
	else if (GetWritePos() > GetReadPos())
	{
		usedSize = GetWritePos() - GetReadPos();
	}
	else if (GetWritePos() < GetReadPos())
	{
		usedSize = GetTotalSize() - (GetReadPos() - GetWritePos());
	}

	return usedSize;
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
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("[TOTAL : %5d] [USE : %5d], [FREE : %5d], [WRITE : %5d], [READ : %5d], [MAX_READ : %5d]"), GetTotalSize(), GetUsedSize(), GetFreeSize(), mWritePos, mReadPos, GetTotalSize() - GetWritePos()), ELogLevel::Log);
}
