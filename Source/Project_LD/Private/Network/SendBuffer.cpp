// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/SendBuffer.h"


FSendBuffer::FSendBuffer()
{
	mBuffer.Init(NULL, 0);
}

FSendBuffer::FSendBuffer(const uint32 size)
{
	mBuffer.Init(NULL, size);
}

FSendBuffer::~FSendBuffer()
{
}

BYTE* FSendBuffer::GetData()
{
	return mBuffer.GetData();
}

uint32 FSendBuffer::GetAllocatedSize()
{
	return mBuffer.GetAllocatedSize();
}
