// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Containers/Array.h>

/**
 * 
 */

class FSendBuffer;
using FSendBufferPtr = TSharedPtr<class FSendBuffer>;

class PROJECT_LD_API FSendBuffer
{

public:
	FSendBuffer();
	FSendBuffer(const uint32 size);
	~FSendBuffer();

	BYTE*	GetData();
	uint32	GetAllocatedSize();

private:
	TArray<BYTE> mBuffer;
};
