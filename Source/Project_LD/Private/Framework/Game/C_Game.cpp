	// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/Game/C_Game.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "GameContent/Item/ItemParent.h"

#include "GameContent/Enemy/E_Slime.h"
#include "GameContent/Enemy/E_NomalSkeleton.h"
#include "GameContent/Enemy/E_ArcherSkeleton.h"
#include "GameContent/Enemy/E_WarriorSkeleton.h"

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

void AC_Game::OnAttackCameraZoomIn_Implementation()
{
}

void AC_Game::OnAttackCameraZoomOut_Implementation()
{
}
