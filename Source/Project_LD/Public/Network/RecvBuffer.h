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
	FRecvBuffer(const uint32 inBufferSize);
	~FRecvBuffer();

public:
	BYTE*			GetBuffer();
	BYTE*			GetReadBuffer();
	BYTE*			GetWriteBuffer();
	int32			GetMaxReadBytes(const uint32 inPendingDataSize);

public:
	void			Claer();
	void			MoveRear(const uint32 size);
	void			MoveFront(const uint32 len);
	uint32			Enqueue(const BYTE* data, const uint32 size);
	uint32			Dequeue(BYTE* dest, const uint32 len);
	uint32			Peek(BYTE* dest, const uint32 len);

public:
	uint32			GetUsedSize() const;
	uint32			GetTotalSize() const;
	uint32			GetFreeSize() const;

public:
	void			TestPrintLog();

private:
	uint32			mWritePos;
	uint32			mIndexMask;
	uint32			mReadPos;
	uint32			mBufferSize;
	BYTE*			mBuffer;
};
