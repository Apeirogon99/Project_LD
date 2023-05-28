// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/Game/C_Game.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "GameContent/Item/ItemParent.h"
#include "Kismet/KismetSystemLibrary.h"

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
	mCameraBoom->TargetArmLength = 1600.f;
	mCameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	mCameraBoom->bDoCollisionTest = false;

	mGameCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	mGameCameraComponent->SetupAttachment(mCameraBoom, USpringArmComponent::SocketName);
	mGameCameraComponent->bUsePawnControlRotation = false;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));

	mInventoryComponent = CreateDefaultSubobject<UACInventoryComponent>(TEXT("InventoryComponent"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

AC_Game::~AC_Game()
{
}

void AC_Game::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("InteractItem", IE_Pressed, this, &AC_Game::InteractItem);
}

void AC_Game::InteractItem()
{
	TArray<AActor*> Result;
	GetOverlappingActors(Result, AItemParent::StaticClass());

	for (auto& Actor : Result)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(Actor, UInventoryInterface::StaticClass()))
		{
			AItemParent* Item = Cast<AItemParent>(Actor);
			if (Item != nullptr)
			{
				Item->PickUpItem(this);
			}
		}
	}
}
