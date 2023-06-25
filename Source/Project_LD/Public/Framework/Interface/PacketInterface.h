// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PacketInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPacketInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_LD_API IPacketInterface
{
	GENERATED_BODY()

public:
	virtual void AppearPacket();
	virtual void DisAppearPacket();
	virtual void DestroyPacket();
};
