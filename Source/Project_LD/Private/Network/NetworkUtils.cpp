// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkUtils.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include <stringapiset.h>
#include "Windows/HideWindowsPlatformTypes.h"

#include <DatabaseErrorTypes.h>

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
	char def = '?';

	int32 len = WideCharToMultiByte(CP_ACP, 0, tempWStr, -1, NULL, 0, NULL, NULL);
	char* tempStr = new char[len];
	::memset(tempStr, '\0', len);

	WideCharToMultiByte(CP_ACP, 0, tempWStr, -1, tempStr, len, &def, NULL);
	tempStr[len] = '\0';

	std::string outStr(tempStr);
	delete[] tempStr;
	return outStr;
}

FString UNetworkUtils::ConvertFString(const std::string& str)
{
	const char* tempStr = str.c_str();

	int32 len = MultiByteToWideChar(CP_ACP, 0, tempStr, strlen(tempStr), NULL, NULL);
	wchar_t* tempWStr = new wchar_t[len];
	::wmemset(tempWStr, '\0', len);

	MultiByteToWideChar(CP_ACP, 0, tempStr, strlen(tempStr), tempWStr, len);
	tempWStr[len] = '\0';

	FString outStr = tempWStr;
	delete[] tempWStr;
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
	uint8 Alpha = (inValue);
	//uint8 Alpha = 255;

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

FString UNetworkUtils::GetNetworkErrorToString(int32 inError)
{
	std::string errorStr = GetDatabaseError(inError);
	return ConvertFString(errorStr);
}
