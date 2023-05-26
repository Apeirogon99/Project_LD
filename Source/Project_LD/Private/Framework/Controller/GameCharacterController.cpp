// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/Controller/GameCharacterController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/World.h"

AGameCharacterController::AGameCharacterController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

AGameCharacterController::~AGameCharacterController()
{
}

void AGameCharacterController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AGameCharacterController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AGameCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination(Player)", IE_Pressed, this, &AGameCharacterController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination(Player)", IE_Released, this, &AGameCharacterController::OnSetDestinationReleased);
}

void AGameCharacterController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AGameCharacterController::OnSetDestinationPressed()
{
	bMoveToMouseCursor = true;
}

void AGameCharacterController::OnSetDestinationReleased()
{
	bMoveToMouseCursor = false;
}
