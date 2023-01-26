// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECT_LD_API URecvBuffer
{
	
public:
	URecvBuffer();
	URecvBuffer(const uint32 inBufferSize);
	~URecvBuffer();

public:
	BYTE*	GetBuffer();
	BYTE*	GetReadBuffer();
	BYTE*	GetWriteBuffer();

public:
	void	MoveRear(const uint32 size);
	void	MoveFront(const uint32 len);
	uint32	Enqueue(const BYTE* data, const uint32 size);
	uint32	Dequeue(BYTE* dest, const uint32 len);
	uint32	Peek(BYTE* dest, const uint32 len);

protected:
	uint32	GetUsedSize() const;
	uint32	GetTotalSize() const;
	uint32	GetFreeSize() const;

private:
	uint32	mWritePos;
	uint32	mReadPos;
	uint32	mBufferSize;
	BYTE*	mBuffer;
};
