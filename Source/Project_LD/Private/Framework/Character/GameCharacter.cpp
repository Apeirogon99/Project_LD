// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/Character/GameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/DecalComponent.h"

AGameCharacter::AGameCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	GameCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	GameCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	GameCameraComponent->bUsePawnControlRotation = false;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));

/**Character Status Setting**/

	//Attack Range
	AttackRange = 200.0f;	AttackRadius = 50.0f;
	//Attack Info
	IsAttacking = false;
	//Health
	MaxHealth = 100.0f;	CurrentHealth = 100.0f;
	//Mana
	MaxMana = 100.0f;		CurrentMana = 100.0f;
	//Character Level
	CharacterLevel = 1;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

AGameCharacter::~AGameCharacter()
{

}

void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AGameCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FHitResult TraceHitResult;
		PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
		FVector CursorFV = TraceHitResult.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();
		CursorToWorld->SetWorldLocation(TraceHitResult.Location);
		CursorToWorld->SetWorldRotation(CursorR);
	}
	*/
}

void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
