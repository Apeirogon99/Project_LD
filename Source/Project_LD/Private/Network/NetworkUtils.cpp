// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkUtils.h"

DEFINE_LOG_CATEGORY(NETWORK_LOG);

void UNetworkUtils::NetworkScreenLog(const FString& inScreenLog)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("[NETWORK_LOG] : %s"), *inScreenLog));
}

void UNetworkUtils::NetworkConsoleLog(const FString& inConsoleLog, const ELogLevel& level)
{
	switch (level)
	{
	case ELogLevel::Fatal:
		UE_LOG(NETWORK_LOG, Fatal, TEXT("%s"), *inConsoleLog);
		break;
	case ELogLevel::Error:
		UE_LOG(NETWORK_LOG, Error, TEXT("%s"), *inConsoleLog);
		break;
	case ELogLevel::Warning:
		UE_LOG(NETWORK_LOG, Warning, TEXT("%s"), *inConsoleLog);
		break;
	case ELogLevel::Display:
		UE_LOG(NETWORK_LOG, Display, TEXT("%s"), *inConsoleLog);
		break;
	case ELogLevel::Log:
		UE_LOG(NETWORK_LOG, Log, TEXT("%s"), *inConsoleLog);
		break;
	case ELogLevel::Verbose:
		UE_LOG(NETWORK_LOG, Verbose, TEXT("%s"), *inConsoleLog);
		break;
	case ELogLevel::VeryVerbose:
		UE_LOG(NETWORK_LOG, VeryVerbose, TEXT("%s"), *inConsoleLog);
		break;
	default:
		break;
	}

}

std::string UNetworkUtils::ConvertString(const FString& str)
{
	return TCHAR_TO_UTF8(*str);
}
