// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/EnemyAnimInstance.h"
#include "GameContent/Enemy/EnemyBase.h"
#include "GameContent/Enemy/EnemyState.h"

#include "Kismet/KismetMathLibrary.h"
#include <Network/NetworkUtils.h>

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

float UEnemyAnimInstance::OnSpawn_Implementation(float inStartTime)
{
	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnSpawn")), ELogLevel::Warning);
	return inStartTime;
}

float UEnemyAnimInstance::OnIdle_Implementation(float inStartTime)
{
	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnIdle")), ELogLevel::Warning);
	return inStartTime;
}

float UEnemyAnimInstance::OnRound_Implementation(float inStartTime)
{
	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnRound")), ELogLevel::Warning);
	return inStartTime;
}

float UEnemyAnimInstance::OnRecovery_Implementation(float inStartTime)
{
	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnRecovery")), ELogLevel::Warning);
	return inStartTime;
}

float UEnemyAnimInstance::OnChase_Implementation(float inStartTime)
{
	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnChase")), ELogLevel::Warning);
	return inStartTime;
}

float UEnemyAnimInstance::OnAttack_Implementation(float inStartTime)
{
	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnAttack")), ELogLevel::Warning);
	return inStartTime;
}

float UEnemyAnimInstance::OnAttackCritical_Implementation(float inStartTime)
{
	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnAttackCritical")), ELogLevel::Warning);
	return inStartTime;
}

float UEnemyAnimInstance::OnHit_Implementation(float inStartTime)
{
	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnHit")), ELogLevel::Warning);
	return inStartTime;
}

float UEnemyAnimInstance::OnStun_Implementation(float inStartTime)
{
	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnStun")), ELogLevel::Warning);
	return inStartTime;
}

float UEnemyAnimInstance::OnDeath_Implementation(float inStartTime)
{
	//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnDeath")), ELogLevel::Warning);
	return inStartTime;
}