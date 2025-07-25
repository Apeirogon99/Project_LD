// Fill out your copyright notice in the Description page of Project Settings.

#include "GameContent/Enemy/EnemyBase.h"
#include "GameContent/Enemy/EnemyAnimInstance.h"
#include "GameContent/Enemy/EnemyController.h"
#include "GameContent/Enemy/EnemyState.h"

#include <Game/GM_Game.h>
#include <Framework/Game/GS_Game.h>
#include <Framework/AnimInstance/AI_PlayerCharacter.h>
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>

#include "Widget/Game/Enemy/W_HealthBar.h"

#include <UObject/ConstructorHelpers.h>

#include "Particles/ParticleSystemComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Component/ACPointOfInterest.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include <Kismet/GameplayStatics.h>
#include <NetworkUtils.h>

// Sets default values
AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	AIControllerClass = AEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Tags.Add(FName("Enemy"));
	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyCollision"));

	TSubclassOf<UW_HealthBar> HealthBarWidgetClass = StaticLoadClass(UW_HealthBar::StaticClass(), NULL, TEXT("WidgetBlueprint'/Game/Blueprint/Widget/Game/Enemy/BW_HealthBar.BW_HealthBar_C'"));
	if (HealthBarWidgetClass)
	{
		mHealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
		mHealthBar->SetupAttachment(RootComponent);
		mHealthBar->SetWidgetClass(HealthBarWidgetClass);
		mHealthBar->SetCollisionProfileName(TEXT("NoCollision"));
		mHealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	}

	mParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	mSlowParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("mSlowParticleSystem"));
	mParticleSystem->SetupAttachment(RootComponent);
	mSlowParticleSystem->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> SLOWPARTICLE(TEXT("ParticleSystem'/Game/Test/P_Slow.P_Slow'"));
	if (SLOWPARTICLE.Succeeded())
	{
		mSlowParticle = SLOWPARTICLE.Object;
	}

	mPOI = CreateDefaultSubobject<UACPointOfInterest>(TEXT("POI"));

	bSpeedCheck = false;
}

AEnemyBase::~AEnemyBase()
{
}

void AEnemyBase::OnEnemyHit_Implementation()
{
	if (mHitMaterialInstance)
	{
		mHitMaterialInstance->SetVectorParameterValue(FName("EmissiveColor"), FLinearColor::Red);
		mHitMaterialInstance->SetScalarParameterValue(FName("EmissiveMul"), 100.0f);
	}
	else
	{
		//UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("Can't find hit material instance")), ELogLevel::Error);
	}

}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
	if (nullptr == gameState)
	{
		return;
	}

	AEnemyController* controller = Cast<AEnemyController>(GetController());
	if (nullptr == controller)
	{
		return;
	}

	AEnemyState* playerState = controller->GetPlayerState<AEnemyState>();
	if (nullptr == playerState)
	{
		return;
	}

	if (playerState->OnMovementSpeedChanged.IsBound())
	{
		playerState->OnMovementSpeedChanged.Clear();
	}

	mHealthBar->SetVisibility(false);
}

void AEnemyBase::Destroyed()
{
	Super::Destroyed();

	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
	if (nullptr == gameState)
	{
		return;
	}

	AEnemyController* controller = Cast<AEnemyController>(GetController());
	if (nullptr == controller)
	{
		return;
	}

	AEnemyState* playerState = controller->GetPlayerState<AEnemyState>();
	if (nullptr == playerState)
	{
		return;
	}

	if (playerState->OnMovementSpeedChanged.IsBound())
	{
		playerState->OnMovementSpeedChanged.Clear();
	}

	mHealthBar->SetVisibility(false);
}

void AEnemyBase::SetParticleTemplate(UParticleSystem* InParticleTemplate)
{
	mParticleSystem->SetTemplate(InParticleTemplate);
}

void AEnemyBase::SetParticleLocationAndRotation(const FVector InNewLocation, const FRotator InNewRotation)
{
	mParticleSystem->SetRelativeLocationAndRotation(InNewLocation, InNewRotation);
}

void AEnemyBase::SetParticleScale(FVector InNewScale)
{
	mParticleSystem->SetRelativeScale3D(InNewScale);
}

void AEnemyBase::Init()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	AGS_Game* gameState = Cast<AGS_Game>(world->GetGameState());
	if (nullptr == gameState)
	{
		return;
	}

	AEnemyController* controller = Cast<AEnemyController>(GetController());
	if (nullptr == controller)
	{
		return;
	}

	AEnemyState* playerState = controller->GetPlayerState<AEnemyState>();
	if (nullptr == playerState)
	{
		return;
	}

	playerState->OnHealthChanged.AddUFunction(this, FName(TEXT("UpdateHealthBar")));
	playerState->OnMovementSpeedChanged.AddUFunction(this, FName(TEXT("UpdateMovementSpeed")));
}

