// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkTimeStamp.h"
#include <NetworkUtils.h>
#include <chrono>

UNetworkTimeStamp::UNetworkTimeStamp() : mServerTimeStamp(0), mTimeStamp(0), mTimeStampDelta(0), mSumTimeStampDelta(0), mNumTimeStampDelta(1), mUtcTimeStamp(0), mUtcTimeStampDelta(0), mRtt(0), mSumRtt(0)
{
}

UNetworkTimeStamp::~UNetworkTimeStamp()
{
}

void UNetworkTimeStamp::UpdateTimeStamp(const int64 inServerTimeStamp, const int64 inServerUtcTime, const int64 inRtt)
{
	FDateTime	currentUtcTimeStamp = FDateTime::UtcNow();
	const int64 nowClientUtcTimeStamp = (currentUtcTimeStamp.ToUnixTimestamp() * 1000) + currentUtcTimeStamp.GetMillisecond();
	mUtcTimeStampDelta = inServerUtcTime - nowClientUtcTimeStamp;

	if (mTimeStamp == 0)
	{
		mServerTimeStamp = inServerTimeStamp;
		mTimeStamp = inServerUtcTime;
		mRtt = inRtt;
	}
	else
	{
		const int64 timeStampDelta = inServerTimeStamp - GetClientTimeStamp();
		mTimeStamp = inServerUtcTime;
		mServerTimeStamp = inServerTimeStamp;

		mSumTimeStampDelta += timeStampDelta;
		mSumRtt += inRtt;

		mNumTimeStampDelta += 1;

		if (mNumTimeStampDelta > 250)
		{
			mSumTimeStampDelta /= mNumTimeStampDelta;
			mSumRtt /= mNumTimeStampDelta;
			mNumTimeStampDelta = 1;
		}

		double TargetWorldTimeSecondsDelta = mSumTimeStampDelta / mNumTimeStampDelta;
		double TargetWorldRtt = mSumRtt / mNumTimeStampDelta;

		if (mTimeStampDelta == 0)
		{
			mTimeStampDelta = TargetWorldTimeSecondsDelta;
			mRtt = mSumRtt;
		}
		else
		{
			mTimeStampDelta += (TargetWorldTimeSecondsDelta - mTimeStampDelta) * 0.5;
			mRtt += (TargetWorldRtt - mRtt) * 0.5;
		}
	}

}

const int64 UNetworkTimeStamp::GetServerTimeStamp()
{
	return GetDurationUtcTimeStamp();
	//return GetClientTimeStamp() + mTimeStampDelta - mRtt;
}

const int64 UNetworkTimeStamp::GetClientTimeStamp()
{
	return GetDurationUtcTimeStamp() - mRtt - mUtcTimeStampDelta;
}

const int64 UNetworkTimeStamp::GetDurationUtcTimeStamp()
{
	FDateTime	currentUtcTimeStamp			= FDateTime::UtcNow();
	const int64 nowClientUtcTimeStamp		= (currentUtcTimeStamp.ToUnixTimestamp() * 1000) + currentUtcTimeStamp.GetMillisecond();
	const int64 oldClientUtcTimeStmap		= mTimeStamp;

	const int64 tempUtcDurationTimeStmap	= (nowClientUtcTimeStamp - oldClientUtcTimeStmap);
	const int64 predictionTimeStamp			= mServerTimeStamp + tempUtcDurationTimeStmap;

	return		predictionTimeStamp;
}