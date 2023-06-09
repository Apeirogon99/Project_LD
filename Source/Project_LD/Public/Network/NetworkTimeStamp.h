// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <chrono>
#include "NetworkTimeStamp.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UNetworkTimeStamp : public UObject
{
	GENERATED_BODY()

public:
	UNetworkTimeStamp();
	virtual ~UNetworkTimeStamp();

public:
	void		UpdateTimeStamp(const int64 inServerTimeStamp, const int64 inServerUtcTime);

public:
	const int64	GetServerTimeStamp();
	const int64 GetTimeStampDelta();
	const int64 GetUtcTimeStampDelta();
	const int64 GetUtcTime();

protected:
	const int64 GetUtcDurationTimeStamp();

public:
	std::chrono::steady_clock::time_point mClock;
	int64 mTimeStamp;
	int64 mTimeStampDelta;
	int64 mSumTimeStampDelta;
	int64 mNumTimeStampDelta;

	int64 mUtcTimeStamp;
	int64 mUtcTimeStampDelta;
};
