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
	int64	GetClientTimeStamp();
	void	SetClientTimeStamp(const int64 inTimeStamp);

private:
	std::chrono::steady_clock::time_point mClock;
	int64 mTimeStamp;
};
