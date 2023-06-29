// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Struct/Game/EnemyStateTypeData.h"
#include "GameFramework/Actor.h"
#include "EnemyStateBase.generated.h"

/*
class AEnemyState;

UCLASS()
class PROJECT_LD_API UEnemyBaseState : public UObject
{
	GENERATED_BODY()

public:
	virtual void Nothing(AEnemyState* EnemyState) {}
	virtual void Hit(AEnemyState* EnemyState) {}
	virtual void Attack(AEnemyState* EnemyState) {}
	virtual void Chase(AEnemyState* EnemyState) {}
	virtual void Kill(AEnemyState* EnemyState) {}
	
protected:
	void SetChangeState(AEnemyState* EnemyState, UEnemyBaseState* EnemyStateBase, EEnemyStateType Type);
};

UCLASS()
class PROJECT_LD_API UEnemyIdleState : public UEnemyBaseState
{
	GENERATED_BODY()

public:
	static UEnemyIdleState* GetInstance();

	virtual void Nothing(AEnemyState* EnemyState);
	virtual void Hit(AEnemyState* EnemyState);
	virtual void Attack(AEnemyState* EnemyState);
	virtual void Chase(AEnemyState* EnemyState);
	virtual void Kill(AEnemyState* EnemyState);

private:
	static UEnemyIdleState* instance;
};

UCLASS()
class PROJECT_LD_API UEnemyChaseState : public UEnemyBaseState
{
	GENERATED_BODY()

public:
	static UEnemyChaseState* GetInstance();

	virtual void Nothing(AEnemyState* EnemyState);
	virtual void Hit(AEnemyState* EnemyState);
	virtual void Attack(AEnemyState* EnemyState);
	virtual void Chase(AEnemyState* EnemyState);
	virtual void Kill(AEnemyState* EnemyState);

private:
	static UEnemyChaseState* instance;
};

UCLASS()
class PROJECT_LD_API UEnemyDeathState : public UEnemyBaseState
{
	GENERATED_BODY()

public:
	static UEnemyDeathState* GetInstance();

	virtual void Nothing(AEnemyState* EnemyState);
	virtual void Hit(AEnemyState* EnemyState);
	virtual void Attack(AEnemyState* EnemyState);
	virtual void Chase(AEnemyState* EnemyState);
	virtual void Kill(AEnemyState* EnemyState);

private:
	static UEnemyDeathState* instance;
};

UCLASS()
class PROJECT_LD_API UEnemyAttackState : public UEnemyBaseState
{
	GENERATED_BODY()

public:
	static UEnemyAttackState* GetInstance();

	virtual void Nothing(AEnemyState* EnemyState);
	virtual void Hit(AEnemyState* EnemyState);
	virtual void Attack(AEnemyState* EnemyState);
	virtual void Chase(AEnemyState* EnemyState);
	virtual void Kill(AEnemyState* EnemyState);

private:
	static UEnemyAttackState* instance;
};

UCLASS()
class PROJECT_LD_API UEnemyHitState : public UEnemyBaseState
{
	GENERATED_BODY()

public:
	static UEnemyHitState* GetInstance();

	virtual void Nothing(AEnemyState* EnemyState);
	virtual void Hit(AEnemyState* EnemyState);
	virtual void Attack(AEnemyState* EnemyState);
	virtual void Chase(AEnemyState* EnemyState);
	virtual void Kill(AEnemyState* EnemyState);

private:
	static UEnemyHitState* instance;
};

UCLASS()
class PROJECT_LD_API AEnemyStateBase : public AActor
{
	GENERATED_BODY()

public:
	AEnemyStateBase();
};
*/

UCLASS()
class PROJECT_LD_API UEnemyBaseState : public UObject
{
	GENERATED_BODY()

public:
	virtual EEnemyStateType Idle() { return EEnemyStateType::None; }
	virtual EEnemyStateType Hit() { return EEnemyStateType::None; }
	virtual EEnemyStateType Attack() { return EEnemyStateType::None; }
	virtual EEnemyStateType Chase() { return EEnemyStateType::None; }
	virtual EEnemyStateType Kill() { return EEnemyStateType::None; }
};

UCLASS()
class PROJECT_LD_API UEnemyIdleState : public UEnemyBaseState
{
	GENERATED_BODY()

public:
	virtual EEnemyStateType Idle();
	virtual EEnemyStateType Hit();
	virtual EEnemyStateType Attack();
	virtual EEnemyStateType Chase();
	virtual EEnemyStateType Kill();
};

UCLASS()
class PROJECT_LD_API UEnemyChaseState : public UEnemyBaseState
{
	GENERATED_BODY()

public:
	virtual EEnemyStateType Idle();
	virtual EEnemyStateType Hit();
	virtual EEnemyStateType Attack();
	virtual EEnemyStateType Chase();
	virtual EEnemyStateType Kill();
};

UCLASS()
class PROJECT_LD_API UEnemyDeathState : public UEnemyBaseState
{
	GENERATED_BODY()

public:
	virtual EEnemyStateType Idle();
	virtual EEnemyStateType Hit();
	virtual EEnemyStateType Attack();
	virtual EEnemyStateType Chase();
	virtual EEnemyStateType Kill();
};

UCLASS()
class PROJECT_LD_API UEnemyAttackState : public UEnemyBaseState
{
	GENERATED_BODY()

public:
	virtual EEnemyStateType Idle();
	virtual EEnemyStateType Hit();
	virtual EEnemyStateType Attack();
	virtual EEnemyStateType Chase();
	virtual EEnemyStateType Kill();
};

UCLASS()
class PROJECT_LD_API UEnemyHitState : public UEnemyBaseState
{ 
	GENERATED_BODY()

public:
	virtual EEnemyStateType Idle();
	virtual EEnemyStateType Hit();
	virtual EEnemyStateType Attack();
	virtual EEnemyStateType Chase();
	virtual EEnemyStateType Kill();
};

UCLASS()
class PROJECT_LD_API AEnemyStateMachine : public AActor
{
	GENERATED_BODY()

public:
	AEnemyStateMachine();
	~AEnemyStateMachine();

public:
	void Idle();
	void Hit();
	void Attack();
	void Chase();
	void Kill();

public:
	void SetType(EEnemyStateType type) { mType = type; }

public:
	EEnemyStateType		GetType() const			{ return mType; }
	UEnemyBaseState*		GetState() const			{ return mState; }

private:
	EEnemyStateType		mType;
	UEnemyBaseState*		mState;

	UEnemyIdleState*			mIdleState;
	UEnemyChaseState*		mChaseState;
	UEnemyDeathState*		mDeathState;
	UEnemyAttackState*		mAttackState;
	UEnemyHitState*			mHitState;

private:
	void TypeSwitch();
};

UCLASS()
class PROJECT_LD_API AEnemyStateBase : public AActor
{
	GENERATED_BODY()

public:
	AEnemyStateBase();
};