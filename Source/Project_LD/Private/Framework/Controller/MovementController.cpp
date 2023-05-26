// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Controller/MovementController.h"
#include "MovementController.h"

#include <Network/NetworkUtils.h>
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>

#include <Network/NetworkCharacter.h>
#include <Framework/Character/AppearanceCharacter.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>

AMovementController::AMovementController()
{
	
}

AMovementController::~AMovementController()
{
}

void AMovementController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (IsMoveToMouseCursor)
	{
		MoveToMouseCursor();
		IsMoveToMouseCursor = false;
	}
}

void AMovementController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination(Player)", IE_Pressed, this, &AMovementController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination(Player)", IE_Released, this, &AMovementController::OnSetDestinationReleased);
	InputComponent->BindAxis("CameraZoom(Player)", this, &AMovementController::OnSetCameraZoomAxis);
}

void AMovementController::OnSetDestinationPressed()
{
	IsMoveToMouseCursor = true;
}

void AMovementController::OnSetDestinationReleased()
{
	IsMoveToMouseCursor = false;
}

void AMovementController::OnSetCameraZoomAxis(const float inValue)
{
}

void AMovementController::SwitchMovementMode()
{
	bShowMouseCursor = true;
	IsMoveToMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMovementController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AMovementController::SetNewMoveDestination(const FVector DestLocation)
{
	//TODO: 서버에게 보낼 값
	ANetworkController* controller = Cast<ANetworkController>(this);

	Protocol::C2S_MovementCharacter movementPacket;
	Protocol::STransform* newTransform = movementPacket.mutable_transform();
	Protocol::SVector* newPosition = newTransform->mutable_position();
	
	newPosition->set_x(DestLocation.X);
	newPosition->set_y(DestLocation.Y);
	newPosition->set_z(DestLocation.Z);

	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(controller, movementPacket);
	controller->Send(pakcetBuffer);
}

void AMovementController::MoveDestination(const FVector DestLocation)
{
	//TODO: 서버에서 받는 값
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
	}
}