// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include "UObject/NoExportTypes.h"

DECLARE_LOG_CATEGORY_EXTERN(NETWORK_LOG, Log, All);

#include "NetworkUtils.generated.h"

class UNetworkUtils;

#define __FUNC__ __FUNCTION__
#define NetworkDetailLog (									\
TEXT(" [ FILE : ") + FString(__FILE__)		+ TEXT(" ] ") +	\
TEXT(" [ FUNC : ") + FString(__FUNC__)		+ TEXT(" ] ") +	\
TEXT(" [ LINE : ") + FString(__LINE__)		+ TEXT(" ] "))

UENUM(BlueprintType)
enum class ELogLevel : uint8
{
	Fatal UMETA(DisplayName = "Fatal"),
	Error UMETA(DisplayName = "Error"),
	Warning UMETA(DisplayName = "Warning"),
	Display UMETA(DisplayName = "Display"),
	Log UMETA(DisplayName = "Log"),
	Verbose UMETA(DisplayName = "Verbose"),
	VeryVerbose UMETA(DisplayName = "VeryVerbose"),
};

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_LD_API UNetworkUtils : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Utils")
	static void NetworkScreenLog(const FString& inDebugLog);

	UFUNCTION(BlueprintCallable, Category = "Utils")
		static void NetworkConsoleLog(const FString& inConsoleLog, const ELogLevel& level);

	static std::string ConvertString(const FString& str);
};
