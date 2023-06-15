	// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/Game/C_Game.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "GameContent/Item/ItemParent.h"

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

	static ConstructorHelpers::FClassFinder<AAppearanceCharacter> PreviewCharacter(TEXT("Blueprint'/Game/Blueprint/Widget/Game/Inventory/PreView/BP_PreViewCharacter.BP_PreViewCharacter_C'"));
	if (PreviewCharacter.Succeeded())
	{
		PreviewBPCharacter = PreviewCharacter.Class;
	}

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

AC_Game::~AC_Game()
{

}

void AC_Game::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector newLocation = FVector(0.f, 0.f, -1000.f);
		FRotator newRotator = FRotator();

		spawnPreview = world->SpawnActor<AAppearanceCharacter>(PreviewBPCharacter, newLocation, newRotator, spawnParams);
	}
}

void AC_Game::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (spawnPreview)
	{
		spawnPreview->Destroy();
	}
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
