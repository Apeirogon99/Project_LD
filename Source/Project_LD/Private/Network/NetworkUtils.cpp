// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkUtils.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include <stringapiset.h>
#include "Windows/HideWindowsPlatformTypes.h"

#include <DatabaseErrorTypes.h>
#include "CommonErrorTypes.h"

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
	const wchar_t* tempWStr = *str;
	int tempWLen = wcslen(tempWStr) + 1;

	int32 tempLen = WideCharToMultiByte(949, 0, tempWStr, tempWLen, NULL, 0, NULL, NULL);
	char* tempStr = new char[tempLen];

	WideCharToMultiByte(949, 0, tempWStr, tempWLen, tempStr, tempLen, NULL, NULL);

	std::string outStr(tempStr);
	delete[] tempStr;
	tempStr = nullptr;
	return outStr;
}

int32 UNetworkUtils::ConvertStringToInt(const FString& str)
{
	return FCString::Atoi(*str);
}

FString UNetworkUtils::ConvertFString(const std::string& inStr)
{
	const char* tempStr = inStr.c_str();
	const int32 tempLen = strlen(tempStr) + 1;

	const int32 tempWLen = MultiByteToWideChar(949, 0, tempStr, tempLen, NULL, 0);
	wchar_t* tempWStr = new wchar_t[tempWLen];

	MultiByteToWideChar(949, 0, tempStr, tempLen, tempWStr, tempWLen);

	FString outStr = tempWStr;
	delete[] tempWStr;
	tempWStr = nullptr;
	return outStr;
}

FString UNetworkUtils::ConvertFString(const int32 value)
{
	std::string str = std::to_string(value);
	return *FString(str.c_str());
}

FText UNetworkUtils::ConvertFText(const FString& str)
{
	return FText::FromString(str);
}

FLinearColor UNetworkUtils::ConverLinearColor(const uint32 inValue)
{
	uint8 Red	= (inValue >> 24);
	uint8 Green = (inValue >> 16);
	uint8 Blue	= (inValue >> 8);
	//uint8 Alpha = (inValue);
	uint8 Alpha = 255;

	FColor fColor(Red, Green, Blue, Alpha);

	FLinearColor linearColor(fColor);
	return linearColor;
}

uint32 UNetworkUtils::ConverLinerColorToInt(FLinearColor inValue)
{
	FColor color = inValue.ToFColor(true);
	uint32 packed = color.ToPackedRGBA();
	return packed;
}

FString UNetworkUtils::GetNetworkErrorToString(const int32 inError)
{
	const std::string errorStr = GetNetworkError(inError);

	const char* tempStr = errorStr.c_str();
	const int32 tempLen = strlen(tempStr) + 1;

	const int32 tempWLen = MultiByteToWideChar(CP_UTF8, 0, tempStr, tempLen, NULL, 0);
	wchar_t* tempWStr = new wchar_t[tempWLen];

	MultiByteToWideChar(CP_UTF8, 0, tempStr, tempLen, tempWStr, tempWLen);

	FString outStr = tempWStr;
	delete[] tempWStr;
	tempWStr = nullptr;
	return outStr;
}
