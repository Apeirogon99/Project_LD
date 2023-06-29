// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Controller/MovementController.h"
#include "MovementController.h"

#include <Network/NetworkUtils.h>
#include <Protobuf/Handler/FClientPacketHandler.h>
#include <Protobuf/Handler/FGamePacketHandler.h>

#include <Network/NetworkCharacter.h>
#include <Framework/Game/C_Game.h>
#include <GameFramework/PawnMovementComponent.h>

#include <Framework/Character/AppearanceCharacter.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <Kismet/GameplayStatics.h>

AMovementController::AMovementController()
{
	IsMoveToMouseCursor = false;
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

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), mMouseCursorParticle, FVector(DestLocation.X, DestLocation.Y, (DestLocation.Z + 1.0f)), FRotator::ZeroRotator, true);

	//TODO: 서버에게 보낼 값
	ANetworkController* controller = Cast<ANetworkController>(this);
	if (nullptr == controller)
	{
		return;
	}

	Protocol::C2S_MovementCharacter movementPacket;
	const int64 serverTimeStamp = controller->GetServerTimeStamp();
	movementPacket.set_timestamp(serverTimeStamp);

	APawn* pawn = controller->GetPawn();
	if (nullptr == pawn)
	{
		return;
	}

	FVector pawnLocation = pawn->GetActorLocation();
	Protocol::SVector* oldMovementLocation = movementPacket.mutable_cur_location();
	oldMovementLocation->set_x(pawnLocation.X);
	oldMovementLocation->set_y(pawnLocation.Y);
	oldMovementLocation->set_z(pawnLocation.Z);

	Protocol::SVector* newMovementLocation = movementPacket.mutable_move_location();
	newMovementLocation->set_x(DestLocation.X);
	newMovementLocation->set_y(DestLocation.Y);
	newMovementLocation->set_z(pawnLocation.Z);

	SendBufferPtr pakcetBuffer = FGamePacketHandler::MakeSendBuffer(controller, movementPacket);
	controller->Send(pakcetBuffer);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
}

void AMovementController::MoveDestination(const FVector inOldMovementLocation, const FVector inNewMovementLocation, const int64 inTime)
{

	APawn* pawn = this->GetPawn();
	if (nullptr == pawn)
	{
		return;
	}

	FVector	direction = inNewMovementLocation - inOldMovementLocation;
	direction.Normalize();

	FVector velocity = direction * 330.0f;
	float	duration = inTime / 1000.0f;

	FVector deadReckoningLocation = inOldMovementLocation + (velocity * duration);

	//현재 위치와 비교하여 차이가 얼마나 나는지 판단
	FVector curLocation = pawn->GetActorLocation();
	float locationDistance = FVector::Dist2D(curLocation, deadReckoningLocation);
	if (locationDistance > 50.0f)
	{
		pawn->SetActorLocation(inOldMovementLocation, false, nullptr, ETeleportType::ResetPhysics);
		pawn->SetActorRotation(direction.Rotation());
		UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("New Pos %ws"), *inOldMovementLocation.ToString()), ELogLevel::Warning);
	}
	else
	{
		//pawn->SetActorLocation(deadReckoningLocation, false, nullptr, ETeleportType::ResetPhysics);
		UNetworkUtils::NetworkConsoleLog(FString::Printf(TEXT("Dec Pos %ws"), *deadReckoningLocation.ToString()), ELogLevel::Warning);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, inNewMovementLocation);
	}
}