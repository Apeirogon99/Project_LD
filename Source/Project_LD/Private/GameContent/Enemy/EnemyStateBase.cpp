// Fill out your copyright notice in the Description page of Project Settings.


#include "GameContent/Enemy/EnemyStateBase.h"
#include "GameContent/Enemy/EnemyState.h"

/*
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
	SetChangeState(EnemyState, UEnemyHitState::GetInstance(), EEnemyStateType::Hit);
}

void UEnemyIdleState::Attack(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyAttackState::GetInstance(), EEnemyStateType::Attack);
}

void UEnemyIdleState::Chase(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyChaseState::GetInstance(), EEnemyStateType::Chase);
}

void UEnemyIdleState::Kill(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyDeathState::GetInstance(), EEnemyStateType::Death);
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
	SetChangeState(EnemyState, UEnemyIdleState::GetInstance(), EEnemyStateType::Idle);
}

void UEnemyChaseState::Hit(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyHitState::GetInstance(), EEnemyStateType::Hit);
}

void UEnemyChaseState::Attack(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyAttackState::GetInstance(), EEnemyStateType::Attack);
}

void UEnemyChaseState::Chase(AEnemyState* EnemyState)
{
}

void UEnemyChaseState::Kill(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyDeathState::GetInstance(), EEnemyStateType::Death);
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
	SetChangeState(EnemyState, UEnemyIdleState::GetInstance(), EEnemyStateType::Idle);
}

void UEnemyAttackState::Hit(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyHitState::GetInstance(), EEnemyStateType::Hit);
}

void UEnemyAttackState::Attack(AEnemyState* EnemyState)
{
}

void UEnemyAttackState::Chase(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyChaseState::GetInstance(), EEnemyStateType::Chase);
}

void UEnemyAttackState::Kill(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyDeathState::GetInstance(), EEnemyStateType::Death);
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
	SetChangeState(EnemyState, UEnemyIdleState::GetInstance(), EEnemyStateType::Idle);
}

void UEnemyHitState::Hit(AEnemyState* EnemyState)
{
}

void UEnemyHitState::Attack(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyAttackState::GetInstance(), EEnemyStateType::Attack);
}

void UEnemyHitState::Chase(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyHitState::GetInstance(), EEnemyStateType::Chase);
}

void UEnemyHitState::Kill(AEnemyState* EnemyState)
{
	SetChangeState(EnemyState, UEnemyDeathState::GetInstance(), EEnemyStateType::Death);
}

void UEnemyBaseState::SetChangeState(AEnemyState* EnemyState, UEnemyBaseState* EnemyStateBase, EEnemyStateType Type)
{
	EnemyState->SetState(EnemyStateBase, Type);
}
*/

AEnemyStateBase::AEnemyStateBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

EEnemyStateType UEnemyIdleState::Idle()
{
	return EEnemyStateType::None;
}

EEnemyStateType UEnemyIdleState::Hit()
{
	return  EEnemyStateType::Hit;
}

EEnemyStateType UEnemyIdleState::Attack()
{
	return EEnemyStateType::Attack;
}

EEnemyStateType UEnemyIdleState::Chase()
{
	return EEnemyStateType::Chase;
}

EEnemyStateType UEnemyIdleState::Kill()
{
	return EEnemyStateType::Death;
}

EEnemyStateType UEnemyChaseState::Idle()
{
	return EEnemyStateType::Idle;
}

EEnemyStateType UEnemyChaseState::Hit()
{
	return EEnemyStateType::Hit;
}

EEnemyStateType UEnemyChaseState::Attack()
{
	return EEnemyStateType::Attack;
}

EEnemyStateType UEnemyChaseState::Chase()
{
	return EEnemyStateType::None;
}

EEnemyStateType UEnemyChaseState::Kill()
{
	return EEnemyStateType::Death;
}

EEnemyStateType UEnemyDeathState::Idle()
{
	return EEnemyStateType::None;
}

EEnemyStateType UEnemyDeathState::Hit()
{
	return EEnemyStateType::None;
}

EEnemyStateType UEnemyDeathState::Attack()
{
	return EEnemyStateType::None;
}

EEnemyStateType UEnemyDeathState::Chase()
{
	return EEnemyStateType::None;
}

EEnemyStateType UEnemyDeathState::Kill()
{
	return EEnemyStateType::None;
}

EEnemyStateType UEnemyAttackState::Idle()
{
	return EEnemyStateType::Idle;
}

EEnemyStateType UEnemyAttackState::Hit()
{
	return EEnemyStateType::Hit;
}

EEnemyStateType UEnemyAttackState::Attack()
{
	return EEnemyStateType::None;
}

EEnemyStateType UEnemyAttackState::Chase()
{
	return EEnemyStateType::Chase;
}

EEnemyStateType UEnemyAttackState::Kill()
{
	return EEnemyStateType::Death;
}

EEnemyStateType UEnemyHitState::Idle()
{
	return EEnemyStateType::Idle;
}

EEnemyStateType UEnemyHitState::Hit()
{
	return EEnemyStateType::None;
}

EEnemyStateType UEnemyHitState::Attack()
{
	return EEnemyStateType::Attack;
}

EEnemyStateType UEnemyHitState::Chase()
{
	return EEnemyStateType::Chase;
}

EEnemyStateType UEnemyHitState::Kill()
{
	return EEnemyStateType::Death;
}

AEnemyStateMachine::AEnemyStateMachine()
{
	mType = EEnemyStateType::Idle;

	mIdleState = NewObject<UEnemyIdleState>();
	mChaseState = NewObject<UEnemyChaseState>();
	mDeathState = NewObject<UEnemyDeathState>();
	mAttackState = NewObject<UEnemyAttackState>();
	mHitState = NewObject<UEnemyHitState>();

	mState = mIdleState;
}

AEnemyStateMachine::~AEnemyStateMachine()
{
}

void AEnemyStateMachine::Idle()
{
	mType = mState->Idle();
	TypeSwitch();
}

void AEnemyStateMachine::Hit()
{
	mType = mState->Hit();
	TypeSwitch();
}

void AEnemyStateMachine::Attack()
{
	mType = mState->Attack();
	TypeSwitch();
}

void AEnemyStateMachine::Chase()
{
	mType = mState->Chase();
	TypeSwitch();
}

void AEnemyStateMachine::Kill()
{
	mType = mState->Kill();
	TypeSwitch();
}

void AEnemyStateMachine::TypeSwitch()
{
	switch (mType)
	{
		case EEnemyStateType::None:
			break;
		case EEnemyStateType::Idle:
			mState = mIdleState;
			break;
		case EEnemyStateType::Chase:
			mState = mChaseState;
			break;
		case EEnemyStateType::Death:
			mState = mDeathState;
			break;
		case EEnemyStateType::Attack:
			mState = mAttackState;
			break;
		case EEnemyStateType::Hit:
			mState = mHitState;
			break;
	}
}
