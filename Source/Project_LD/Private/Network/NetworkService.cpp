// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/NetworkService.h"

UNetworkService::UNetworkService()
{

}

UNetworkService::~UNetworkService()
{
}

void UNetworkService::Initialize(FSubsystemCollectionBase& Collection)
{
}

void UNetworkService::Deinitialize()
{
}

void UNetworkService::Tick(float DeltaTime)
{
}

bool UNetworkService::IsAllowedToTick() const
{
	return false;
}

ETickableTickType UNetworkService::GetTickableTickType() const
{
	return ETickableTickType();
}

TStatId UNetworkService::GetStatId() const
{
	return TStatId();
}

bool UNetworkService::IsTickable() const
{
	return false;
}
