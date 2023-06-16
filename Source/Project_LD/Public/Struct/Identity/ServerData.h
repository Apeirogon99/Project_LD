// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ServerData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_LD_API UServerData : public UObject
{
	GENERATED_BODY()

public:
	int32 GetServerID() const
	{
		return mServerID;
	}
	FString GetServerName() const
	{
		return mServerName;
	}
	FString GetServerIP() const
	{
		return mServerIP;
	}
	int32 GetServerPort() const
	{
		return mServerPort;
	}

public:
	void SetServerID(const int32 inServerID)
	{
		mServerID = inServerID;
	}
	void SetServerName(const FString& inServerName)
	{
		mServerName = inServerName;
	}
	void SetServerIP(const FString& inServerIP)
	{
		mServerIP = inServerIP;
	}
	void SetServerPort(const int32 inServerPort)
	{
		mServerPort = inServerPort;
	}
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 mServerID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString mServerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString mServerIP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 mServerPort;
};
