// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/SendBuffer.h"


FSendBuffer::FSendBuffer()
{
	mBuffer.Init(NULL, 0);
}

FSendBuffer::FSendBuffer(const uint32 inDataSize)
{
	mBuffer.Init(NULL, inDataSize);
}

FSendBuffer::FSendBuffer(const FSendBuffer& inSendBuffer)
{
	mBuffer = inSendBuffer.mBuffer;
}

FSendBuffer& FSendBuffer::operator=(const FSendBuffer& inSendBuffer)
{
	mBuffer = inSendBuffer.mBuffer;
	return *this;
}

FSendBuffer::FSendBuffer(FSendBuffer&& inSendBuffer)
{
	mBuffer = inSendBuffer.mBuffer;
}

FSendBuffer& FSendBuffer::operator=(FSendBuffer&& inSendBuffer)
{
	mBuffer = inSendBuffer.mBuffer;
	return *this;
}

FSendBuffer::~FSendBuffer()
{
	mBuffer.Empty();
}

BYTE* FSendBuffer::GetData()
{
	return mBuffer.GetData();
}

uint32 FSendBuffer::GetAllocatedSize()
{
	return mBuffer.GetAllocatedSize();
}
