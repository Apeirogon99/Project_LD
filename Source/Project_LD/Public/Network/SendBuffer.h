// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Containers/Array.h>

/**
 * 
 */

class FSendBuffer;

class PROJECT_LD_API FSendBuffer
{

public:
	FSendBuffer();
	FSendBuffer(const uint32 inDataSize);

	FSendBuffer(const FSendBuffer& inSendBuffer);
	FSendBuffer& operator=(const FSendBuffer& inSendBuffer);

	FSendBuffer(FSendBuffer&& inSendBuffer);
	FSendBuffer& operator=(FSendBuffer&& inSendBuffer);

	virtual ~FSendBuffer();

public:
	BYTE*	GetData();
	uint32	GetAllocatedSize();

private:
	TArray<BYTE> mBuffer;
};
