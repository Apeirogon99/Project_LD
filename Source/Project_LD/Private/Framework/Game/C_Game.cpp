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

#include "Kismet/KismetSystemLibrary.h"
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
	mCameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	mCameraBoom->bDoCollisionTest = false;

	mGameCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	mGameCameraComponent->SetupAttachment(mCameraBoom, USpringArmComponent::SocketName);
	mGameCameraComponent->bUsePawnControlRotation = false;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
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

void AC_Game::InteractItem()
{
	TArray<AActor*> Result;
	GetOverlappingActors(Result, AActor::StaticClass());

	for (auto& Actor : Result)
	{
		if (UKismetSystemLibrary::DoesImplementInterface(Actor, UInteractiveInterface::StaticClass()))
		{
			FString ClassName = Actor->GetClass()->GetName();
			//UE_LOG(LogTemp, Warning, TEXT("Interactive Class Name : %s"), *ClassName);

			if (ClassName == "ItemParent")
			{
				AItemParent* Item = Cast<AItemParent>(Actor);
				if (Item != nullptr)
				{
					Item->Interactive(this);
				}
			}
			else if (ClassName == "BE_Slime_C")
			{
				//UE_LOG(LogTemp, Warning, TEXT("Interactive Class Slime_C"));
				AE_Slime* Slime = Cast<AE_Slime>(Actor);
				if (Slime != nullptr)
				{
					Slime->Interactive(this);
				}
			}
			else if (ClassName == "BE_NomalSkeleton_C")
			{
				//UE_LOG(LogTemp, Warning, TEXT("Interactive Class Slime_C"));
				AE_NomalSkeleton* NomalSkeleton = Cast<AE_NomalSkeleton>(Actor);
				if (NomalSkeleton != nullptr)
				{
					NomalSkeleton->Interactive(this);
				}
			}
			else if (ClassName == "BE_ArcherSkeleton_C")
			{
				//UE_LOG(LogTemp, Warning, TEXT("Interactive Class Slime_C"));
				AE_ArcherSkeleton* ArcherSkeleton = Cast<AE_ArcherSkeleton>(Actor);
				if (ArcherSkeleton != nullptr)
				{
					ArcherSkeleton->Interactive(this);
				}
			}
			else if (ClassName == "BE_WarriorSkeleton_C")
			{
				//UE_LOG(LogTemp, Warning, TEXT("Interactive Class Slime_C"));
				AE_WarriorSkeleton* WarriorSkeleton = Cast<AE_WarriorSkeleton>(Actor);
				if (WarriorSkeleton != nullptr)
				{
					WarriorSkeleton->Interactive(this);
				}
			}
		}
	}
}
