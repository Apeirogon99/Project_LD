// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkTimeStamp.h"
#include <NetworkUtils.h>
#include <chrono>

UNetworkTimeStamp::UNetworkTimeStamp() : isInit(false), mServerTimeStamp(0), mOldUtcTimeStamp(0), mRtt(0), mSumRtt(0), mNumRtt(1)
{
}

UNetworkTimeStamp::~UNetworkTimeStamp()
{
}

void UNetworkTimeStamp::ResetTimeStamp()
{
	mServerTimeStamp = 0;
	mOldUtcTimeStamp = 0;
	mRtt = 0;
	mSumRtt = 0;
	mNumRtt = 1;
	isInit = false;
}

void UNetworkTimeStamp::InitTimeStamp(const int64 inServerTimeStamp, const int64 inUtcTimeStmap, const int64 inRtt)
{
	mOldUtcTimeStamp = inUtcTimeStmap;
	mServerTimeStamp = inServerTimeStamp;
	mRtt = inRtt;
	isInit = true;
}

void UNetworkTimeStamp::UpdateTimeStamp(const int64 inServerTimeStamp, const int64 inUtcTimeStmap, const int64 inRtt)
{

	if (isInit == false || mServerTimeStamp == 0)
	{
		return;
	}

	mOldUtcTimeStamp = inUtcTimeStmap;
	mServerTimeStamp = inServerTimeStamp;

	if (inRtt - mRtt > 10)
	{
		return;
	}

	mSumRtt += inRtt;

	double TargetWorldRtt = 0;

	mNumRtt += 1;
		
	if (mNumRtt > 250)
	{
		mSumRtt	/= mNumRtt;
		mNumRtt = 1;
	}

	TargetWorldRtt = mSumRtt / mNumRtt;

	if (mRtt == 0)
	{
		mRtt = TargetWorldRtt;
	}
	else
	{
		mRtt += (TargetWorldRtt - mRtt) * 0.5;
	}
	

}

const bool UNetworkTimeStamp::IsInit()
{
	return isInit;
}

const int64 UNetworkTimeStamp::GetUtcTimeStmap()
{
	FDateTime currentUtcTimeStamp = FDateTime::UtcNow();
	const int64 nowClientUtcTimeStamp = (currentUtcTimeStamp.ToUnixTimestamp() * 1000) + currentUtcTimeStamp.GetMillisecond();
	return nowClientUtcTimeStamp;
}

const int64 UNetworkTimeStamp::GetServerTimeStamp()
{
	return mServerTimeStamp + GetDurationUtcTimeStamp() + (mRtt / 2);
}

const int64 UNetworkTimeStamp::GetRTT()
{
	return mRtt;
}

const int64 UNetworkTimeStamp::GetDurationUtcTimeStamp()
{
	return GetUtcTimeStmap() - mOldUtcTimeStamp;
}