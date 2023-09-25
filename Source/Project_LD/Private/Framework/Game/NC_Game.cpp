// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Game/NC_Game.h"
#include "Framework/Game/NPC_Game.h"
#include "Framework/Game/GS_Game.h"
#include "Framework/Game/PS_Game.h"

#include <Widget/Game/Chat/W_WorldChat.h>

#include "Components/CapsuleComponent.h"
#include <Components/WidgetComponent.h>
#include "GameFramework/CharacterMovementComponent.h"

#include "Niagara/Public/NiagaraComponent.h"
#include "Niagara/Classes/NiagaraSystem.h"
#include "Particles/ParticleSystemComponent.h"

#include <UObject/ConstructorHelpers.h>

ANC_Game::ANC_Game()
{
	//PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));

	AIControllerClass = ANPC_Game::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	TSubclassOf<UW_WorldChat> chatWidgetClass = StaticLoadClass(UW_WorldChat::StaticClass(), NULL, TEXT("WidgetBlueprint'/Game/Blueprint/Widget/Game/Chatting/BW_WorldChat.BW_WorldChat_C'"));
	if (chatWidgetClass)
	{
		mChatWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("mChatWidget"));
		mChatWidget->SetupAttachment(RootComponent);
		mChatWidget->SetWidgetClass(chatWidgetClass);
		mChatWidget->SetCollisionProfileName(TEXT("NoCollision"));
		mChatWidget->SetWidgetSpace(EWidgetSpace::Screen);
		mChatWidget->SetDrawAtDesiredSize(true);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> LEVELUP_PARTICLE(TEXT("ParticleSystem'/Game/RPGEffects/Particles/P_Status_LevelUp.P_Status_LevelUp'"));
	if (LEVELUP_PARTICLE.Succeeded())
	{
		mLevelUpParticle = LEVELUP_PARTICLE.Object;
	}

	mLevelUpParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LevelUpParticle"));
	mLevelUpParticleSystem->SetupAttachment(RootComponent);
	mLevelUpParticleSystem->bAutoActivate = false;

	mLevelUpParticleSystem->SetTemplate(mLevelUpParticle);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> SHIELD_PARTICLE(TEXT("NiagaraSystem'/Game/sA_Megapack_v1/sA_PickupSet_1/Fx/NiagaraSystems/NS_Shield_2.NS_Shield_2'"));
	if (SHIELD_PARTICLE.Succeeded())
	{
		mApplyBuffParticle = SHIELD_PARTICLE.Object;
	}
	mApplyBuffStore = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BuffParticle"));
	mApplyBuffStore->SetupAttachment(RootComponent);
	mApplyBuffStore->SetRelativeScale3D(FVector(1.5f));
	mApplyBuffStore->bAutoActivate = false;

	mApplyBuffStore->SetAsset(mApplyBuffParticle);

	bBuffActive = false;

	bCanMove = true;

	bUsingSkill = false;

	bCanSkillQ = true;
	bCanSkillW = true;
	bCanSkillE = true;
	bCanSkillR = true;
	bCanDash = true;

	mQCoolDown = 2.5f;
	mWCoolDown = 2.5f;
	mECoolDown = 2.5f;
	mRCoolDown = 2.5f;
	mDashCoolDown = 2.5f;
}

ANC_Game::~ANC_Game()
{
}

void ANC_Game::ShowWorldChat(const FString& inPlayerName, const FString& inMessage, const float& inDuration)
{
	UUserWidget* widget = mChatWidget->GetUserWidgetObject();
	if (nullptr == widget)
	{
		return;
	}

	UW_WorldChat* chat = Cast<UW_WorldChat>(widget);
	if (nullptr == chat)
	{
		return;
	}
	chat->SetWorldChat(inPlayerName, inMessage, inDuration);
}

void ANC_Game::ShowLevelUpParticle()
{
	mLevelUpParticleSystem->Activate();
}

void ANC_Game::ActiveBuffParticle()
{
	mApplyBuffStore->SetFloatParameter("LifeTime", 99999.f);
	mApplyBuffStore->Activate();
}

void ANC_Game::DeActiveBuffParticle()
{
	mApplyBuffStore->SetFloatParameter("LifeTime", 0.1f);
	mApplyBuffStore->Deactivate();
}

void ANC_Game::StopMovement()
{
	this->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
}

void ANC_Game::ActiveMovement()
{
	this->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void ANC_Game::BeginPlay()
{
	Super::BeginPlay();
}

void ANC_Game::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ANC_Game::Destroyed()
{

	//Super::Destroyed();

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

	ANPC_Game* controller = Cast<ANPC_Game>(GetController());
	if (nullptr == controller)
	{
		return;
	}

	ANPS_Game* playerState = controller->GetPlayerState<ANPS_Game>();
	if (nullptr == playerState)
	{
		return;
	}

	controller->UnPossess();

	gameState->RemovePlayerState(playerState);

	playerState->Destroy();

	world->DestroyActor(playerState);

	world->DestroyActor(controller);
}

void ANC_Game::StartQTimer()
{
	GetWorldTimerManager().SetTimer(mQTimer, this, &ANC_Game::EndQ, mQCoolDown, false);
}

void ANC_Game::StartWTimer()
{
	GetWorldTimerManager().SetTimer(mWTimer, this, &ANC_Game::EndW, mWCoolDown, false);
}

void ANC_Game::StartETimer()
{
	GetWorldTimerManager().SetTimer(mETimer, this, &ANC_Game::EndE, mECoolDown, false);
}

void ANC_Game::StartRTimer()
{
	GetWorldTimerManager().SetTimer(mRTimer, this, &ANC_Game::EndR, mRCoolDown, false);
}

void ANC_Game::StartDashTimer()
{
	GetWorldTimerManager().SetTimer(mDashTimer, this, &ANC_Game::EndDash, mDashCoolDown, false);
}

void ANC_Game::EndQ()
{
	bCanSkillQ = true;
}

void ANC_Game::EndW()
{
	bCanSkillW = true;
}

void ANC_Game::EndE()
{
	bCanSkillE = true;
}

void ANC_Game::EndR()
{
	bCanSkillR = true;
}

void ANC_Game::EndDash()
{
	bCanDash = true;
}
