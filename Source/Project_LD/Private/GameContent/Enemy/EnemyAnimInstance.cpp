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

void UEnemyAnimInstance::OnIdle_Implementation(float inStartTime)
{
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnIdle")), ELogLevel::Warning);
}

void UEnemyAnimInstance::OnRound_Implementation(float inStartTime)
{
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnRound")), ELogLevel::Warning);
}

void UEnemyAnimInstance::OnRecovery_Implementation(float inStartTime)
{
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnRecovery")), ELogLevel::Warning);
}

void UEnemyAnimInstance::OnChase_Implementation(float inStartTime)
{
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnChase")), ELogLevel::Warning);
}

void UEnemyAnimInstance::OnAttack_Implementation(float inStartTime)
{
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnAttack")), ELogLevel::Warning);
}

void UEnemyAnimInstance::OnHit_Implementation(float inStartTime)
{
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnHit")), ELogLevel::Warning);
}

void UEnemyAnimInstance::OnStun_Implementation(float inStartTime)
{
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnStun")), ELogLevel::Warning);
}

void UEnemyAnimInstance::OnDeath_Implementation(float inStartTime)
{
	UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("OnDeath")), ELogLevel::Warning);
}
