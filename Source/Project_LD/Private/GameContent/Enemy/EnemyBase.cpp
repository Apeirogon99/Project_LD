// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Enemy/EnemyBase.h"
#include "GameContent/Enemy/EnemyAnimInstance.h"
#include "GameContent/Enemy/EnemyController.h"
#include "GameContent/Enemy/EnemyState.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	AIControllerClass = AEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyCollision"));
}

AEnemyBase::~AEnemyBase()
{
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AEnemyBase::Destroyed()
{
	Super::Destroyed();

}

void AEnemyBase::ChangeState(const EEnemyStateType inStateType, float inStartTime)
{

	UEnemyAnimInstance* enemyAnimationInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == enemyAnimationInstance)
	{
		return;
	}

	switch (inStateType)
	{
	case EEnemyStateType::State_Unspecified:
		break;
	case EEnemyStateType::State_Idle:
		enemyAnimationInstance->OnIdle(inStartTime);
		break;
	case EEnemyStateType::State_Round:
		enemyAnimationInstance->OnRound(inStartTime);
		break;
	case EEnemyStateType::State_Recovery:
		enemyAnimationInstance->OnRecovery(inStartTime);
		break;
	case EEnemyStateType::State_Chase:
		enemyAnimationInstance->OnChase(inStartTime);
		break;
	case EEnemyStateType::State_Attack:
		enemyAnimationInstance->OnAttack(inStartTime);
		break;
	case EEnemyStateType::State_Hit:
		enemyAnimationInstance->OnHit(inStartTime);
		break;
	case EEnemyStateType::State_Stun:
		enemyAnimationInstance->OnStun(inStartTime);
		break;
	case EEnemyStateType::State_Death:
		enemyAnimationInstance->OnDeath(inStartTime);
		break;
	default:
		break;
	}
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::Interactive(AC_Game* inPlayer)
{
	AEnemyState* state = GetPlayerState<AEnemyState>();
	if (state == nullptr)
	{
		return;
	}

	float damage = 10.f;

	FEnemyStatData stateData = state->GetEnemyCurrentStats();
	stateData.base_health -= damage;
	state->SetEnemyCurrentStats(stateData);

}