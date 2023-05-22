// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkTimeStamp.h"
#include <chrono>

UNetworkTimeStamp::UNetworkTimeStamp() : mTimeStamp(0), mTimeStampDelta(0), mSumTimeStampDelta(0), mNumTimeStampDelta(1), mUtcTimeStamp(0), mUtcTimeStampDelta(0)
{
}

UNetworkTimeStamp::~UNetworkTimeStamp()
{
}

const int64 UNetworkTimeStamp::GetDurationTimeStamp()
{
	return int64();
}

const int64 UNetworkTimeStamp::GetUtcDurationTimeStamp()
{
	FDateTime currentUtcTimeStamp = FDateTime::UtcNow();
	const int64 newClientUtcTimeStamp = (currentUtcTimeStamp.ToUnixTimestamp() * 1000) + currentUtcTimeStamp.GetMillisecond();
	const int64 oldClientUtcTimeStmap = mUtcTimeStamp;
	const int64 tempUtcDurationTimeStmap = (newClientUtcTimeStamp - oldClientUtcTimeStmap) + mUtcTimeStampDelta;
	return tempUtcDurationTimeStmap;
}

void UNetworkTimeStamp::UpdateTimeStamp(const int64 inServerTimeStamp)
{
	if (mTimeStamp == 0)
	{
		mTimeStamp = inServerTimeStamp;
	}
	else
	{
		const int64 timeStampDelta = inServerTimeStamp - mTimeStamp;
		mTimeStamp = inServerTimeStamp;

		mSumTimeStampDelta += timeStampDelta;
		mNumTimeStampDelta += 1;

		if (mNumTimeStampDelta > 250)
		{
			mSumTimeStampDelta /= mNumTimeStampDelta;
			mNumTimeStampDelta = 1;
		}

		double TargetWorldTimeSecondsDelta = mSumTimeStampDelta / mNumTimeStampDelta;

		if (mTimeStampDelta == 0.0)
		{
			mTimeStampDelta = TargetWorldTimeSecondsDelta;
		}
		else
		{
			mTimeStampDelta += (TargetWorldTimeSecondsDelta - mTimeStampDelta) * 0.5;
		}
	}
}

void UNetworkTimeStamp::UpdateUtcDelta(const int64 inServerUtcTime)
{
	FDateTime currentUtcTimeStamp = FDateTime::UtcNow();
	mUtcTimeStamp = (currentUtcTimeStamp.ToUnixTimestamp() * 1000) + currentUtcTimeStamp.GetMillisecond();
	mUtcTimeStampDelta = mUtcTimeStamp - inServerUtcTime;

}

const int64 UNetworkTimeStamp::GetServerTimeStamp()
{
	return mTimeStamp + GetUtcDurationTimeStamp();
}

const int64 UNetworkTimeStamp::GetUtcTimeStampDelta()
{
	return mUtcTimeStampDelta;
}

const int64 UNetworkTimeStamp::GetTimeStampDelta()
{
	return mTimeStampDelta;
}

