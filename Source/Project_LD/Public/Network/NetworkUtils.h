// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

DECLARE_LOG_CATEGORY_EXTERN(NETWORK_LOG, Log, All);

#include "NetworkUtils.generated.h"

UENUM(BlueprintType)
enum class ETestEnum : uint8
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
		static void NetworkConsoleLog(const FString& inConsoleLog, const ETestEnum& level);
};
