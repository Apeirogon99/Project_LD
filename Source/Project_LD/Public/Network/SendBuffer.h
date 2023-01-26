// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Containers/Array.h>

/**
 * 
 */
class PROJECT_LD_API USendBuffer
{

public:
	USendBuffer();
	USendBuffer(const BYTE* buffer, const uint32 size);
	~USendBuffer();

	BYTE*	GetData();
	uint32	GetAllocatedSize();

private:
	TArray<BYTE> mBuffer;
};

using SendBufferPtr = TSharedPtr<class USendBuffer>;
