// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/EnemyStateBase.h"
#include "GameContent/Enemy/EnemyState.h"

UEnemyIdleState*			UEnemyIdleState::instance;
UEnemyChaseState*		UEnemyChaseState::instance;
UEnemyDeathState*		UEnemyDeathState::instance;
UEnemyAttackState*		UEnemyAttackState::instance;
UEnemyHitState*			UEnemyHitState::instance;

AEnemyStateBase::AEnemyStateBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

UEnemyIdleState* UEnemyIdleState::GetInstance()
{
	if (instance == nullptr)
	{
		instance = NewObject<UEnemyIdleState>();
	}

	return instance;
}

void UEnemyIdleState::Nothing(AEnemyState* EnemyState)
{
}

void UEnemyIdleState::Hit(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyHitState::GetInstance());
}

void UEnemyIdleState::Attack(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyAttackState::GetInstance());
}

void UEnemyIdleState::Chase(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyChaseState::GetInstance());
}

void UEnemyIdleState::Kill(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyDeathState::GetInstance());
}

UEnemyChaseState* UEnemyChaseState::GetInstance()
{
	if (instance == nullptr)
	{
		instance = NewObject<UEnemyChaseState>();
	}

	return instance;
}

void UEnemyChaseState::Nothing(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyIdleState::GetInstance());
}

void UEnemyChaseState::Hit(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyHitState::GetInstance());
}

void UEnemyChaseState::Attack(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyAttackState::GetInstance());
}

void UEnemyChaseState::Chase(AEnemyState* EnemyState)
{
}

void UEnemyChaseState::Kill(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyDeathState::GetInstance());
}

UEnemyDeathState* UEnemyDeathState::GetInstance()
{
	if (instance == nullptr)
	{
		instance = NewObject<UEnemyDeathState>();
	}

	return instance;
}

void UEnemyDeathState::Nothing(AEnemyState* EnemyState)
{
}

void UEnemyDeathState::Hit(AEnemyState* EnemyState)
{
}

void UEnemyDeathState::Attack(AEnemyState* EnemyState)
{
}

void UEnemyDeathState::Chase(AEnemyState* EnemyState)
{
}

void UEnemyDeathState::Kill(AEnemyState* EnemyState)
{
}

UEnemyAttackState* UEnemyAttackState::GetInstance()
{
	if (instance == nullptr)
	{
		instance = NewObject<UEnemyAttackState>();
	}

	return instance;
}

void UEnemyAttackState::Nothing(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyIdleState::GetInstance());
}

void UEnemyAttackState::Hit(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyHitState::GetInstance());
}

void UEnemyAttackState::Attack(AEnemyState* EnemyState)
{
}

void UEnemyAttackState::Chase(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyChaseState::GetInstance());
}

void UEnemyAttackState::Kill(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyDeathState::GetInstance());
}

UEnemyHitState* UEnemyHitState::GetInstance()
{
	if (instance == nullptr)
	{
		instance = NewObject<UEnemyHitState>();
	}

	return instance;
}

void UEnemyHitState::Nothing(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyIdleState::GetInstance());
}

void UEnemyHitState::Hit(AEnemyState* EnemyState)
{
}

void UEnemyHitState::Attack(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyAttackState::GetInstance());
}

void UEnemyHitState::Chase(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyHitState::GetInstance());
}

void UEnemyHitState::Kill(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyDeathState::GetInstance());
}

void UEnemyBaseState::SetChangeState(AEnemyState* EnemyState, UEnemyBaseState* EnemyStateBase)
{
	EnemyState->SetState(EnemyStateBase);
}
