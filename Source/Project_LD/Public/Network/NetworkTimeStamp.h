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
	void		ResetTimeStamp();
	void		InitTimeStamp(const int64 inServerTimeStamp, const int64 inUtcTimeStmap, const int64 inRtt);
	void		UpdateTimeStamp(const int64 inServerTimeStamp, const int64 inUtcTimeStmap, const int64 inRtt);

public:
	const bool	IsInit();
	const int64 GetUtcTimeStmap();
	const int64	GetServerTimeStamp();
	const int64 GetRTT();

protected:
	const int64 GetDurationUtcTimeStamp();

public:
	bool isInit;

	std::chrono::steady_clock::time_point mClock;
	int64 mServerTimeStamp;
	int64 mOldUtcTimeStamp;

	int64 mRtt;
	int64 mSumRtt;
	int64 mNumRtt;
};
