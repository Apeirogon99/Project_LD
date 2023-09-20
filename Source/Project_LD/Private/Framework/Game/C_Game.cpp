	// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/Game/C_Game.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "GameContent/Item/ItemParent.h"

#include <Widget/Handler/ClientHUD.h>
#include <Widget/Game/Main/W_MainGame.h>

#include <Game/GM_Game.h>
#include <Game/PC_Game.h>
#include <Game/PS_Game.h>

#include "GameContent/Enemy/E_Slime.h"
#include "GameContent/Enemy/E_NomalSkeleton.h"
#include "GameContent/Enemy/E_ArcherSkeleton.h"
#include "GameContent/Enemy/E_WarriorSkeleton.h"

#include "Components/Border.h"
#include "Framework/Interface/InteractiveInterface.h"
#include <UObject/ConstructorHelpers.h>


AC_Game::AC_Game()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	mCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	mCameraBoom->SetupAttachment(RootComponent);
	mCameraBoom->SetUsingAbsoluteRotation(true);
	mCameraBoom->TargetArmLength = 1000.f;
	mCameraBoom->SetRelativeRotation(FRotator(300.f, 0.f, 0.f));
	mCameraBoom->bDoCollisionTest = false;

	mGameCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	mGameCameraComponent->SetupAttachment(mCameraBoom, USpringArmComponent::SocketName);
	mGameCameraComponent->bUsePawnControlRotation = false;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bIsZoom = false;
}

AC_Game::~AC_Game()
{
	/*
	UWorld* world = GetWorld();
	if (nullptr == world)
	{
		return;
	}

	AGM_Game* gamemode = Cast<AGM_Game>(world->GetAuthGameMode());
	if (nullptr == gamemode)
	{
		return;
	}

	APC_Game* playercontroller = Cast<APC_Game>(gamemode->GetNetworkController());
	if (nullptr == playercontroller)
	{
		return;
	}

	APS_Game* playerstate = playercontroller->GetPlayerState<APS_Game>();
	if (nullptr == playerstate)
	{
		return;
	}

	if (playerstate->OnCharacterHealthChanged.IsBound())
	{
		playerstate->OnCharacterHealthChanged.Clear();
	}

	if (playerstate->OnCharacterManaChanged.IsBound())
	{
		playerstate->OnCharacterManaChanged.Clear();
	}
	*/
}

void AC_Game::BeginPlay()
{
	Super::BeginPlay();
}

void AC_Game::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AC_Game::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AC_Game::Destroyed()
{
}

void AC_Game::OnCameraZoomIn_Implementation()
{
}

void AC_Game::OnCameraZoomOut_Implementation()
{
}

void AC_Game::PlayerLoseEyesight()
{
	FTimerHandle recoveryTimer;
	APC_Game* controller = Cast<APC_Game>(GetController());
	if (nullptr == controller)
	{
		return;
	}
	AClientHUD* clientHud = Cast<AClientHUD>(controller->GetHUD());
	if (nullptr == clientHud)
	{
		return;
	}
	UUserWidget* Widget = clientHud->GetWidgetFromName(TEXT("MainGame"));
	if (nullptr == Widget)
	{
		return;
	}
	UW_MainGame* maingame = Cast<UW_MainGame>(Widget);
	UBorder* borderwidget = maingame->GetPlayerSightBorder();
	borderwidget->SetVisibility(ESlateVisibility::Visible);
	GetWorldTimerManager().SetTimer(recoveryTimer, this, &AC_Game::PlayerRecoveryEyesight, 3.f, false);
}

void AC_Game::PlayerRecoveryEyesight()
{
	APC_Game* controller = Cast<APC_Game>(GetController());
	if (nullptr == controller)
	{
		return;
	}
	AClientHUD* clientHud = Cast<AClientHUD>(controller->GetHUD());
	if (nullptr == clientHud)
	{
		return;
	}
	UUserWidget* Widget = clientHud->GetWidgetFromName(TEXT("MainGame"));
	if (nullptr == Widget)
	{
		return;
	}
	UW_MainGame* maingame = Cast<UW_MainGame>(Widget);
	UBorder* borderwidget = maingame->GetPlayerSightBorder();
	borderwidget->SetVisibility(ESlateVisibility::Hidden);
}