void AEnemyBase::HealthBarActive()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	TArray<AActor*> localplayer;
	UGameplayStatics::GetAllActorsOfClass(world, AC_Game::StaticClass(), localplayer);
	if (localplayer.Num() == 0)
	{
		return;
	}
	AC_Game* player = Cast<AC_Game>(localplayer[0]);
	if (nullptr == player)
	{
		return;
	}
	player->BossHealthBarWidgetActive(this);
}

void AEnemyBase::HealthBarDeactive()
{
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	TArray<AActor*> localplayer;
	UGameplayStatics::GetAllActorsOfClass(world, AC_Game::StaticClass(), localplayer);
	if (localplayer.Num() == 0)
	{
		return;
	}
	AC_Game* player = Cast<AC_Game>(localplayer[0]);
	if (nullptr == player)
	{
		return;
	}
	player->BossHealthBarWidgetDeactive();
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
	case EEnemyStateType::State_Search:
		enemyAnimationInstance->OnSearch(inStartTime);
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
		UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("INVALID Enemy State")), ELogLevel::Error);
		break;
	}
}

void AEnemyBase::UpdateHealthBar()
{
	AController* controller = GetController();
	if (nullptr == controller)
	{
		return;
	} 

	AEnemyState* playerState = controller->GetPlayerState<AEnemyState>();
	if (nullptr == playerState)
	{
		return;
	}

	UW_HealthBar* healthbar = Cast<UW_HealthBar>(mHealthBar->GetUserWidgetObject());
	if(nullptr == healthbar)
	{
		return;
	}
	float MaxHealth = playerState->GetEnemyStats().GetHealth();
	float CurrentHealth = playerState->GetEnemyCurrentStats().GetHealth();

	float HealthPercent = CurrentHealth / MaxHealth;

	healthbar->HealthBar->SetPercent(HealthPercent);
}

void AEnemyBase::UpdateMovementSpeed()
{
	AController* controller = GetController();
	if (nullptr == controller)
	{
		return;
	}

	AEnemyState* playerState = controller->GetPlayerState<AEnemyState>();
	if (nullptr == playerState)
	{
		return;
	}
	
	float MaxSpeed = playerState->GetEnemyStats().GetMovementSpeed();
	float CurrentSpeed = playerState->GetEnemyCurrentStats().GetMovementSpeed();

	if (MaxSpeed > CurrentSpeed)
	{
		if (bSpeedCheck == false)
		{
			bSpeedCheck = true;
			mSlowParticleSystem->SetTemplate(mSlowParticle);
		}
	}
	else
	{
		if (bSpeedCheck == true)
		{
			bSpeedCheck = false;
			mSlowParticleSystem->SetTemplate(nullptr);
		}
	}
}

void AEnemyBase::Interactive(ANC_Game* inPlayer)
{
	if (inPlayer->GetUsingSkill())
	{
		return;
	}

	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	ANetworkGameMode* gameMode = Cast<ANetworkGameMode>(world->GetAuthGameMode());
	if (nullptr == gameMode)
	{
		return;
	}

	ANetworkController* controller = gameMode->GetNetworkController();
	if (nullptr == controller)
	{
		return;
	}

	if (false == gameMode->CompareNetworkController(inPlayer->GetController()))
	{
		return;
	}

	AEnemyState* state = GetPlayerState<AEnemyState>();
	if (state == nullptr)
	{
		return;
	}

	UAI_PlayerCharacter* animInstance = Cast<UAI_PlayerCharacter>(inPlayer->GetMesh()->GetAnimInstance());
	if (nullptr == animInstance)
	{
		return;
	}

	FVector direction = this->GetActorLocation() - inPlayer->GetActorLocation();
	inPlayer->SetActorRotation(FRotator(0.0f, direction.Rotation().Yaw, 0.0f));

	float distance = FVector::Dist2D(inPlayer->GetActorLocation(), this->GetActorLocation());
	float range = 175.0f;

	if (distance <= range)
	{
		animInstance->PlayClientAttackMontage();
		inPlayer->IsAttack = true;
	}
	Protocol::C2S_PlayerAutoAttack attackPacket;
	attackPacket.set_object_id(state->GetObjectID());
	attackPacket.set_timestamp(controller->GetServerTimeStamp());

	SendBufferPtr sendBuffer = FGamePacketHandler::MakeSendBuffer(controller, attackPacket);
	controller->Send(sendBuffer);
}