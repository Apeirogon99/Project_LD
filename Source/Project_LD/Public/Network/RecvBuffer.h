// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Containers/Array.h>

/**
 * 
 */
class PROJECT_LD_API FRecvBuffer
{
	
public:
	FRecvBuffer();
	FRecvBuffer(const int32 inCapcity);
	~FRecvBuffer();

protected:
	void InitBuffer(const int32 inCapcity);

public:
	BYTE*			GetBuffer();
	BYTE*			GetReadBuffer();
	BYTE*			GetWriteBuffer();
	int32			GetMaxReadBytes(const int32 inPendingDataSize);

public:
	void			Clear();
	void			MoveRear(const int32 size);
	void			MoveFront(const int32 len);
	int32			Enqueue(const BYTE* data, const int32 size);
	int32			Dequeue(BYTE* dest, const int32 len);
	int32			Peek(BYTE* dest, const int32 len);

public:
	int32			GetUsedSize() const;
	int32			GetTotalSize() const;
	int32			GetFreeSize() const;

public:
	void			TestPrintLog();

private:
	int32			mWritePos;
	int32			mIndexMask;
	int32			mReadPos;
	int32			mCapcity;
	BYTE*			mBuffer;
};
