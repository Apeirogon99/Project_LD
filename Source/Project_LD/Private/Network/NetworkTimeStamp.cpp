// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkTimeStamp.h"

UNetworkTimeStamp::UNetworkTimeStamp() : mTimeStamp(0)
{
}

UNetworkTimeStamp::~UNetworkTimeStamp()
{
}

int64 UNetworkTimeStamp::GetClientTimeStamp()
{
	std::chrono::steady_clock::time_point endTimeStamp = std::chrono::steady_clock::now();
	long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeStamp - mClock).count();
	return static_cast<int64>(mTimeStamp + duration);
}

void UNetworkTimeStamp::SetClientTimeStamp(const int64 inTimeStamp)
{
	mTimeStamp = inTimeStamp;
	mClock = std::chrono::steady_clock::now();
}
