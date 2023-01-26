// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkUtils.h"

DEFINE_LOG_CATEGORY(NETWORK_LOG);

void UNetworkUtils::NetworkScreenLog(const FString& inScreenLog)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("[NETWORK_LOG] : %s"), *inScreenLog));
}

void UNetworkUtils::NetworkConsoleLog(const FString& inConsoleLog, const ETestEnum& level)
{
	switch (level)
	{
	case ETestEnum::Fatal:
		UE_LOG(NETWORK_LOG, Fatal, TEXT("%s"), *inConsoleLog);
		break;
	case ETestEnum::Error:
		UE_LOG(NETWORK_LOG, Error, TEXT("%s"), *inConsoleLog);
		break;
	case ETestEnum::Warning:
		UE_LOG(NETWORK_LOG, Warning, TEXT("%s"), *inConsoleLog);
		break;
	case ETestEnum::Display:
		UE_LOG(NETWORK_LOG, Display, TEXT("%s"), *inConsoleLog);
		break;
	case ETestEnum::Log:
		UE_LOG(NETWORK_LOG, Log, TEXT("%s"), *inConsoleLog);
		break;
	case ETestEnum::Verbose:
		UE_LOG(NETWORK_LOG, Verbose, TEXT("%s"), *inConsoleLog);
		break;
	case ETestEnum::VeryVerbose:
		UE_LOG(NETWORK_LOG, VeryVerbose, TEXT("%s"), *inConsoleLog);
		break;
	default:
		break;
	}

}